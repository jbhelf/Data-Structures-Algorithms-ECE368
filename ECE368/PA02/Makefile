WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = huffman_main.c huffman.c
OBJS = $(SRCS:%.c=%.o)
pa2: $(OBJS)
	$(GCC) $(OBJS) -o pa2

.c.o:
	$(GCC) -c $*.c

testall: test1 test2

test1: pa2
	./pa2 original/gophers gophers.count gophers.tree gophers.code gophers.hbt
	diff count/gophers.count gophers.count
	diff tree/gophers.tree gophers.tree
	diff code/gophers.code gophers.code
	diff compressed/gophers.hbt gophers.hbt
test2: pa2
	./pa2 original/empty empty.count empty.tree empty.code empty.hbt
	diff count/empty.count empty.count
	diff tree/empty.tree empty.tree
	diff code/empty.code empty.code
	diff compressed/empty.hbt empty.hbt

memory: pa2
	$(VAL) ./pa2 original/gophers gophers.count gophers.tree gophers.code gophers.hbt

clean:
	rm -f pa2 *.o output? vallog testgen 
	clear
