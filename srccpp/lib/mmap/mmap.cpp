#include "mmap.hpp"

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
  struct rec {
    rec():_1(0),_2(0){}
    rec(int _1, int _2) { this->_1=_1; this->_2=_2; }
    int _1, _2;
  };
  int i=7;
  auto eq_check1 = [&] (const rec& a, const rec& b) { return a._1==b._1 && i==7; };
  auto hsh1 = [] (const rec& a) { return (long)a._1; };
  HashIndex<rec> index(hsh1,eq_check1);

  rec r1(1,2);
  rec r2(2,3);
  rec r3(3,4);
  rec r3_v2(3,4);
  index.add(r1);
  index.add(r2);
  index.add(r3);
  assert(index.count()==3);
  //index.foreach([] (const rec& a) { printf(" - %d %d\n", a._1, a._2); });
  index.del(r3_v2);
  assert(index.count()==2);

  assert(eq_check1(*(index.get(rec(1,5))),rec(1,2)));
}

void test_map() {
  struct rec {
    rec():_1(0),_2(0){}
    rec(int _1, int _2) { this->_1=_1; this->_2=_2; }
    int _1, _2;
  };
  int i=7;
  auto eq_check1 = [&] (const rec& a, const rec& b) { return a._1==b._1 && i==7; };
  auto hsh1 = [] (const rec& a) { return (long)a._1; };
  HashIndex<rec> index1(hsh1,eq_check1);
  HashIndex<rec> idxs[] = { std::move(index1) };
  MultiHashMap<rec,1> hmap(idxs);
  hmap.add(rec(1,2));
  hmap.add(rec(2,3));
  hmap.add(rec(3,4));
  assert(hmap.count()==3);
  //hmap.foreach([] (const rec& a) { printf(" - %d %d\n", a._1, a._2); });
  hmap.del(rec(3,4));
  assert(hmap.count()==2);

  assert(eq_check1(*hmap.get(0,rec(1,5)),rec(1,2)));
}

int main(int argc, char** argv) {
  test_pool();
  test_index();
  test_map();
  std::cout << "All tests passes successfully :)" << std::endl;
  return 0;
}