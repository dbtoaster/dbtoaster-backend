#include "mmap.hpp"

struct rec {
  rec():_1(0),_3(""),_2(0),_val(0){}
  rec(int _1, int _2=0, int _val=0, std::string _3="") { this->_1=_1; this->_2=_2; this->_3=_3; this->_val=_val; }
  int _1;
  std::string _3;
  int _2;
  int _val;
};
struct IndexFn1 {
  static HASH_RES_t hash(const rec& a) {
    return (HASH_RES_t)(a._1*1000+a._2);
  }
  static bool equals(const rec& a,const rec& b) { 
    return a._1==b._1 && a._2==b._2;
  }
};

struct IndexFn2 {
  static HASH_RES_t hash(const rec& a) {
    return (HASH_RES_t)a._1;
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

void test_hash(){
  rec r1(1,2,11);
  uint32_t h1_1 = MurmurHash2(&r1,sizeof(rec));
  std::cout << "h1_1 = " << h1_1 << std::endl;
  uint32_t h2_1 = MurmurHash2(&r1,sizeof(rec)-sizeof(((rec *)0)->_val));
  std::cout << "h2_1 = " << h2_1 << std::endl;
  uint32_t h3_1=0, carry_1=0;
  PMurHash32_Process(&h3_1, &carry_1, &(r1._1),sizeof(((rec *)0)->_1));
  std::cout << "  h3_1 = " << h3_1 << std::endl;
  PMurHash32_Process(&h3_1, &carry_1, &(r1._2),sizeof(((rec *)0)->_2));
  std::cout << "  h3_1 = " << h3_1 << std::endl;
  std::cout << "h3_1 = " << PMurHash32_Result(h3_1, carry_1, sizeof(((rec *)0)->_1)+sizeof(((rec *)0)->_2)) << std::endl;

  std::cout << std::endl;

  rec r2(1,2,28);
  uint32_t h1_2 = MurmurHash2(&r2,sizeof(rec));
  std::cout << "h1_2 = " << h1_2 << std::endl;
  uint32_t h2_2 = MurmurHash2(&r2,sizeof(rec)-sizeof(((rec *)0)->_val));
  std::cout << "h2_2 = " << h2_2 << std::endl;
  uint32_t h3_2=0, carry_2=0;
  PMurHash32_Process(&h3_2, &carry_2, &(r2._1),sizeof(((rec *)0)->_1));
  std::cout << "  h3_2 = " << h3_2 << std::endl;
  PMurHash32_Process(&h3_2, &carry_2, &(r2._2),sizeof(((rec *)0)->_2));
  std::cout << "  h3_2 = " << h3_2 << std::endl;
  std::cout << "h3_2 = " << PMurHash32_Result(h3_2, carry_2, sizeof(((rec *)0)->_1)+sizeof(((rec *)0)->_2)) << std::endl;
}


int main(int argc, char** argv) {
  std::cout << "test_pool()" << std::endl;
  test_pool();
  std::cout << "test_index()" << std::endl;
  test_index();
  std::cout << "test_map()" << std::endl;
  test_map();
  std::cout << "test_hash()" << std::endl;
  test_hash();
  std::cout << "All tests passes successfully :)" << std::endl;
  return 0;
}