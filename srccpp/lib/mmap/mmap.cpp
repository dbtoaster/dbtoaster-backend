#include "mmap.hpp"

struct rec {
  rec():_1(0),_2(0),_val(0){}
  rec(int _1, int _2=0, int _val=0) { this->_1=_1; this->_2=_2; this->_val=_val; }
  int _1, _2,_val;
};
struct IndexFn1 {
  static long hash(const rec& a) {
    return (long)(a._1*1000+a._2);
  }
  static bool equals(const rec& a,const rec& b) { 
    return a._1==b._1 && a._2==b._2;
  }
};

struct IndexFn2 {
  static long hash(const rec& a) {
    return (long)a._1;;
  }
  static bool equals(const rec& a,const rec& b) { 
    return a._1==b._1;
  }
};

void test_pool() {
  const int num = 100;
  Pool<int> pool(2);
  int* d = new int[num];
  int** p = new int*[num];
  for (int i=0;i<num;++i) {
    d[i] = i;
    p[i] = pool.add();
    *(p[i]) = i;
  }
  for (int i=0;i<num;++i) {
    assert(d[i] == *(p[i]));
    pool.del(p[i]);
  }
  delete[] d;
  delete[] p;
}

void test_index() {
  HashIndex<rec,IndexFn1> index;

  rec r1(1,2,11);
  rec r2(2,3,12);
  rec r3(3,4,13);
  rec r3_v2(3,4);
  index.add(r1);
  index.add(r2);
  index.add(r3);
  assert(index.count()==3);
  index.foreach([] (const rec& a) { printf(" - %d %d\n", a._1, a._2); });
  index.del(r3_v2);
  assert(index.count()==2);

  assert(IndexFn1::equals(*(index.get(rec(1,2))),rec(1,2)));
}

void test_map() {
  std::cout << "- hmap1" << std::endl;
  MultiHashMap<rec,HashIndex<rec,IndexFn1>,HashIndex<rec,IndexFn2>> hmap1;
  hmap1.add(rec(1,2,11));
  hmap1.add(rec(1,6,12));
  hmap1.add(rec(2,3,13));
  hmap1.add(rec(3,4,14));
  assert(hmap1.count()==4);
  // hmap1.foreach([] (const rec& a) { printf(" - %d -> %d\n", a._1, a._2); });
  hmap1.slice(1,rec(1),[] (const rec& a) { printf(" - %d -> %d\n", a._1, a._2); });
  hmap1.del(rec(3,4));
  assert(hmap1.count()==3);
  assert(IndexFn1::equals(*hmap1.get(rec(1),1),rec(1,2)));

  std::cout << "- hmap2" << std::endl;
  MultiHashMap<rec,HashIndex<rec,IndexFn1>,HashIndex<rec,IndexFn2>> hmap2(hmap1);
  assert(IndexFn1::equals(*hmap2.get(rec(1),1),rec(1,2)));
  assert(hmap2.count()==3);
  // hmap2.foreach([] (const rec& a) { printf(" - %d -> %d\n", a._1, a._2); });
  hmap2.slice(1,rec(1),[] (const rec& a) { printf(" - %d -> %d\n", a._1, a._2); });
}

int main(int argc, char** argv) {
  std::cout << "test_pool()" << std::endl;
  test_pool();
  std::cout << "test_index()" << std::endl;
  test_index();
  std::cout << "test_map()" << std::endl;
  test_map();
  std::cout << "All tests passes successfully :)" << std::endl;
  return 0;
}