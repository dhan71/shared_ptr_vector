##################################################
# Makefile
##################################################

CCC = g++
CXX = g++
LD  = g++
CCOPTIONS = -std=c++17 -fPIC -g -Wall -Wextra
LDOPTIONS = -g -m64
SLOPTOINS = -shared -g -m64

CPPUNIT_HOME = /usr
CPPUNIT_INC = $(CPPUNIT_HOME)/include
CPPUNIT_LIB = $(CPPUNIT_HOME)/lib/x86_64-linux-gnu/libcppunit.a
#BOOSTUT_LIB = -lboost_unit_test_framework

APP_INC = -I$(CPPUNIT_INC) -I.

APP_LIB = $(CPPUNIT_LIB)

CXXFLAGS = $(CCOPTIONS) $(APP_INC)
LDFLAGS  = $(APP_LIB)
VPATH    = .

# Suffix rules
.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

exe : ut ut2

all : exe
clean:
	/bin/rm -f *o
	/bin/rm -f ut ut2


ut : ut.o
	$(CCC) $(LDOPTIONS) -o $@ $? $(LDFLAGS)

ut2 : ut2.o
	$(CCC) $(LDOPTIONS) -o $@ $? $(LDFLAGS)

