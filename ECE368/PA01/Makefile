Warning = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR)
VAL= valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose

SRCS = pa1.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)
arss: $(OBJS)
	$(GCC) $(OBJS) -o arss

.c.o:
	$(GCC) -c $*.c

testall: testA testL

testA: arss
	./arss -a examples/15.b output1.b
	diff output1.b examples/15sa.b

testL: arss
	./arss -l examples/15.b output2.b
	diff output2.b examples/15sl.b

memory: arss
	$(VAL) ./arss examples/15.b output1.b

clean:
	rm -f arss *.o output? vallog testgen
	clear
