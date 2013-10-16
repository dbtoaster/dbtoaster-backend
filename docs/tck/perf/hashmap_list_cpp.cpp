#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <string>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

//#define CUCKOO
// XXX: give a try to cuckoo hashing

// -----------------------------------------------
/*
// String encoding in a char[StrSize] with StrSize >= 2*sizeof(char*)
//   if (strlen(s)<StrSize) => used as a regular string
//   else we consider the memory as p:=char** and p[0]=StrTag, p[1]=pointer to actual string

// XXX: introduce sharing reference strings and possibly a big trie where to store them
// XXX: use a trie sharing strings and reference counting on them instead
// XXX: there is a BUG hampering strings performance

class str_pack {
private:
  #define str_tag ((char*)0x000ff000)
  #define str_size (2*sizeof(char*))
  union {
    char ds[str_size];
    char* dp[2];
  };
public:
  str_pack() { dp[0]=0; }
  str_pack(const char* str) { dp[0]=0; operator=(str); }
  ~str_pack() { if (dp[0]==str_tag) free(dp[1]); }
  bool operator==(const str_pack &that) const { return strcmp(dp[0]==str_tag?dp[1]:ds,that.dp[0]==str_tag?that.dp[1]:that.ds)==0; }
  void operator=(const str_pack &that) { memcpy(ds,that.ds,str_size); if (dp[0]==str_tag) dp[1]=strdup(dp[1]); }
  void operator=(const char* str) {
    size_t l=strlen(str);
    if (dp[0]==str_tag) { if (!strcmp(dp[1],str)) return; free(dp[1]); }
    if (l<str_size) { dp[0]=0; strlcpy(ds,str,str_size); }
    else { dp[0]=str_tag; dp[1]=strdup(str); }
  }
  long hash() const {
    long hash=0; const char* c=ds; if (dp[0]==str_tag) c=dp[1];
    if (*c) do { hash ^= hash * 48611 + (long)c; } while(*++c); return hash;
  }
  const char* c_str() const { return dp[0]==str_tag ? dp[1] : ds; }
};
*/
// -----------------------------------------------
// To be provided externally

class Key {
public:
  long l1; long l2; string s3; //str_pack s3;
  Key() {}
  Key(long l1_, long l2_, char* s3_) { l1=l1_; l2=l2_; s3=s3_; }
  const long hash() { return l1 * 13834103L + l2 * 15485863L /*+ s3.hash()*/; }
  bool operator==(const Key &that) { return l1==that.l1 && l2==that.l2 && s3==that.s3; }
};

class Val {
public:
  double d1; double d2;
  Val() {}
  Val(double d1_, double d2_) { d1=d1_; d2=d2_; }
};

// -----------------------------------------------

#define ASSERT(X) extern int __assert__[-1+2*(X)];
ASSERT(sizeof(long)==8) // make sure long is 64 bits

template <class K, class V>
class Rec {
public:
  K key;
  V val;
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
  Rec(K key_, V val_) { key=key_; val=val_; }
};

#define FactorGrow    0.75
#define FactorShrink  0.10
#define MapSizeMin    128

// Regular hash maps
template <class K, class V>
class Map {
  typedef void(*fun)(K*,V*);

#ifdef CUCKOO
#else
  Rec<K,V>** data;   // array of pointers
#endif
  size_t alloc; // allocated capacity
  size_t size;  // number of elements
  size_t th_up;  // need to grow if (size>th_up)
  size_t th_low; // need to shrink if (size<th_low)
  inline void th(size_t n) { alloc=n; th_up=FactorGrow*n; th_low=FactorShrink*n; if (th_low <= MapSizeMin*FactorShrink) th_low=0; }
  inline void release() { size_t i; for (i=0;i<alloc;++i) { Rec<K,V>* rec=data[i], *next; if (rec) do { next=rec->next; delete rec; } while((rec=next)); } }
  inline void resize(size_t capacity) {
    Rec<K,V>** d = (Rec<K,V>**)malloc(capacity*sizeof(Rec<K,V>*)); memset(d,0,capacity*sizeof(Rec<K,V>*));
    size_t i; for (i=0;i<alloc;++i) {
      Rec<K,V>* rec=data[i], *next;
      if (rec) do {
        size_t b = rec->hash % capacity;
        next=rec->next; rec->next=d[b]; d[b]=rec;
      } while((rec=next));
    }
    free(data); data=d; th(capacity);
  }

public:
  Map(size_t capacity) {
    data = (Rec<K,V>**)malloc(capacity*sizeof(Rec<K,V>*)); alloc = capacity;
    memset(data,0,capacity*sizeof(Rec<K,V>*)); th(capacity);
  }
  ~Map() { release(); free(data); }
  void clear() { release(); memset(data,0,sizeof(Rec<K,V>*)*alloc); size=0; }
  void foreach(fun f) const {
    size_t i; for (i=0;i<alloc;++i) { Rec<K,V>* rec=data[i];
      if (rec) do f(&(rec->key),&(rec->val)); while((rec=rec->next));
    }
  }
  const bool has(K &key) const { return get(key)!=NULL; }
  const V* get(K &key) const {
    long h=key.hash(); size_t b=h%alloc; Rec<K,V>* rec=data[b];
    if (rec) do if (h==rec->hash && key==rec->key) { return &(rec->val); } while((rec=rec->next));
    return NULL;
  }
  void put(K &key, V &val) {
    long h=key.hash(); size_t b=h%alloc; Rec<K,V>* rec=data[b];
    // Update value
    if (rec) do if (h==rec->hash && key==rec->key) {
      rec->val=val; return;
    } while((rec=rec->next));
    // Insert key
    ++size; if (size>th_up) resize(alloc*2);
    rec = new Rec<K,V>(key,val); //  (Rec<K,V>*)malloc(sizeof(Rec<K,V>));
    //rec->key=key; rec->val=val;
    rec->hash=h; rec->next=data[b]; data[b]=rec;
  }
  void del(const K &key) {
    long h=key.hash(); size_t b=h%alloc;
    Rec<K,V> **ptr=(&data[b]),*rec=*ptr;
    if (rec) do {
      if (h==rec->hash && key==rec->key) {
        *ptr=rec->next;
        delete &(rec->key);
        delete &(rec->val);
        free(rec);
        --size; if (size<th_low) resize(alloc/2);
        return;
      }
      ptr=&(rec->next); rec=*ptr;
    } while(rec);
  }
};

// -----------------------------------------------------------------------------

Map<Key,Val> map(128);

void for1(Key* k, Val* v) {
  //printf("%ld %ld %s -> %f %f\n",k->l1,k->l2,k->s3.c_str(),v->d1,v->d2);
  Val v2(v->d1*2.0,v->d2*0.5);
  map.put(*k, v2);
}

int main() {
  char str0[32]; strlcpy(str0,"Hello world",32);

  int z;
  for (z=0;z<10;++z) {
    srand(time(NULL));
    struct timeval t0,t1;
    gettimeofday (&t0,NULL);

  
    #define N 10000
    #define F 1.5
  
    long i,j,n=N;
    for (i=0;i<n;++i) {
      Key k(i,i+1,str0);
      Val v(i*3.0,i*4.0);
      map.put(k,v);
    }
  
    for (j=0;j<n;++j) {
      i=rand()%(long)(N*F);
      Key k(i,i+1,str0);
      Val v(i*1.0,i*1.0);
      if (!map.has(k)) map.put(k,v);
      
      if (i%10==0) map.foreach(for1);
    }

    gettimeofday (&t1,NULL);
    printf("Time: %0.6f\n",(t1.tv_sec-t0.tv_sec)+((double)(t1.tv_usec-t0.tv_usec))/1000000L);
    map.clear();
  }

  return 0;
}
