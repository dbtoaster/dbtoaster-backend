#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

template<class K,class V, int num=2>
class Cuckoo {
	K empty;
	K* keys;
	V* vals;
	size_t sz;
	size_t hf[2*num];

	inline size_t hash(K key, int n) {
		size_t k = (size_t)key; k ^= k<<7 ^ k<<13;
		return ((k * hf[n*2] + hf[n*2+1]) % 4294967291u) % sz;
	}
	ssize_t rehash(K key, size_t prev) {
		size_t h[num]; for (int i=0;i<num;++i) h[i]=hash(key,i);
		for (int i=0;i<num-1;++i) if (prev==h[i]) return h[i+1];
		return -1; // error
	}
	inline bool is_empty(size_t pos) { return memcmp(&keys[pos],&empty,sizeof(K))==0; }

public:
	Cuckoo(size_t* hash_fun,size_t size=4) {
		sz = size;
		keys=new K[size];
		vals=new V[size];
		memset(keys,0xfe,size*sizeof(K));
		memset(&empty,0xfe,sizeof(K));
		memcpy(hf,hash_fun,num*2*sizeof(size_t));
	}
	~Cuckoo() {
		delete[] keys;
		delete[] vals;
	}
public:
	void add(K key, V val) {
		ssize_t pos = hash(key, 0);
		do {
			if (is_empty(pos) || keys[pos]==key) {
				keys[pos]=key; vals[pos]=val; return;
			}
			K tk=keys[pos]; keys[pos]=key; key=tk;
			V tv=vals[pos]; vals[pos]=val; val=tv;
		} while((pos=rehash(key,pos))>=0);

		// Rebuild the table
		Cuckoo<K,V,num> h2(hf,sz*2);
		for (size_t i=0;i<sz;++i) if (keys[i]!=empty) h2.add(keys[i],vals[i]);
		K* tk = h2.keys; h2.keys=keys; keys=tk;
		V* tv = h2.vals; h2.vals=vals; vals=tv;
		sz=sz*2;
		fprintf(stderr,"Table rebuilt.\n");
	}
	void del(K key) {
		size_t h[num]; for (int i=0;i<num;++i) h[i]=hash(key,i);
		for (int i=0;i<num;++i) if (keys[h[i]]==key) {
			keys[h[i]] = empty;
		}
	}
	V get(K key) {
		size_t h[num]; for (int i=0;i<num;++i) h[i]=hash(key,i);
		for (int i=0;i<num;++i) { if (keys[h[i]]==key) return vals[h[i]]; }
		fprintf(stderr,"Not found\n");
		return 0;
	}

};

int main() {
	size_t n[4]={random(),random(),random(),random()};
	Cuckoo<int,int,2> h(n);
	h.add(1,2);
	h.add(2,2);
	h.add(3,2);
	h.add(4,2);
	h.add(5,2);
	h.add(6,2);
	h.add(7,2);
	h.add(8,2);
	return 0;
}
