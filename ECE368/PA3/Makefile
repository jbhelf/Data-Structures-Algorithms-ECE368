WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa3.c packing.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	$(GCC) $(OBJS) -o pa3

.c.o:
	$(GCC) -c $*.c

testall: test1 test2 testrr

test1: pa3
	./pa3 examples/3.po 3.pr 3.dim 3.pck
	diff 3.pr examples/3.pr
	diff 3.dim examples/3.dim
	diff 3.pck examples/3.pck

test2: pa3
	./pa3 examples/8.po 8.pr 8.dim 8.pck
	diff 8.pr examples/8.pr
	diff 8.dim examples/8.dim
	diff 8.pck examples/8.pck

testrr: pa3
	./pa3 examples/100.po 100.pr 100.dim 100.pck 
	diff 100.pr erik/100.pr
	diff 100.dim erik/100.dim
	diff 100.pck erik/100.pck
	./pa3 examples/500.po 500.pr 500.dim 500.pck 
	diff 500.pr erik/500.pr
	diff 500.dim erik/500.dim
	diff 500.pck erik/500.pck
	./pa3 examples/1K.po 1K.pr 1K.dim 1K.pck
	diff 1K.pr erik/1K.pr
	diff 1K.dim erik/1K.dim
	diff 1K.pck erik/1K.pck

dec: pa3
	diff erik/100.pr carrie/100.pr
	diff erik/100.dim carrie/100.dim
	diff erik/100.pck carrie/100.pck
	diff erik/500.pr carrie/500.pr
	diff erik/500.dim carrie/500.dim
	diff erik/500.pck carrie/500.pck
	diff erik/1K.pr carrie/1K.pr
	diff erik/1K.dim carrie/1K.dim
	diff erik/1K.pck carrie/1K.pck

memory: pa3
	$(VAL) ./pa3 examples/3.po 3.pr 3.dim 3.pck

clean:
	rm -f pa3 *.o output *.dim *.pck *.pr vallog testgen
	clear