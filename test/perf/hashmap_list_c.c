#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

//#define CUCKOO

// -----------------------------------------------

/*
Median in seconds:
Plain Java         = 0,956764
Plain C            = 1.472860
Plain C no strings = 0.394969
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
static inline long Key_hash(const Key* k) { return k->l1 * 13834103L + k->l2 * 15485863L /*+ StrHash(k->s3)*/; }
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

#define FactorGrow    0.75
#define FactorShrink  0.10
#define MapSizeMin    128

// Regular hash maps
typedef struct {
#ifdef CUCKOO
#else
  Rec** data;   // array of pointers
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
void Map_del(Map* map, Key* key);

// --------------------------------------------

#define Map_th(m,N) { (m)->alloc=(N); (m)->th_up = FactorGrow*(N); (m)->th_low = FactorShrink*(N); if ((m)->th_low <= MapSizeMin*FactorShrink) (m)->th_low=0; }
Map* Map_init(size_t capacity) {
  Map* m = (Map*)malloc(sizeof(Map));
  m->data = (Rec**)malloc(capacity*sizeof(Rec*));
  m->alloc = capacity;
  memset(m->data,0,capacity*sizeof(Rec*));
  Map_th(m,capacity);
  return m;
}

static inline void Map_free_internal(Map* map) {
  size_t i; for (i=0;i<map->alloc;++i) { Rec* rec=map->data[i];
    if (rec) do { Key_free(&(rec->key)); Val_free(&(rec->val)); } while((rec=rec->next));
  }
}

void Map_clear(Map* map) { Map_free_internal(map); memset(map->data,0,sizeof(Rec*)*map->alloc); map->size=0; }
void Map_free(Map* map) { Map_free_internal(map); free(map->data); free(map); }

static inline void Map_resize_internal(Map* map, size_t capacity) {
  Rec** data = (Rec**)malloc(capacity*sizeof(Rec*)); memset(data,0,capacity*sizeof(Rec*));
  size_t i; for (i=0;i<map->alloc;++i) {
    Rec* rec=map->data[i], *next;
    if (rec) do {
      size_t b = rec->hash % capacity;
      next=rec->next; rec->next=data[b]; data[b]=rec;
    } while((rec=next));
  }
  free(map->data); map->data=data; Map_th(map,capacity)
}

void Map_foreach(Map* map, Map_fun f) {
  size_t i; for (i=0;i<map->alloc;++i) {
    Rec* rec=map->data[i];
    if (rec) do f(&(rec->key),&(rec->val)); while((rec=rec->next));
  }
}

const Val* Map_get(Map* map, Key* key) {
  long hash = Key_hash(key) ;
  size_t b = hash%map->alloc;
  Rec* rec=map->data[b];
  if (rec) do if (hash==rec->hash && Key_cmp(key,&(rec->key))==0) {
    return &(rec->val);
  } while((rec=rec->next));
  return NULL;
}

void Map_put(Map* map, const Key* key, const Val* val) {
  long hash = Key_hash(key);
  size_t b = hash%map->alloc;
  Rec* rec=map->data[b];
  // Update value
  if (rec) do if (hash==rec->hash && Key_cmp(key,&(rec->key))==0) {
    Val_free(&(rec->val)); Val_copy(&(rec->val),val); return;
  } while((rec=rec->next));
  // Insert key
  ++map->size; if (map->size>map->th_up) Map_resize_internal(map,map->alloc*2);
  rec = (Rec*)malloc(sizeof(Rec));
  Key_copy(&(rec->key),key); Val_copy(&(rec->val),val); rec->hash=hash;
  rec->next=map->data[b]; map->data[b]=rec;
}

void Map_del(Map* map, Key* key) {
  long hash = Key_hash(key);
  size_t b = hash%map->alloc;
  Rec **ptr=(&map->data[b]),*rec=*ptr;
  if (rec) do {
    if (hash==rec->hash && Key_cmp(key,&(rec->key))==0) {
      *ptr=rec->next;
      Key_free(&(rec->key));
      Val_free(&(rec->val));
      free(rec);
      --map->size; if (map->size<map->th_low) Map_resize_internal(map,map->alloc/2);
      return;
    }
    ptr=&(rec->next); rec=*ptr;
  } while(rec);
}

// -----------------------------------------------------------------------------

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
  
    #define N 10000
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
  }
  Map_free(map);
  return 0;
}
