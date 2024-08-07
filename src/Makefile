GCC = gcc -std=c++17
SRC = tests.cpp
OBJ = s21_containers.o
CFLAGS = -Wall -Wextra -Werror -pedantic -g
TESTFLAGS = -lgtest -lgcov --coverage -lstdc++ -lm

all: clean gcov_report

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css *.txt *.gcda *.gcno report tests

test: clean
	$(GCC) $(CFLAGS) $(SRC) -o tests $(TESTFLAGS)
	./tests

gcov_report: test
	lcov -t tests -o rep.info -c -d . --no-external
	genhtml -o report rep.info
	open report/index.html

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SRC) *.h
	valgrind --tool=memcheck --leak-check=yes  ./tests

style_check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cpp *.h
	rm .clang-format

style_format:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cpp *.h
	rm .clang-format