CC = g++
WCHECKS = -Wall -Werror -Wextra -lstdc++ -std=c++17 
CHECK_FLAGS = -lgtest -pthread -lgtest_main 

MAIN_SRCS = *.cc
MAIN_HEADS = *.h
MAIN_OBJS = $(MAIN_SRCS:.cc=.o)

all: matrix_oop.a

matrix_oop.a: $(MAIN_HEADS) $(MAIN_SRCS)
	g++ -c $(WCHECKS) *.cc
	ar rc $@ $(MAIN_OBJS)
	ranlib $@ 

matrix_oop.o:
	$(CC) $(WCHECKS) -c $(MAIN_SRCS)

test: test.cc matrix_oop.a
	$(CC) -g $^ $(BASE_FLAGS) $(CHECK_FLAGS) -lm -ldl -o test.out
	clear
	./test.out

style:
	clang-format -n *.cc *.h

leaks-mac: test
	leaks --atExit -- ./test.out

leaks-linux: test
	valgrind --leak-check=yes ./test.out

clean:
	rm -f *.out
	rm -rf *.out*
	rm -f *.o
	rm -f *.a
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -rf gcov_report
	rm -f *.gcov
