file_test=queue.cpp

all:
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g $(file_test) -lgtest -lstdc++ -lm
	./a.out

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM *.out

valgrind:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM *.out
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g $(file_test) -lstdc++ -lm
	valgrind --tool=memcheck --leak-check=yes  ./a.out

valgrind_long:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM *.out
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g $(file_test) -lstdc++ -lm
	valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./a.out

set:
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g set.cpp -lgtest -lstdc++ -lm
	./a.out

reference:
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g reference.cpp -lstdc++ -lm
	./a.out

copy_construct:
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g copy_construct.cpp -lstdc++ -lm
	./a.out

equivalent:
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g equivalent.cpp -lstdc++ -lm
	./a.out

tree:
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g tree.cpp -lstdc++ -lm
	./a.out

test_map: clean
	gcc -std=c++17 -Wall -Werror -Wextra -pedantic -g test_map.cpp -lgtest -lstdc++ -lm
	./a.out