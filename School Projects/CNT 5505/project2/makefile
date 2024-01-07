CC=gcc
CXX=g++
#CFLAGS=-ansi -Wall -pedantic
#CFLAGS=-std=c99 -Wall -pedantic
CFLAGS=-std=c11 -Wall -pedantic

CXXFLAGS=-std=c++11 -Wall -pedantic
.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f *.o *.x core.* a.out

%.x : %.c
	$(CC) $(CFLAGS) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
