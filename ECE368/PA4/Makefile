WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = hbt_main.c hbt.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(OBJS) -o pa4

.c.o:
	$(GCC) -c $*.c

testall: test1 test2

test1: pa4
	./pa4 -b examples/ops0 tree0

test2: pa4
	./pa4 -e examples/ops0
	
memory: memory1 memory2

memory1: pa4
	$(VAL) ./pa4 -b examples/operations_input_file tree_output_file

memory2: pa4
	$(VAL) ./pa4 -e examples/tree_input_file

clean:
	rm -f pa4 *.o output vallog testgen
	clear