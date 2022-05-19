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
    cout << "Tests::setUp called" << endl;
  }
  void tearDown()
  {
    cout << "Tests::tearDown called" << endl;
  }

public:
  void test_ctor1()
  {
    cout << "Tests::test_ctor1 called" << endl;
    shared_ptr_vector<int> v1;
    //CPPUNIT_ASSERT_EQUAL(0, v1.size());
    CPPUNIT_ASSERT(0 == v1.size());
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
  }
  void test_ctor2()
  {
    cout << "Tests::test_ctor2 called" << endl;
    shared_ptr_vector<int> v1;
    //CPPUNIT_ASSERT_EQUAL(0, v1.size());
    CPPUNIT_ASSERT(0 == v1.size());
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
  }
  void test_push1()
  {
    shared_ptr_vector<int> v1;
    CPPUNIT_ASSERT_EQUAL(true, v1.empty());
    v1.push_back(1);
    CPPUNIT_ASSERT(1 == v1.size());
    CPPUNIT_ASSERT_EQUAL(false, v1.empty());
  }
  void test_push2()
  {
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
  void test_pop1()
  {
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

    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor1", &Tests::test_ctor1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_ctor2", &Tests::test_ctor2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_push1", &Tests::test_push1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_push2", &Tests::test_push2));
    s->addTest(new CppUnit::TestCaller<Tests>("test_pop1", &Tests::test_pop1));
    s->addTest(new CppUnit::TestCaller<Tests>("test_str", &Tests::test_str));

    return s;
  }
};

int
main(int argc, char* argv[])
{
  CppUnit::TextTestRunner r;
  r.addTest(Tests::suite());
  r.run();
  return 0;
}

