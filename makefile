CC := gcc
CXX := g++
CFLAGS := -O3 -std=c11
CXXFLAGS := -O3 -std=c++11 -Wall 
SFMT_USE := -msse2 -fno-strict-aliasing -DSFMT_MEXP=19937 -DHAVE_SSE2=1 -I./SFMT

COMPILE :=$(CC) $(CFLAGS) -c
COMPILE_CXX :=$(CXX) $(CXXFLAGS) -c
SFMT_USE_COMPILE :=$(CC) $(CFLAGS) $(SFMT_USE) -c
SFMT_USE_COMPILE_CXX := $(CXX) $(CXXFLAGS) $(SFMT_USE) -c 

default:db-search db-create db-sort  list

#Target list
test-tick10:test-tick10.o

db-search:db-search.o
	$(CXX) $^ -o $@

db-create:db-create-entry.o db-create.o
	$(CXX) $^ -pthread -o $@

db-sort:db-sort-entry.o db-sort.o
	$(CXX) $^ -pthread -o $@

tickList:tickList.o
	$(CXX) $^ -o $@

list:list-entry.o
	$(CXX) $^ -o $@

#Test Target
test:test.o db-create.o tickSeed.o util.o SFMT.o 
	$(CXX) $^ -pthread -o  $@

#Who use util/tickSeed/SFMT
db-create db-sort db-search: tickSeed.o

test-tick10 db-create db-sort db-search tickList:util.o

test-tick10 db-create tickList list:SFMT.o

list:list.o RNGData.o

db-search:SFMTUtil.o SFMT.o util.o

#Header file
util.o:util.hpp

tickSeed.o:tickSeed.hpp

SFMT.o:SFMT/SFMT.h

RNGData.o:RNGData.hpp

list.o list-entry.o:list.hpp

db-create.o db-create-entry.o:db-create.hpp threadSafeWorker.hpp

db-sort.o db-sort-entry.o:db-sort.hpp threadSafeWorker.hpp

SFMTUtil.o:SFMTUtil.hpp


#Default compile(Use SFMT)
%.o:%.c
	$(SFMT_USE_COMPILE) $<
%.o:%.cpp
	$(SFMT_USE_COMPILE_CXX) $<
	

#Compile for Non-SFMT
util.o:util.cpp
	$(COMPILE_CXX) $<
tickSeed.o:tickSeed.cpp
	$(COMPILE_CXX) $<

#Because of ./SFMT/, SFMT.o can't be applied %.o:%.c
SFMT.o:SFMT/SFMT.c 
	$(SFMT_USE_COMPILE) $<

clean:
	$(RM) *.o
	$(RM) db-search db-create tickList list test db-sort
