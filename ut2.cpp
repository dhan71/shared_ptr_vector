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
    int* i1 = new int(1);
    int* i2 = new int(2);

    shared_ptr<int> sp1(i1);
    cout << "sp1.get() = " << sp1.get() << ":" << *(sp1.get()) << endl;
    sp1.get() = i2;
    cout << "sp1.get() = " << sp1.get() << ":" << *(sp1.get()) << endl;
    CPPUNIT_ASSERT(i2 == sp1.get());
  }

public:
  static CppUnit::Test* suite()
  {
    CppUnit::TestSuite* s = new CppUnit::TestSuite(" Test Test ");

    s->addTest(new CppUnit::TestCaller<Tests>("test_x1", &Tests::test_x1));

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

