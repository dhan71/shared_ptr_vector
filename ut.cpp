#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>

#include <iostream>
#include <shared_ptr_vector.h>
using namespace std;

class TObj
{
public:
  TObj()
    : iN(0)
    , iS("")
  {
    cout << "TObj default ctor called" << endl;
  }
  TObj(int a, const string& b)
    : iN(a)
    , iS(b)
  {
    cout << "TObj(" << a << "," << b << ") ctor called" << endl;
  }
  ~TObj()
  {
    cout << "TObj(" << iN << "," << iS << ") dtor called" << endl;
  }

public:
  int getN() const
  {
    return iN;
  }
  void setN(int a)
  {
    iN = a;
  }
  const string& getS() const
  {
    return iS;
  }
  void setS(const string& a)
  {
    iS = a;
  }

private:
  int    iN;
  string iS;
};
bool
operator==(const TObj& lhs, const TObj& rhs)
{
  return (lhs.getN() == rhs.getN()) &&
         (lhs.getS() == rhs.getS()) ;
}
bool
operator<(const TObj& lhs, const TObj& rhs)
{
  if (lhs.getN() < rhs.getN())
    return true;
  return lhs.getS() < rhs.getS();
}
ostream&
operator<<(ostream& os, const TObj& a)
{
  os << "(" << a.getN() << "," << a.getS() << ")";
  return os;
}

bool
int_less(int a, int b)
{
  return a < b;
}


class Tests : public CppUnit::TestFixture
{
public:
  void setUp()
  {
    //cout << "Tests::setUp called" << endl;
  }
  void tearDown()
  {
    //cout << "Tests::tearDown called" << endl;
  }

  void title(const char* h)
  {
    cout << "-------------------\n"
         << h << "\n"
         << "--------------------\n";
  }

public:
  void test_x1()
  {
    shared_ptr<int> sp1(nullptr);
    CPPUNIT_ASSERT(nullptr == sp1.get());
  }
  void test_x2()
  {
    int* i1 = new int(1);
    // pointer double use is an error
    return;
    shared_ptr<int> sp1(i1);
    shared_ptr<int> sp2(i1);
    CPPUNIT_ASSERT(i1 == sp1.get());
    CPPUNIT_ASSERT(i1 == sp2.get());
  }
  void test_x3()
  {
    int* i1 = new int(1);
    shared_ptr<int> sp1(i1);
    shared_ptr<int> sp2(sp1);
    CPPUNIT_ASSERT(i1 == sp1.get());
    CPPUNIT_ASSERT(i1 == sp2.get());

    TObj* t1 = new TObj(2, "TObj double use");
    shared_ptr<TObj> sp3(t1);
    shared_ptr<TObj> sp4(sp3);
    CPPUNIT_ASSERT(t1 == sp3.get());
    CPPUNIT_ASSERT(t1 == sp4.get());
  }
  void test_ctor1()
  {
    title("Tests::test_ctor1 called");
    shared_ptr_vector<int> v1;
    //CPPUNIT_ASSERT_EQUAL(0, v1.size());
    CPPUNIT_ASSERT(0 == v1.size());
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
  }
  void test_ctor2()
  {
    title("Tests::test_ctor2 called");
    shared_ptr_vector<int> v1;
    CPPUNIT_ASSERT(0 == v1.size());
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
    shared_ptr_vector<int> v2(v1);
    //CPPUNIT_ASSERT_EQUAL(0, v1.size());
    CPPUNIT_ASSERT(0 == v2.size());
    CPPUNIT_ASSERT_EQUAL(true, v2.empty());
  }
  void test_ctor3()
  {
    title("Tests::test_ctor3 called");
    shared_ptr_vector<int> v1(3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT(nullptr == v1.front());
    CPPUNIT_ASSERT(nullptr == v1.back());
  }
  void test_ctor4()
  {
    title("Tests::test_ctor4 called");
    int* i1 = new int(1);
    shared_ptr_vector<int> v1(3, i1);
    cout << "v1=" << v1 << endl;
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT(i1 == v1.front());
    CPPUNIT_ASSERT(i1 == v1.back());

    TObj* t1 = new TObj(3, "Three");
    shared_ptr_vector<TObj> v2(3, t1);
    cout << "v2=" << v2 << endl;
    CPPUNIT_ASSERT(3 == v2.size());
    CPPUNIT_ASSERT_EQUAL(false, v2.empty());
    CPPUNIT_ASSERT(t1 == v2.front());
    CPPUNIT_ASSERT(t1 == v2.back());
  }
  void test_ctor5()
  {
    title("Tests::test_ctor5 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    shared_ptr_vector<TObj> v1;
    v1.push_back(t1);
    v1.push_back(t2);
    v1.push_back(t3);
    cout << "v1=" << v1 << endl;

    shared_ptr_vector<TObj> v2(v1);
    CPPUNIT_ASSERT_EQUAL(v1.size(), v2.size());
    CPPUNIT_ASSERT(v1.front() == v2.front());
    CPPUNIT_ASSERT(v1.back() == v2.back());
    cout << "v2=" << v1 << endl;
  }
  void test_ctor6()
  {
    title("Tests::test_ctor6 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    initializer_list<TObj*> il{ t1, t2, t3};
    shared_ptr_vector<TObj> v1(il);
    cout << "v1=" << v1 << endl;
    cout << "v1.capacity=" << v1.capacity() << endl;

    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT(v1.front() == t1);
    CPPUNIT_ASSERT(v1.back() == t3);

    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");
    TObj* t6 = new TObj(6,"F");
    TObj* t7 = new TObj(7,"G");
    TObj* t8 = new TObj(8,"H");
    shared_ptr_vector<TObj> v2({t4, t5, t6, t7, t8});
    CPPUNIT_ASSERT(5 == v2.size());
    CPPUNIT_ASSERT(5 == v2.capacity());
    CPPUNIT_ASSERT(v2.front() == t4);
    CPPUNIT_ASSERT(v2.back() == t8);
  }
  void test_ctor7()
  {
    title("Tests::test_ctor7 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    initializer_list<TObj*> il{ t1, t2, t3, t4, t5};

    shared_ptr_vector<TObj> v1(il.begin(), il.end());
    cout << "v1=" << v1 << endl;
    cout << "v1.capacity=" << v1.capacity() << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(v1.front() == t1);
    CPPUNIT_ASSERT(v1.back() == t5);
  }

  void test_assign1()
  {
    title("Tests::test_assign1 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    shared_ptr_vector<TObj> v1{ t1, t2, t3, t4, t5};

    shared_ptr_vector<TObj> v2;
    v2 = v1;
    cout << "v1=" << v1 << endl;
    cout << "v2=" << v2 << endl;

    CPPUNIT_ASSERT_EQUAL(v1.size(), v2.size());
    CPPUNIT_ASSERT_EQUAL(v1.capacity(), v2.capacity());
    CPPUNIT_ASSERT(v1.capacity() == v2.capacity());
    CPPUNIT_ASSERT(v1.front() == v2.front());
    CPPUNIT_ASSERT(v1.back() == v2.back());
  }
  void test_assign2()
  {
    title("Tests::test_assign2 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    
    shared_ptr_vector<TObj> v2;
    v2 = shared_ptr_vector<TObj>{ t1, t2, t3, t4, t5};
    cout << "v2=" << v2 << endl;

    CPPUNIT_ASSERT(5 == v2.size());
    CPPUNIT_ASSERT(5 == v2.capacity());
    CPPUNIT_ASSERT(t1== v2.front());
    CPPUNIT_ASSERT(t5 == v2.back());
  }
  void test_assign3()
  {
    title("Tests::test_assign3 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    initializer_list il{t1, t2, t3, t4, t5};
    
    shared_ptr_vector<TObj> v1;
    v1 = il;
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(il.size() == v1.size());
    CPPUNIT_ASSERT(*il.begin() == v1.front());
    CPPUNIT_ASSERT(*(il.end()-1) == v1.back());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t5 == v1.back());
  }
  void test_assign4()
  {
    title("Tests::test_assign4 called");
    TObj* t1 = new TObj(1,"A");
    
    shared_ptr_vector<TObj> v1;
    v1.assign(5, t1);
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t1 == v1.back());
  }
  void test_assign5()
  {
    title("Tests::test_assign5 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    initializer_list il{t1, t2, t3, t4, t5};
    
    shared_ptr_vector<TObj> v1;
    v1.assign(il.begin(), il.end());
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(il.size() == v1.size());
    CPPUNIT_ASSERT(*il.begin() == v1.front());
    CPPUNIT_ASSERT(*(il.end()-1) == v1.back());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t5 == v1.back());
  }
  void test_assign6()
  {
    title("Tests::test_assign6 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    initializer_list il{t1, t2, t3, t4, t5};
    
    shared_ptr_vector<TObj> v1;
    v1.assign(il);
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(il.size() == v1.size());
    CPPUNIT_ASSERT(*il.begin() == v1.front());
    CPPUNIT_ASSERT(*(il.end()-1) == v1.back());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t5 == v1.back());
  }
  void test_begin1()
  {
    title("Tests::test_begin1 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t5 == v1.back());

    CPPUNIT_ASSERT(t1 == v1.begin()->get());
  }
  void test_end1()
  {
    title("Tests::test_end1 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t5 == v1.back());

    CPPUNIT_ASSERT(t5 == (v1.end()-1)->get());
  }
  void test_max_size()
  {
    title("Tests::test_max_size called");
    shared_ptr_vector<TObj> v1;
    cout << "v1=" << v1 << endl;
    cout << "v1.max_size()=" << v1.max_size() << endl;

    CPPUNIT_ASSERT(v1.iList.max_size() == v1.max_size());
    CPPUNIT_ASSERT(0 == v1.size());
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
  }
  void test_resize1()
  {
    title("Tests::test_resize1 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t5 == v1.back());

    v1.resize(3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t3 == v1.back());

    v1.resize(5);
    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(nullptr == v1.back());
  }
  void test_resize2()
  {
    title("Tests::test_resize2 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t5 == v1.back());

    v1.resize(3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t3 == v1.back());

    TObj* t6 = new TObj(6,"G");
    v1.resize(6, t6);
    v1.shrink_to_fit();
    cout << "resize v1=" << v1 << endl;
    CPPUNIT_ASSERT(6 == v1.size());
    CPPUNIT_ASSERT(6 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front());
    CPPUNIT_ASSERT(t6 == v1.back());
  }

  void test_aat1()
  {
    title("Tests::test_aat1 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1[0]);
    CPPUNIT_ASSERT(t2 == v1[1]);
    CPPUNIT_ASSERT(t3 == v1[2]);
    CPPUNIT_ASSERT(t4 == v1[3]);
    CPPUNIT_ASSERT(t5 == v1[4]);

    TObj* tt1 = v1[0];
    cout << " tt1=" << *tt1 << endl;
    tt1->setS("X");
    tt1->setN(100);
    cout << " tt1=" << *tt1 << endl;
  }
  void test_aat2()
  {
    title("Tests::test_aat2 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    TObj* t6 = new TObj(6,"G");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1[0]);
    CPPUNIT_ASSERT(t2 == v1[1]);
    CPPUNIT_ASSERT(t3 == v1[2]);
    CPPUNIT_ASSERT(t4 == v1[3]);
    CPPUNIT_ASSERT(t5 == v1[4]);

    v1.at(4, t6);
    cout << "v1=" << v1 << endl;
    CPPUNIT_ASSERT(t6 == v1[4]);
  }
  void test_at1()
  {
    title("Tests::test_at1 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1.at(0));
    CPPUNIT_ASSERT(t2 == v1.at(1));
    CPPUNIT_ASSERT(t3 == v1.at(2));
    CPPUNIT_ASSERT(t4 == v1.at(3));
    CPPUNIT_ASSERT(t5 == v1.at(4));
  }
  void test_at2()
  {
    title("Tests::test_at2 called");
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"F");
    TObj* t6 = new TObj(6,"G");
    
    shared_ptr_vector<TObj> v1{t1, t2, t3, t4, t5};
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1.at(0));
    CPPUNIT_ASSERT(t2 == v1.at(1));
    CPPUNIT_ASSERT(t3 == v1.at(2));
    CPPUNIT_ASSERT(t4 == v1.at(3));
    CPPUNIT_ASSERT(t5 == v1.at(4));

    v1.at(4, t6);
    cout << "v1=" << v1 << endl;
    CPPUNIT_ASSERT(t6 == v1.at(4));
  }

  void test_push1()
  {
    title("test_push1() called");
    shared_ptr_vector<int> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
    v1.push_back(1);
    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
  }
  void test_push2()
  {
    title("test_push2() called");
    shared_ptr_vector<int> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
    int* i1 = new int(1);
    v1.push_back(i1);
    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(i1, v1.front());
    CPPUNIT_ASSERT_EQUAL(i1, v1.back());
    CPPUNIT_ASSERT(i1 == v1.at(0));
    int* i2 = new int(2);
    v1.push_back(i2);
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i2, v1.back());
    CPPUNIT_ASSERT(i2 == v1.at(1));
  }
  void test_emplaceback1()
  {
    title("test_emplaceback1() called");
    vector<TObj> v1;
    v1.push_back(TObj(1,"A"));
    v1.emplace_back(2,"B");
    v1.emplace_back(3,"C");
    for (auto i : v1)
      cout << i << "\n";
    cout << endl;

    vector<int> v2;
    v2.push_back(1);
    v2.emplace_back(2);
    v2.emplace_back(3);
    for (auto i : v2)
      cout << i << "\n";
    cout << endl;
  }
  void test_emplaceback2()
  {
    title("test_emplaceback2() called");

    shared_ptr_vector<TObj> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

    TObj* r = v1.emplace_back(1, "A");
    cout << "r = " << *r << endl;

    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(1, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), v1.front()->getS());

    v1.emplace_back(2, "B");
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(2, v1.back()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), v1.back()->getS());
  }
  void test_emplace1()
  {
    title("test_emplace1() called");

    shared_ptr_vector<TObj> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

    TObj* r = v1.emplace_back(1, "A");
    cout << "r = " << *r << endl;

    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(1, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(1, r->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), r->getS());

    shared_ptr_vector<TObj>::iterator itr = v1.emplace(v1.begin(), 2, "B");
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(2, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(2, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), itr->get()->getS());

    itr = v1.emplace(v1.end(), 3, "C");
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(3, v1.back()->getN());
    CPPUNIT_ASSERT_EQUAL(string("C"), v1.back()->getS());
    CPPUNIT_ASSERT_EQUAL(3, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("C"), itr->get()->getS());
  }
  void test_insert1()
  {
    title("test_insert1() called");

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");

    shared_ptr_vector<TObj> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

    shared_ptr_vector<TObj>::iterator itr = v1.insert(v1.end(), t1);

    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(t1, itr->get());
    CPPUNIT_ASSERT_EQUAL(1, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(1, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), itr->get()->getS());

    itr = v1.insert(v1.begin(), t2);
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(t2, itr->get());
    CPPUNIT_ASSERT_EQUAL(2, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(2, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), itr->get()->getS());

    itr = v1.insert(v1.end(), t3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(t3, itr->get());
    CPPUNIT_ASSERT_EQUAL(3, v1.back()->getN());
    CPPUNIT_ASSERT_EQUAL(string("C"), v1.back()->getS());
    CPPUNIT_ASSERT_EQUAL(3, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("C"), itr->get()->getS());
  }
  void test_insert2()
  {
    title("test_insert2() called");

//  TObj* t1 = new TObj(1,"A");
//  TObj* t2 = new TObj(2,"B");
//  TObj* t3 = new TObj(3,"C");

    shared_ptr_vector<TObj> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

    shared_ptr_vector<TObj>::iterator itr = v1.insert(v1.end(), new TObj(1,"A"));

    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(1, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(1, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), itr->get()->getS());

    itr = v1.insert(v1.begin(), new TObj(2,"B"));
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(2, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(2, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), itr->get()->getS());

    itr = v1.insert(v1.end(), new TObj(3,"C"));
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(3, v1.back()->getN());
    CPPUNIT_ASSERT_EQUAL(string("C"), v1.back()->getS());
    CPPUNIT_ASSERT_EQUAL(3, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("C"), itr->get()->getS());
  }
  void test_insert3()
  {
    title("test_insert3() called");

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");

    vector<TObj*> v2{t1,t2,t3};
    shared_ptr_vector<TObj> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

//  shared_ptr_vector<TObj>::iterator itr = v1.insert(v1.end(), v2.begin(), v2.end());
//  shared_ptr_vector<TObj>::iterator itr = v1.insert(v1.begin(), v2.begin(), v2.end());
    shared_ptr_vector<TObj>::iterator itr = v1.insert(v1.end(), {t1,t2,t3});
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT(itr == v1.begin());
    CPPUNIT_ASSERT_EQUAL(t1, itr->get());
    CPPUNIT_ASSERT_EQUAL(1, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(1, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), itr->get()->getS());
  }
  void test_insert4()
  {
    title("test_insert4() called");

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
//  TObj* t3 = new TObj(3,"C");

    shared_ptr_vector<TObj> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

//  shared_ptr_vector<TObj>::iterator itr = v1.insert(v1.end(), {t1,t2,t3});
    shared_ptr_vector<TObj>::iterator itr = v1.insert(v1.end(), 3, t1);
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT(itr == v1.begin());
    CPPUNIT_ASSERT_EQUAL(t1, itr->get());
    CPPUNIT_ASSERT_EQUAL(1, v1.front()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), v1.front()->getS());
    CPPUNIT_ASSERT_EQUAL(1, itr->get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), itr->get()->getS());
    CPPUNIT_ASSERT_EQUAL(v1[0], v1[1]);

    itr = v1.insert(v1.end(), 3, t2);
    CPPUNIT_ASSERT(itr == (v1.begin() + 3));
    CPPUNIT_ASSERT(t2 == v1[4]);
    CPPUNIT_ASSERT_EQUAL(v1[3], v1[4]);
  }
  void test_erase1()
  {
    title("test_erase1() called");

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");

    shared_ptr_vector<TObj> v1{t1,t2,t3,t4,t5};
    cout << "v1=" << v1 << endl;
    cout << "t1=" << t1 << endl;
    cout << "t2=" << t2 << endl;
    cout << "t3=" << t3 << endl;
    cout << "t4=" << t4 << endl;
    cout << "t5=" << t5 << endl;

    shared_ptr_vector<TObj>::iterator itr = v1.erase(v1.end());
    cout << "after erase end: v1=" << v1 << endl;
    cout << "itr->get()=" << itr->get() << endl;
    CPPUNIT_ASSERT(4 == v1.size());

    itr = v1.erase(v1.begin());
    cout << "after erase begin: v1=" << v1 << endl;
    cout << "itr->get()=" << itr->get() << endl;
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT(itr == v1.begin());

    itr = v1.erase(v1.begin());
    cout << "after erase begin: v1=" << v1 << endl;
    cout << "itr->get()=" << itr->get() << endl;
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT(itr == v1.begin());

    itr = v1.erase(v1.begin());
    cout << "after erase begin: v1=" << v1 << endl;
    cout << "itr->get()=" << itr->get() << endl;
    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT(itr == v1.begin());
  }
  void test_erase2()
  {
    title("test_erase2() called");

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");

    shared_ptr_vector<TObj> v1{t1,t2,t3,t4,t5};
    cout << "v1=" << v1 << endl;
    cout << "t1=" << t1 << endl;
    cout << "t2=" << t2 << endl;
    cout << "t3=" << t3 << endl;
    cout << "t4=" << t4 << endl;
    cout << "t5=" << t5 << endl;

    shared_ptr_vector<TObj>::iterator itr = v1.erase(v1.end(), v1.end());
    cout << "after erase end: v1=" << v1 << endl;
    cout << "itr->get()=" << itr->get() << endl;
    CPPUNIT_ASSERT(5 == v1.size());

    itr = v1.erase(v1.begin(), v1.begin());
    cout << "after erase begin: v1=" << v1 << endl;
    cout << "itr->get()=" << itr->get() << endl;
    CPPUNIT_ASSERT(5 == v1.size());

    itr = v1.erase(v1.begin()+1, v1.end()-1);
    cout << "after erase begin: v1=" << v1 << endl;
    cout << "itr->get()=" << itr->get() << endl;
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT(itr == (v1.end()-1));
  }
  void test_swap()
  {
    title("test_swap() called");

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");

    shared_ptr_vector<TObj> v1{t1,t2,t3,t4,t5};
    cout << "v1=" << v1 << endl;

    shared_ptr_vector<TObj> v2;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(0 == v2.size());

    v1.swap(v2);
    cout << "v1=" << v1 << endl;
    cout << "v2=" << v2 << endl;

    CPPUNIT_ASSERT(0 == v1.size());
    CPPUNIT_ASSERT(5 == v2.size());

    swap(v1, v2);
    cout << "v1=" << v1 << endl;
    cout << "v2=" << v2 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(0 == v2.size());
  }

  void test_pop1()
  {
    title("test_pop1() called");
    shared_ptr_vector<int> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

    int* i1 = new int(1);
    v1.push_back(i1);
    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(i1, v1.front());
    CPPUNIT_ASSERT_EQUAL(i1, v1.back());
    CPPUNIT_ASSERT(i1 == v1.at(0));

    int* i2 = new int(2);
    v1.push_back(i2);
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i2, v1.back());
    CPPUNIT_ASSERT(i2 == v1.at(1));

    int* i3 = new int(3);
    v1.push_back(i3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i3, v1.back());
    CPPUNIT_ASSERT(i3 == v1.at(2));

    int* r_i3 = v1.back();
    CPPUNIT_ASSERT_EQUAL(i3, r_i3);
    v1.pop_back();
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i2, v1.back());
    CPPUNIT_ASSERT(i2 == v1.at(1));
  }

  void test_eq()
  {
    title("test_eq() called");

    vector<int> i1;
    vector<int> i2;

    shared_ptr_vector<int> v1;
    shared_ptr_vector<int> v2;
    CPPUNIT_ASSERT(v1 == v2);
    CPPUNIT_ASSERT(i1 == i2);
    CPPUNIT_ASSERT_EQUAL(i1 == i2, v1 == v2);

    i1.push_back(1);
    i1.push_back(2);
    i1.push_back(3);
    v1.push_back(new int(1));
    v1.push_back(new int(2));
    v1.push_back(new int(3));
    cout << "v1=" << v1 << endl;

    i2.push_back(1);
    i2.push_back(2);
    i2.push_back(3);
    v2.push_back(new int(1));
    v2.push_back(new int(2));
    v2.push_back(new int(3));
    cout << "v2=" << v2 << endl;

    CPPUNIT_ASSERT(v1 == v2);
    CPPUNIT_ASSERT_EQUAL(i1 == i2, v1 == v2);

    i2.push_back(4);
    v2.push_back(new int(4));
    CPPUNIT_ASSERT( (v1 != v2) );
    CPPUNIT_ASSERT( (i1 != i2) );
    CPPUNIT_ASSERT_EQUAL(i1 != i2, v1 != v2);
  }
  void test_less()
  {
    title("test_less() called");

    vector<int> i1;
    vector<int> i2;

    shared_ptr_vector<int> v1;
    shared_ptr_vector<int> v2;
    CPPUNIT_ASSERT( !(v1 < v2) );
    CPPUNIT_ASSERT( !(v1 > v2) );
    CPPUNIT_ASSERT( !(i1 < i2) );
    CPPUNIT_ASSERT( !(i1 > i2) );
    CPPUNIT_ASSERT_EQUAL(i1 < i2, v1 < v2);
    CPPUNIT_ASSERT_EQUAL(i1 > i2, v1 > v2);

    i1.push_back(1);
    i1.push_back(2);
    i1.push_back(3);
    v1.push_back(new int(1));
    v1.push_back(new int(2));
    v1.push_back(new int(3));
    cout << "v1=" << v1 << endl;

    i2.push_back(1);
    i2.push_back(2);
    i2.push_back(3);
    v2.push_back(new int(1));
    v2.push_back(new int(2));
    v2.push_back(new int(3));
    cout << "v2=" << v2 << endl;

    CPPUNIT_ASSERT( !(v1 < v2) );
    CPPUNIT_ASSERT( !(i1 < i2) );
    CPPUNIT_ASSERT( !(v1 > v2) );
    CPPUNIT_ASSERT( !(i1 > i2) );
    CPPUNIT_ASSERT_EQUAL(i1 < i2, v1 < v2);
    CPPUNIT_ASSERT_EQUAL(i1 > i2, v1 > v2);

    i2.push_back(4);
    v2.push_back(new int(4));
    CPPUNIT_ASSERT(v1 < v2);
    CPPUNIT_ASSERT(i1 < i2);
    CPPUNIT_ASSERT(v2 > v1);
    CPPUNIT_ASSERT(i2 > i1);

    CPPUNIT_ASSERT_EQUAL(i1 < i2, v1 < v2);
    CPPUNIT_ASSERT_EQUAL(i1 > i2, v1 > v2);
  }

  void test_str()
  {
    title("test_str() called");
    shared_ptr_vector<int> v1;
    v1.push_back(new int(1));
    v1.push_back(new int(2));
    v1.push_back(new int(3));
    v1.push_back(nullptr);
    string s = to_string(v1);
    cout << "to_string(v1)=" << s << endl;
    CPPUNIT_ASSERT("[ 1 2 3 NULL ]" == s);

    shared_ptr_vector<TObj> v2;
    v2.push_back(new TObj(1, "A"));
    v2.push_back(new TObj(2, "B"));
    v2.push_back(new TObj(3, "C"));
    v2.push_back(nullptr);
    s = to_string(v2);
    cout << "to_string(v2)=" << s << endl;
    CPPUNIT_ASSERT("[ (1,A) (2,B) (3,C) NULL ]" == s);
    cout << "v1=" << v1 << endl;
    cout << "v2=" << v2 << endl;
  }

  void test_loop1()
  {
    title("test_loop1() called");

    shared_ptr_vector<int> v1;
    v1.push_back(new int(1));
    v1.push_back(new int(2));
    v1.push_back(nullptr);
    v1.push_back(new int(3));
    cout << "v1=" << v1 << endl;

    for (auto p : v1)
    {
      if (p)
        cout << *p << " ";
      else
        cout << "NULL ";
    }
    cout << endl;
    for (auto i = v1.begin(); i != v1.end(); ++i)
    {
      if (*i)
        cout << **i << " ";
      else
        cout << "NULL ";
    }
    cout << endl;
    for (auto i = v1.begin(); i != v1.end(); ++i)
    {
      int* p = i->get();
      if (p)
        cout << *p << " ";
      else
        cout << "NULL ";
    }
    cout << endl;
  }
  void test_sort1()
  {
    title("test_sort1() called");

    shared_ptr_vector<int> v1;
    v1.push_back(new int(2));
    v1.push_back(new int(5));
    v1.push_back(new int(3));
    v1.push_back(new int(1));
    v1.push_back(new int(4));
    cout << "before sort: v1=" << v1 << endl;

    //sort(v1);
    v1.sort();

    cout << "after sort: v1=" << v1 << endl;
    string sorted_v = to_string(v1);
    CPPUNIT_ASSERT("[ 1 2 3 4 5 ]" == sorted_v);

    TObj* t1 = new TObj(5,"H");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(3,"D");
    TObj* t5 = new TObj(1,"A");
    shared_ptr_vector<TObj> v2{t1,t2,t3,t4,t5};
    cout << "before sort: v2=" << v2 << endl;
    //sort(v2);
    v2.sort();
    cout << "after sort: v2=" << v2 << endl;
  }
  void test_sort2()
  {
    title("test_sort2() called");

    shared_ptr_vector<int> v1;
    v1.push_back(nullptr);
    v1.push_back(new int(2));
    v1.push_back(new int(5));
    v1.push_back(new int(3));
    v1.push_back(new int(1));
    v1.push_back(new int(4));
    cout << "before sort: v1=" << v1 << endl;

    sort(v1);

    cout << "after sort: v1=" << v1 << endl;
    string sorted_v = to_string(v1);
    CPPUNIT_ASSERT("[ 1 2 3 4 5 NULL ]" == sorted_v);

    TObj* t1 = new TObj(5,"H");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(3,"D");
    TObj* t5 = new TObj(1,"A");
    TObj* t6 = nullptr;
    shared_ptr_vector<TObj> v2{t6,t1,t2,t3,t4,t5};
    cout << "before sort: v2=" << v2 << endl;
    sort(v2);
    cout << "after sort: v2=" << v2 << endl;
  }
  void test_sort3()
  {
    title("test_sort3() called");

    shared_ptr_vector<int> v1;
    v1.push_back(new int(2));
    v1.push_back(new int(5));
    v1.push_back(new int(3));
    v1.push_back(new int(1));
    v1.push_back(new int(4));
    cout << "before sort: v1=" << v1 << endl;

    v1.sort();

    cout << "after sort: v1=" << v1 << endl;
    string sorted_v = to_string(v1);
    CPPUNIT_ASSERT("[ 1 2 3 4 5 ]" == sorted_v);

    /*
    TObj* t1 = new TObj(5,"H");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(3,"D");
    TObj* t5 = new TObj(1,"A");
    TObj* t6 = nullptr;
    shared_ptr_vector<TObj> v2{t6,t1,t2,t3,t4,t5};
    cout << "before sort: v2=" << v2 << endl;
    sort(v2);
    cout << "after sort: v2=" << v2 << endl;
    */
  }
  void test_find1()
  {
    title("test_find1() called");

    int* i1 = new int(1);
    int* i2 = new int(2);
    int* i3 = new int(3);
    int* i4 = new int(4);
    int* i5 = new int(5);
    int* i6 = new int(6);

    shared_ptr_vector<int> v1{i1,i2,i3,i4,i5};
    cout << "v1=" << v1 << endl;

    shared_ptr_vector<int>::iterator itr = v1.find(i3);
    CPPUNIT_ASSERT(itr != v1.end());
    CPPUNIT_ASSERT(itr == (v1.begin()+2));

    itr = v1.find(i6);
    CPPUNIT_ASSERT(itr == v1.end());

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");
    TObj* t6 = new TObj(6,"F");
    TObj* t7 = nullptr;
    shared_ptr_vector<TObj> v2{t1,t2,t3,t4,t5,t7};
    cout << "v2=" << v2 << endl;

    shared_ptr_vector<TObj>::iterator itr2 = v2.find(t3);
    CPPUNIT_ASSERT(itr2 != v2.end());
    CPPUNIT_ASSERT(itr2 == (v2.begin()+2));

    itr2 = v2.find(t6);
    CPPUNIT_ASSERT(itr2 == v2.end());
    itr2 = v2.find(nullptr);
    CPPUNIT_ASSERT(itr2 == (v2.end()-1));
  }
  void test_find2()
  {
    title("test_find2() called");

    int* i1 = new int(1);
    int* i2 = new int(2);
    int* i3 = new int(3);
    int* i4 = new int(4);
    int* i5 = new int(5);
    int* i6 = new int(6);

    shared_ptr_vector<int> v1{i1,i2,i3,i4,i5,nullptr};
    cout << "v1=" << v1 << endl;

    shared_ptr_vector<int>::iterator itr = v1.find_value(i3);
    CPPUNIT_ASSERT(itr != v1.end());
    CPPUNIT_ASSERT(itr == (v1.begin()+2));

    itr = v1.find_value(i6);
    CPPUNIT_ASSERT(itr == v1.end());
    itr = v1.find_value(nullptr);
    CPPUNIT_ASSERT(itr == v1.end());

    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");
    TObj* t6 = new TObj(6,"F");
    shared_ptr_vector<TObj> v2{t1,t2,t3,t4,t5,nullptr};
    cout << "v2=" << v2 << endl;

    shared_ptr_vector<TObj>::iterator itr2 = v2.find_value(t3);
    CPPUNIT_ASSERT(itr2 != v2.end());
    CPPUNIT_ASSERT(itr2 == (v2.begin()+2));

    itr2 = v2.find_value(t6);
    CPPUNIT_ASSERT(itr2 == v2.end());
    itr2 = v2.find_value(nullptr);
    CPPUNIT_ASSERT(itr2 == v2.end());
  }
  void test_find3()
  {
    title("test_find3() called");

    int* i1 = new int(1);
    int* i2 = new int(2);
    int* i3 = new int(3);
    int* i4 = new int(4);
    int* i5 = new int(5);
    int* i6 = new int(6);

    shared_ptr_vector<int> v1{i1,i2,nullptr,i3,i4,i5,i6};
    cout << "v1=" << v1 << endl;

    struct FindInt
    {
      FindInt(int a)
        : __n(a)
      { }
      bool operator()(const int& a) const
      {
        return (a%__n) == 0;
      }
      private:
      int __n;
    };
    //shared_ptr_vector<int>::iterator itr = v1.find_if_value(i3, [](const int& a){return (a%5) == 0;});
    shared_ptr_vector<int>::iterator itr = v1.find_if_value(FindInt(5));
    CPPUNIT_ASSERT(itr != v1.end());
    CPPUNIT_ASSERT(**itr == 5);

    itr = v1.find_if_value(FindInt(8));
    CPPUNIT_ASSERT(itr == v1.end());

    struct FindObj
    {
      FindObj(int a)
        : __n(a)
      { }
      bool operator()(const TObj& a) const
      {
        return (a.getN()%__n) == 0;
      }
      private:
      int __n;
    };
    TObj* t1 = new TObj(1,"A");
    TObj* t2 = new TObj(2,"B");
    TObj* t3 = new TObj(3,"C");
    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");
    TObj* t6 = new TObj(6,"F");
    shared_ptr_vector<TObj> v2{t1,t2,nullptr,t3,t4,t5,t6};
    cout << "v2=" << v2 << endl;

    shared_ptr_vector<TObj>::iterator itr2 = v2.find_if_value(FindObj(5));
    CPPUNIT_ASSERT(itr2 != v2.end());
    CPPUNIT_ASSERT((*itr2)->getN() == 5);
    cout << "FindObj(5) : " << **itr2 << endl;

    itr2 = v2.find_if_value(FindObj(8));
    CPPUNIT_ASSERT(itr2 == v2.end());
  }

  template<typename IteratorType>
  void iteratorTraitsTest(IteratorType it)
  {
    typename std::iterator_traits<IteratorType>::value_type temp = *it;
    std::cout << temp << std::endl;
  }

  void test_iter1()
  {
    title("test_iter1() called");

    vector<int> v1{1,2,3};
    Tests::iteratorTraitsTest(v1.begin());

    int* i3 = new int(3);
    int* i2 = new int(2);
    int* i1 = new int(1);
    shared_ptr_vector<int> v2 { i3, i2, i1 };
    Tests::iteratorTraitsTest(v2.begin());

    std::sort(v2.begin(), v2.end());
    cout << "v2 = " << v2 << endl;

    bool r = (v2.begin()+0) < (v2.begin() + 1);
    cout << " (v2.begin()+0) < (v2.begin() + 1):" << r << endl;
    r = (v2.begin()+1) < (v2.begin() + 0);
    cout << " (v2.begin()+1) < (v2.begin() + 0):" << r << endl;
  }

public:
  static CppUnit::Test* suite()
  {
    CppUnit::TestSuite* s = new CppUnit::TestSuite(" Test Test ");

    s->addTest(new CppUnit::TestCaller<Tests>("test_x1", &Tests::test_x1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_x2", &Tests::test_x2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_x3", &Tests::test_x3));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor1", &Tests::test_ctor1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor2", &Tests::test_ctor2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor3", &Tests::test_ctor3));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor4", &Tests::test_ctor4));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor5", &Tests::test_ctor5));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor6", &Tests::test_ctor6));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor7", &Tests::test_ctor7));
    s->addTest(new CppUnit::TestCaller<Tests>("test_assign1", &Tests::test_assign1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_assign2", &Tests::test_assign2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_assign3", &Tests::test_assign3));
    s->addTest(new CppUnit::TestCaller<Tests>("test_assign4", &Tests::test_assign4));
    s->addTest(new CppUnit::TestCaller<Tests>("test_assign5", &Tests::test_assign5));
    s->addTest(new CppUnit::TestCaller<Tests>("test_assign6", &Tests::test_assign6));
    s->addTest(new CppUnit::TestCaller<Tests>("test_begin1", &Tests::test_begin1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_end1", &Tests::test_end1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_max_size", &Tests::test_max_size));
    s->addTest(new CppUnit::TestCaller<Tests>("test_resize1", &Tests::test_resize1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_resize2", &Tests::test_resize2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_aat1", &Tests::test_aat1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_aat2", &Tests::test_aat2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_at1", &Tests::test_at1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_at2", &Tests::test_at2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_push1", &Tests::test_push1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_push2", &Tests::test_push2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_emplaceback1", &Tests::test_emplaceback1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_emplaceback2", &Tests::test_emplaceback2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_emplace1", &Tests::test_emplace1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_insert1", &Tests::test_insert1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_insert2", &Tests::test_insert2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_insert3", &Tests::test_insert3));
    s->addTest(new CppUnit::TestCaller<Tests>("test_insert4", &Tests::test_insert4));
    s->addTest(new CppUnit::TestCaller<Tests>("test_erase1", &Tests::test_erase1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_erase2", &Tests::test_erase2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_swap", &Tests::test_swap));
    s->addTest(new CppUnit::TestCaller<Tests>("test_pop1", &Tests::test_pop1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_eq", &Tests::test_eq));
    s->addTest(new CppUnit::TestCaller<Tests>("test_less", &Tests::test_less));
    s->addTest(new CppUnit::TestCaller<Tests>("test_str", &Tests::test_str));
    s->addTest(new CppUnit::TestCaller<Tests>("test_loop1", &Tests::test_loop1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_sort1", &Tests::test_sort1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_sort2", &Tests::test_sort2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_sort3", &Tests::test_sort3));
    s->addTest(new CppUnit::TestCaller<Tests>("test_find1", &Tests::test_find1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_find2", &Tests::test_find2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_find3", &Tests::test_find3));

    s->addTest(new CppUnit::TestCaller<Tests>("test_iter1", &Tests::test_iter1));

    return s;
  }
};

int
main()//int argc, char* argv[])
{
  CppUnit::TextTestRunner r;
  r.addTest(Tests::suite());
  r.run();
  return 0;
}

