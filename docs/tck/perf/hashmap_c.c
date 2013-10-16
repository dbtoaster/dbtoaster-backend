#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

//#define CUCKOO

/*
Cuckoo:
Add       : 0.327609
Clear     : 0.079027
Aggr      : 0.033156
Update    : 0.035152
Update2   : 0.692703

Linked_list:
Add       : 0.143202
Clear     : 0.229319
Aggr      : 0.020213
Update    : 0.021943
Update2   : 0.518241
*/


// -----------------------------------------------
// String encoding in a char[StrSize] with StrSize >= 2*sizeof(char*)
//   if (strlen(s)<StrSize) => used as a regular string
//   else we consider the memory as p:=char** and p[0]=StrTag, p[1]=pointer to actual string

#define StrTag ((void*)0x000ff000)
#define StrSize (2*sizeof(char*))
static inline long StrHash(const char* str) {
  char** p=(char**)(str); if (p[0]==StrTag) str=p[1];
  long hash=0; const char* c=str;
  if (*c) do { hash ^= hash * 48611 + (long)c; } while(*++c);
  return hash;
}
static inline void StrDel(char* str) { char** p=(char**)(str); if (p[0]==StrTag) free(p[1]); }
static inline const char* StrGet(const char* str) { char** p=(char**)(str); if (p[0]==StrTag) str=p[1]; return str; }
static inline void StrSet(char* str, const char* string) {
  size_t l=strlen(string); char** p=(char**)(str);
  if (l<StrSize) { p[0]=0; strlcpy(str,string,StrSize); }
  else { p[0]=StrTag; p[1]=strdup(string); }
}
static inline int StrCmp(const char* str1, const char* str2) {
  char** p1=(char**)(str1); if (p1[0]==StrTag) str1=p1[1];
  char** p2=(char**)(str2); if (p2[0]==StrTag) str2=p2[1];
  return strcmp(str1,str2);
}
static inline void StrCpy(char* dest, const char* src) { memcpy(dest,src,StrSize);
  char** ps=(char**)(src); if (ps[0]==StrTag) { char** pd=(char**)(dest); pd[1]=strdup(ps[1]); }
}

// -----------------------------------------------
// To be provided externally

// XXX: use a trie sharing strings and reference counting on them instead
// XXX: give a try to cuckoo hashing

//#define NO_STRINGS
typedef struct { long l1; long l2; char s3[StrSize]; } Key;
static inline size_t Key_hash(const Key* k) { return k->l1 * 13834103L + k->l2 * 15485863L /*+ StrHash(k->s3)*/; }
static inline int  Key_cmp(const Key* k1, const Key* k2) { return k1->l1==k2->l1 && k1->l2==k2->l2 && StrCmp(k1->s3,k2->s3); }
static inline void Key_set(Key* k, long l1, long l2, char* s3) { k->l1=l1; k->l2=l2;
#ifdef NO_STRINGS
  k->s3[0]=0;
#else 
  StrSet(k->s3,s3);
#endif
}
static inline void Key_get(Key* k, long* l1, long* l2, const char** s3) { *l1=k->l1; *l2=k->l2; *s3=StrGet(k->s3); }
static inline void Key_free(Key* k) { StrDel(k->s3); }
static inline void Key_copy(Key* dest, const Key* src) { *dest=*src;
#ifdef NO_STRINGS
  dest->s3[0]=0;
#else
  StrCpy(dest->s3,src->s3);
#endif
}

typedef struct { double d1; double d2; } Val;
static inline void Val_set(Val* v, double d1, double d2) { v->d1=d1; v->d2=d2; }
static inline void Val_get(Val* v, double* d1, double* d2) { *d1=v->d1; *d2=v->d2; }
static inline void Val_free(Val* v) { }
static inline void Val_copy(Val* dest, const Val* src) { *dest=*src; }

// -----------------------------------------------

#define ASSERT(X) extern int __assert__[-1+2*(X)];
ASSERT(sizeof(long)==8) // make sure long is 64 bits

typedef struct Rec_ Rec;
struct Rec_ {
  Key key;
  Val val;
#ifdef CUCKOO
  union {
    long head;
    struct {
      long valid : 1;
      long hash : 63;
    };
  };
#else
  long hash;
  Rec* next;
#endif
};

#define FactorGrow    0.75 // Linked list only
#define FactorShrink  0.10
#define MapSizeMin    128
#define CuckooFuns    6 // 1-15

// Regular hash maps
typedef struct {
#ifdef CUCKOO
  Rec* bkts;
  size_t h_in;
  size_t h_out[CuckooFuns];
#else
  Rec** bkts;   // array of pointers
#endif
  size_t alloc; // allocated capacity
  size_t size;  // number of elements
  size_t th_up;  // need to grow if (size>th_up)
  size_t th_low; // need to shrink if (size<th_low)
} Map;

// --------------------------------------------
// Public interface

typedef void(*Map_fun)(const Key*,const Val*);
Map* Map_init(size_t capacity);
void Map_clear(Map* map);
void Map_free(Map* map);
void Map_foreach(Map* map, Map_fun f);
const Val* Map_get(Map* map, Key* key);
#define Map_has(map,key) (Map_get(map,key)!=NULL)
void Map_put(Map* map, const Key* key, const Val* val);
void Map_del(Map* map, const Key* key);

// -----------------------------------------------------------------------------
// Helpers

#define __Map_th(m,N) { (m)->alloc=(N); (m)->th_up = FactorGrow*(N); (m)->th_low = FactorShrink*(N); if ((m)->th_low <= MapSizeMin*FactorShrink) (m)->th_low=0; }
#ifdef CUCKOO
#define __Map_hash(H) ((H)&0x8fffffffffffffff)
#define __Map_alloc(N) ((Rec*)malloc((N)*sizeof(Rec)))
#define __Map_init(b,N) { size_t i; for (i=0;i<(N);++i) (b)[i].head=0; }
#define __Map_free(m) { size_t i; for (i=0;i<(m)->alloc;++i) { Rec* rec=&(m)->bkts[i]; if (rec->valid) { Key_free(&(rec->key)); Val_free(&(rec->val)); } } }
#else
#define __Map_hash(H) (H)
#define __Map_alloc(N) ((Rec**)malloc((N)*sizeof(Rec*)))
#define __Map_init(b,N) { memset((b),0,(N)*sizeof(Rec*)); }
#define __Map_free(m) { size_t i; for (i=0;i<(m)->alloc;++i) { Rec* rec=(m)->bkts[i], *next; if (rec) do { Key_free(&(rec->key)); Val_free(&(rec->val)); next=rec->next; free(rec); } while((rec=next)); } }
#endif

#ifdef CUCKOO
#define HashMask(H) (H&((1LL<<31)-1)
static const size_t __Map_hf[30] = {1728991793L, 3326355811L, 3197636147L,
  3581949061L, 3011278649L, 3761473421L,  285566009L, 2884106279L, 2423313577L,
  1832255333L, 2293946183L,  250079861L, 2922712393L, 3259512647L, 2496698837L,
  1079282131L,  946957673L,   73959463L, 1429361497L, 2626835317L, 1616718407L,
   258365483L,  743413939L, 2850767593L, 1322521279L, 2701463923L, 1649500777L,
  1236844277L, 2632020791L, 3499022851L};

static inline ssize_t __Map_h(Map* map, size_t hash, int i) {
  if (i>CuckooFuns) return -1;
  size_t k = hash ^ (hash<<7) ^ (hash<<13);
  return ((k * __Map_hf[i<<1] + __Map_hf[(i<<1)+1]) % 375529124539L + i) % map->alloc;
}
#endif

static inline void __Map_resize(Map* map, size_t capacity) {
#ifdef CUCKOO
  Rec* old = map->bkts;
  size_t sz = map->alloc;

here_resize:
  map->alloc=capacity;
  map->bkts = __Map_alloc(map->alloc); __Map_init(map->bkts,map->alloc);
  size_t j;
  for (j=0;j<sz;++j) if (old[j].valid) {
    size_t hash = old[j].hash;
    int i=0;
    ssize_t pos = __Map_h(map,hash,i);
    do {
      Rec* rec = &map->bkts[pos];
      if (!rec->valid) { *rec=old[j]; break; }
      Rec tmp=*rec; *rec=old[j]; old[j]=tmp;
    } while((pos=__Map_h(map,hash,++i))>=0);
    if (pos<1) { 
      capacity = 1.5 * capacity;
      goto here_resize;
    }
  }
  free(old);
#else
  Rec** bs = __Map_alloc(capacity); __Map_init(bs,capacity);
  size_t i; for (i=0;i<map->alloc;++i) {
    Rec* rec=map->bkts[i], *next;
    if (rec) do {
      size_t b = rec->hash % capacity;
      next=rec->next; rec->next=bs[b]; bs[b]=rec;
    } while((rec=next));
  }
  free(map->bkts); map->bkts=bs; __Map_th(map,capacity)
#endif
}

inline Rec* Map_find(Map* map, const Key* key) {
  long hash = __Map_hash(Key_hash(key));
#ifdef CUCKOO
  int i=0;
  ssize_t pos = __Map_h(map,hash,i);
  do {
    Rec* rec = &map->bkts[pos];
    if (rec->valid && rec->hash==hash && Key_cmp(key,&(rec->key))==0) return rec;
  } while((pos=__Map_h(map,hash,++i))>=0);
#else
  size_t b = hash%map->alloc;
  Rec* rec=map->bkts[b];
  if (rec) do {
    if (hash==rec->hash && Key_cmp(key,&(rec->key))==0) return rec;
  } while((rec=rec->next));
#endif
  return NULL;
}

// -----------------------------------------------------------------------------
// Functions implementation

Map* Map_init(size_t capacity) {
  Map* m = (Map*)malloc(sizeof(Map)); m->bkts=__Map_alloc(capacity); m->alloc=capacity;
  __Map_init(m->bkts,capacity); __Map_th(m,capacity); return m;
}
void Map_clear(Map* map) { __Map_free(map); __Map_init(map->bkts,map->alloc); map->size=0; }
void Map_free(Map* map) { __Map_free(map); free(map->bkts); free(map); }

void Map_foreach(Map* map, Map_fun f) {
  size_t i; for (i=0;i<map->alloc;++i) {
#ifdef CUCKOO
    Rec* rec=&map->bkts[i];
    if (rec->valid) f(&(rec->key),&(rec->val));
#else
    Rec* rec=map->bkts[i];
    if (rec) do f(&(rec->key),&(rec->val)); while((rec=rec->next));
#endif
  }
}

void inline Map_put(Map* map, const Key* key, const Val* val) {
  long hash = __Map_hash(Key_hash(key));
#ifdef CUCKOO
  // Update
  Rec* rec=Map_find(map,key);
  if (rec) {
    Val_free(&(rec->val));
    Val_copy(&(rec->val),val);
    return;
  }
  // Insert
  Key k; Key_copy(&k,key);
  Val v; Val_copy(&v,val);
  do { // attempt
    int i=0;
    ssize_t pos = __Map_h(map,hash,i);
    do {
      Rec* rec = &map->bkts[pos];
      if (!rec->valid) {
        rec->valid=1; rec->hash=hash;
        rec->key=k;
        rec->val=v;
        ++map->size;
        return;
      }
      Key tk=rec->key; rec->key=k; k=tk;
      Val tv=rec->val; rec->val=v; v=tv;
    } while((pos=__Map_h(map,hash,++i))>=0);
    // Rebuild the table
    __Map_resize(map,map->alloc*2);
    usleep(200*1000);
  } while (1);
#else
  size_t b = hash%map->alloc;
  Rec* rec=map->bkts[b];
  // Update value
  if (rec) do if (hash==rec->hash && Key_cmp(key,&(rec->key))==0) {
    Val_free(&(rec->val)); Val_copy(&(rec->val),val); return;
  } while((rec=rec->next));
  // Insert key
  ++map->size; if (map->size>map->th_up) __Map_resize(map,map->alloc*2);
  rec = (Rec*)malloc(sizeof(Rec));
  Key_copy(&(rec->key),key); Val_copy(&(rec->val),val); rec->hash=hash;
  rec->next=map->bkts[b]; map->bkts[b]=rec;
#endif
}

const Val* Map_get(Map* map, Key* key) {
  Rec* rec = Map_find(map,key);
  return rec ? &rec->val : NULL;
}

void Map_del(Map* map, const Key* key) {
#ifdef CUCKOO
  Rec* rec = Map_find(map,key);
  if (rec) {
    rec->valid=0;
    Key_free(&(rec->key)); 
    Val_free(&(rec->val));
    --map->size; if (map->size<map->th_low) __Map_resize(map,map->alloc/2);
  }
#else
  long hash = __Map_hash(Key_hash(key));
  size_t b = hash%map->alloc;
  Rec **ptr=(&map->bkts[b]),*rec=*ptr;
  if (rec) do {
    if (hash==rec->hash && Key_cmp(key,&(rec->key))==0) {
      *ptr=rec->next;
      Key_free(&(rec->key)); Val_free(&(rec->val)); free(rec);
      --map->size; if (map->size<map->th_low) __Map_resize(map,map->alloc/2);
      return;
    }
    ptr=&(rec->next); rec=*ptr;
  } while(rec);
#endif
}

// -----------------------------------------------------------------------------

// Timer
struct {
  int n;
  double res[20];
  struct timeval t0,t1;
}  _tt;
void start() { gettimeofday (&_tt.t0,NULL); }
void stop() { gettimeofday (&_tt.t1,NULL); _tt.res[_tt.n]=(_tt.t1.tv_sec-_tt.t0.tv_sec)+((double)(_tt.t1.tv_usec-_tt.t0.tv_usec))/1000000L; if (_tt.n<19) ++_tt.n; }
int dcmp(const void *x, const void *y) { double xx = *(double*)x, yy = *(double*)y; return (xx<yy) ? -1 : ((xx > yy) ? 1 : 0); }
void pr(const char* name) { qsort(_tt.res,_tt.n,sizeof(double),dcmp); printf("%-10s: %0.6f\n",name,_tt.res[_tt.n/2]); }
void rst() { _tt.n=0; }

Map* map1;
Map* map2;
static long N = 1000000;

void load() {
 long i; for (i=0;i<N;++i) {
   Key k = {i,i+1,"Hello world"};
   Val v = {i*3.0,i*4.0};
   Map_put(map1,&k,&v);
 }
}
void clear() { Map_clear(map1); Map_clear(map2); }

void fun_xx(const Key* k, const Val* v) { Val* vv=(Val*)v; vv->d1*=2.0; vv->d2*=0.5; }

double acc=0;
void fun_agg(const Key* k, const Val* v) { acc += v->d1*2.0 + v->d2*0.5; }

void fun_swap1(const Key* k, const Val* v) { Map_del(map1,k); Key k2={k->l1-3,k->l2+3,"Hello world2"}; Val v2={v->d1*2.0,v->d2*0.5}; Map_put(map2,&k2,&v2); }
void fun_swap2(const Key* k, const Val* v) { Map_del(map2,k); Key k2={k->l1-3,k->l2+3,"Hello world2"}; Val v2={v->d1*2.0,v->d2*0.5}; Map_put(map1,&k2,&v2); }

int main() {
  int z;
  map1 = Map_init(128);
  map2 = Map_init(128);

  // 1. Add/clear
  rst();
  for (z=0;z<10;++z) { start(); load(); stop(); clear(); }
  pr("Add");
  rst();
  for (z=0;z<10;++z) { load(); start(); clear(); stop(); }
  pr("Clear");

  load();
  // 2. Loop/aggregate
  rst();
  for (z=0;z<10;++z) {
    start();
    Map_foreach(map1,fun_agg);
    stop();
  }
  pr("Aggr");

  // 3. Loop update
  rst();
  for (z=0;z<10;++z) {
    start();
    Map_foreach(map1,fun_xx);
    stop();
  }
  pr("Update");

  // 4. Loop add/delete
  rst();
  for (z=0;z<10;++z) {
    start();
    if (z%2==0) {
      Map_foreach(map1,fun_swap1);
    } else {
      Map_foreach(map2,fun_swap2);
    }
    stop();
  }
  pr("Update2");

  Map_free(map1);
  Map_free(map2);
  return 0;
}

/*
Map* map;

void for1(const Key* k, const Val* v) {
  Key k2; Key_copy(&k2,k);
  Val v2; Val_set(&v2,v->d1*2.0,v->d2*0.5);
  Map_put(map,&k2,&v2); Key_free(&k2); Val_free(&v2);
}

int main() {
  int z;
  map = Map_init(128);
  for (z=0;z<10;++z) {
    srand(time(NULL));
    struct timeval t0,t1;
    gettimeofday (&t0,NULL);
  
    #define N 1000
    #define F 1.5
  
    long i,j,n=N;
    for (i=0;i<n;++i) {
      Key k; Key_set(&k,i,i+1,"Hello world");
      Val v; Val_set(&v,i*3.0,i*4.0);
      Map_put(map,&k,&v); Key_free(&k); Val_free(&v);
    }
    
    for (j=0;j<n;++j) {
      i=rand()%(long)(N*F);
      Key k; Key_set(&k,i,i+1,"Hello world");
      Val v; Val_set(&v,i*1.0,i*1.0);
      if (!Map_has(map,&k)) Map_put(map,&k,&v); Key_free(&k); Val_free(&v);
      if (i%10==0) Map_foreach(map,for1);
    }

    gettimeofday (&t1,NULL);
    printf("Time: %0.6f\n",(t1.tv_sec-t0.tv_sec)+((double)(t1.tv_usec-t0.tv_usec))/1000000L);
    Map_clear(map);
    printf("------------------\n");
  }
  Map_free(map);
  return 0;
}
*/
