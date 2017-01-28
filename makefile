CC := gcc
CFLAGS := -O3 -std=c11 
SFMT_USE := -msse2 -fno-strict-aliasing -DSFMT_MEXP=19937 -DHAVE_SSE2=1 -I./SFMT

COMPILE :=$(CC) $(CFLAGS) -c
SFMT_USE_COMPILE =$(CC) $(CFLAGS) $(SFMT_USE) -c

default:db-search db-create tickList list

#Target list
test-tick10:test-tick10.o

db-search:db-search.o

db-create:db-create.o

tickList:tickList.o

list:list.o

#Who use util/tickSeed/SFMT
db-create db-search: tickSeed.o

test-tick10 db-create db-search tickList list:util.o

test-tick10 db-create tickList list:SFMT.o

#Header file
util.o:util.h

tickSeed.o:tickSeed.h

SFMT.o:SFMT/SFMT.h

#Default compile(Use SFMT)
%.o:%.c
	$(SFMT_USE_COMPILE) $<

#Compile for Non-SFMT
db-search.o:db-search.c
	$(COMPILE) $<
util.o:util.c
	$(COMPILE) $<
tickSeed.o:tickSeed.c
	$(COMPILE) $<

#Because of ./SFMT/, SFMT.o can't be applied %.o:%.c
SFMT.o:SFMT/SFMT.c 
	$(SFMT_USE_COMPILE) $<

clean:
	$(RM) *.o
