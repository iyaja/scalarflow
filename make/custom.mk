EXENAME = scalarflow
LIBNAME = libscalarflow.a

EXE = src
LIB = src/scalarflow
OBJ = .objs
TESTS = $(wildcard tests/*.cpp)

LIBOBJS = graph.o edge.o
EXEOBJS =
TESTOBJS = test.o test_edge.o test_graph.o
OBJS = $(EXEOBJS) $(LIBOBJS) main.o


# Toolchains and flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm
AR = ar
ARFLAGS =  rcs

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean output_msg

all : $(LIBNAME) $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)


$(EXENAME): $(OBJS) $(LIBNAME)
	$(LD) $(OBJS) $(LIBNAME) $(LDFLAGS) -o $(EXENAME)

$(LIBNAME): $(LIBOBJS)
	$(AR) $(ARFLAGS) $(LIBNAME) $(LIBOBJS)	

test: test.o $(LIBNAME)
	$(LD) $(LIBNAME) $(TESTOBJS) $(LDFLAGS) -o test

test.o: $(TESTS)
	$(CXX) $(CXXFLAGS) -I$(LIB)/.. $(TESTS)

main.o: $(EXEOBJS)
	$(CXX) $(CXXFLAGS) $(EXE)/main.cpp

edge.o:
	$(CXX) $(CXXFLAGS) $(LIB)/edge.cpp

graph.o: edge.o
	$(CXX) $(CXXFLAGS) $(LIB)/graph.cpp

# $(OBJ)%.o: $(EXE)/%.cpp
#     $(CXX) $(CXXFLAGS) $< -o $@	

clean:
	-rm -f *.o $(EXENAME) $(LIBNAME) $(OBJS) test