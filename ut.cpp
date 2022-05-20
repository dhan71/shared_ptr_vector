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
  void setS(int a)
  {
    iS = a;
  }

private:
  int    iN;
  string iS;
};
ostream&
operator<<(ostream& os, const TObj& a)
{
  os << "(" << a.getN() << "," << a.getS() << ")";
  return os;
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
    CPPUNIT_ASSERT(nullptr == v1.front().get());
    CPPUNIT_ASSERT(nullptr == v1.back().get());
  }
  void test_ctor4()
  {
    title("Tests::test_ctor4 called");
    int* i1 = new int(1);
    shared_ptr_vector<int> v1(3, i1);
    cout << "v1=" << v1 << endl;
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT(i1 == v1.front().get());
    CPPUNIT_ASSERT(i1 == v1.back().get());

    TObj* t1 = new TObj(3, "Three");
    shared_ptr_vector<TObj> v2(3, t1);
    cout << "v2=" << v2 << endl;
    CPPUNIT_ASSERT(3 == v2.size());
    CPPUNIT_ASSERT_EQUAL(false, v2.empty());
    CPPUNIT_ASSERT(t1 == v2.front().get());
    CPPUNIT_ASSERT(t1 == v2.back().get());
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
    CPPUNIT_ASSERT(v1.front().get() == v2.front().get());
    CPPUNIT_ASSERT(v1.back().get() == v2.back().get());
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
    CPPUNIT_ASSERT(v1.front().get() == t1);
    CPPUNIT_ASSERT(v1.back().get() == t3);

    TObj* t4 = new TObj(4,"D");
    TObj* t5 = new TObj(5,"E");
    TObj* t6 = new TObj(6,"F");
    TObj* t7 = new TObj(7,"G");
    TObj* t8 = new TObj(8,"H");
    shared_ptr_vector<TObj> v2({t4, t5, t6, t7, t8});
    CPPUNIT_ASSERT(5 == v2.size());
    CPPUNIT_ASSERT(5 == v2.capacity());
    CPPUNIT_ASSERT(v2.front().get() == t4);
    CPPUNIT_ASSERT(v2.back().get() == t8);
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
    CPPUNIT_ASSERT(v1.front().get() == t1);
    CPPUNIT_ASSERT(v1.back().get() == t5);
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
    CPPUNIT_ASSERT(v1.front().get() == v2.front().get());
    CPPUNIT_ASSERT(v1.back().get() == v2.back().get());
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
    CPPUNIT_ASSERT(t1== v2.front().get());
    CPPUNIT_ASSERT(t5 == v2.back().get());
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
    CPPUNIT_ASSERT(*il.begin() == v1.front().get());
    CPPUNIT_ASSERT(*(il.end()-1) == v1.back().get());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t5 == v1.back().get());
  }
  void test_assign4()
  {
    title("Tests::test_assign4 called");
    TObj* t1 = new TObj(1,"A");
    
    shared_ptr_vector<TObj> v1;
    v1.assign(5, t1);
    cout << "v1=" << v1 << endl;

    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t1 == v1.back().get());
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
    CPPUNIT_ASSERT(*il.begin() == v1.front().get());
    CPPUNIT_ASSERT(*(il.end()-1) == v1.back().get());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t5 == v1.back().get());
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
    CPPUNIT_ASSERT(*il.begin() == v1.front().get());
    CPPUNIT_ASSERT(*(il.end()-1) == v1.back().get());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t5 == v1.back().get());
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
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t5 == v1.back().get());

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
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t5 == v1.back().get());

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
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t5 == v1.back().get());

    v1.resize(3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t3 == v1.back().get());

    v1.resize(5);
    CPPUNIT_ASSERT(5 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(nullptr == v1.back().get());
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
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t5 == v1.back().get());

    v1.resize(3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT(5 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t3 == v1.back().get());

    TObj* t6 = new TObj(6,"G");
    v1.resize(6, t6);
    v1.shrink_to_fit();
    cout << "resize v1=" << v1 << endl;
    CPPUNIT_ASSERT(6 == v1.size());
    CPPUNIT_ASSERT(6 == v1.capacity());
    CPPUNIT_ASSERT(t1 == v1.front().get());
    CPPUNIT_ASSERT(t6 == v1.back().get());
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
    CPPUNIT_ASSERT(t1 == v1[0].get());
    CPPUNIT_ASSERT(t2 == v1[1].get());
    CPPUNIT_ASSERT(t3 == v1[2].get());
    CPPUNIT_ASSERT(t4 == v1[3].get());
    CPPUNIT_ASSERT(t5 == v1[4].get());
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
    CPPUNIT_ASSERT(t1 == v1[0].get());
    CPPUNIT_ASSERT(t2 == v1[1].get());
    CPPUNIT_ASSERT(t3 == v1[2].get());
    CPPUNIT_ASSERT(t4 == v1[3].get());
    CPPUNIT_ASSERT(t5 == v1[4].get());

    v1[4] = shared_ptr_vector<TObj>::shared_data_type(t6);
    cout << "v1=" << v1 << endl;
    CPPUNIT_ASSERT(t6 == v1[4].get());
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
    CPPUNIT_ASSERT(t1 == v1.at(0).get());
    CPPUNIT_ASSERT(t2 == v1.at(1).get());
    CPPUNIT_ASSERT(t3 == v1.at(2).get());
    CPPUNIT_ASSERT(t4 == v1.at(3).get());
    CPPUNIT_ASSERT(t5 == v1.at(4).get());
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
    CPPUNIT_ASSERT(t1 == v1.at(0).get());
    CPPUNIT_ASSERT(t2 == v1.at(1).get());
    CPPUNIT_ASSERT(t3 == v1.at(2).get());
    CPPUNIT_ASSERT(t4 == v1.at(3).get());
    CPPUNIT_ASSERT(t5 == v1.at(4).get());

    v1.at(4, t6);
    cout << "v1=" << v1 << endl;
    CPPUNIT_ASSERT(t6 == v1.at(4).get());
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
    CPPUNIT_ASSERT_EQUAL(i1, v1.front().get());
    CPPUNIT_ASSERT_EQUAL(i1, v1.back().get());
    CPPUNIT_ASSERT_EQUAL(i1, v1.at(0).get());
    int* i2 = new int(2);
    v1.push_back(i2);
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i2, v1.back().get());
    CPPUNIT_ASSERT_EQUAL(i2, v1.at(1).get());
  }
  /* do not use emplace function
  void test_emplaceback1()
  {
    title("test_emplaceback1() called");
    shared_ptr_vector<TObj> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

    //TObj* t1 = new TObj(1,"A");
    v1.emplace_back(1, "A");

    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(1, v1.front().get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("A"), v1.front().get()->getS());

    v1.emplace_back(2, "B");
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(2, v1.back().get()->getN());
    CPPUNIT_ASSERT_EQUAL(string("B"), v1.back().get()->getS());
  }*/

  void test_pop1()
  {
    title("test_pop1() called");
    shared_ptr_vector<int> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());

    int* i1 = new int(1);
    v1.push_back(i1);
    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
    CPPUNIT_ASSERT_EQUAL(i1, v1.front().get());
    CPPUNIT_ASSERT_EQUAL(i1, v1.back().get());
    CPPUNIT_ASSERT_EQUAL(i1, v1.at(0).get());

    int* i2 = new int(2);
    v1.push_back(i2);
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i2, v1.back().get());
    CPPUNIT_ASSERT_EQUAL(i2, v1.at(1).get());

    int* i3 = new int(3);
    v1.push_back(i3);
    CPPUNIT_ASSERT(3 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i3, v1.back().get());
    CPPUNIT_ASSERT_EQUAL(i3, v1.at(2).get());

    int* r_i3 = v1.back().get();
    CPPUNIT_ASSERT_EQUAL(i3, r_i3);
    v1.pop_back();
    CPPUNIT_ASSERT(2 == v1.size());
    CPPUNIT_ASSERT_EQUAL(i2, v1.back().get());
    CPPUNIT_ASSERT_EQUAL(i2, v1.at(1).get());
  }
  void test_str()
  {
    title("test_str() called");
    shared_ptr_vector<int> v1;
    v1.push_back(new int(1));
    v1.push_back(new int(2));
    v1.push_back(new int(3));
    string s = to_string(v1);
    cout << "to_string(v1)=" << s << endl;
    CPPUNIT_ASSERT("[ 1 2 3 ]" == s);

    shared_ptr_vector<TObj> v2;
    v2.push_back(new TObj(1, "A"));
    v2.push_back(new TObj(2, "B"));
    v2.push_back(new TObj(3, "C"));
    s = to_string(v2);
    cout << "to_string(v2)=" << s << endl;
    CPPUNIT_ASSERT("[ (1,A) (2,B) (3,C) ]" == s);
    cout << "v1=" << v1 << endl;
    cout << "v2=" << v2 << endl;
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
//  s->addTest(new CppUnit::TestCaller<Tests>("test_emplaceback1", &Tests::test_emplaceback1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_pop1", &Tests::test_pop1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_str", &Tests::test_str));

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

