backend_comp: backend.c common.c linked_list.c utils_m.c hash_table.c unit_test.c
	clear
	gcc -Wall -g backend.c linked_list.c hash_table.c utils_m.c common.c unit_test.c -o unit_tests -lcunit

frontend_comp: backend.c common.c linked_list.c utils_m.c hash_table.c unit_test.c frontend.c
	clear
	gcc -Wall -g backend.c linked_list.c hash_table.c utils_m.c common.c frontend.c -o frontend

frun: frontend_comp
	./frontend

frunmem: frontend_comp
	valgrind -s --leak-check=full ./frontend

cov:
	clear
	gcc -Wall -g -fprofile-arcs -ftest-coverage backend.c linked_list.c hash_table.c utils_m.c common.c unit_test.c -o unit_tests -lcunit
	./unit_tests
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

memtest: backend_comp
	valgrind -s --leak-check=full ./unit_tests