
unit_tests: hash_table.c linked_list.c unit_tests.c common.c
	clear
	gcc -Wall -g -fprofile-arcs -ftest-coverage hash_table.c linked_list.c unit_tests.c common.c -o unit_tests -lcunit

memtest: unit_tests 
	valgrind --leak-check=full ./unit_tests

ll:
	clear
	gcc -Wall -g linked_list.c common.c -o linked_tests -lcunit

it:
	clear
	gcc -Wall -g linked_list.c common.c -o iterator_test -lcunit

freq_comp:
	clear
	gcc -Wall -g -pg hash_table.c linked_list.c freq-count.c -o freq-count

cov:
	clear
	gcc -Wall -g -fprofile-arcs -ftest-coverage hash_table.c linked_list.c unit_tests.c common.c -o unit_tests -lcunit
	./unit_tests
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

clean:
	rm *o rm *out
