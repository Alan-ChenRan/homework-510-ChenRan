test.sh: 0.c
	gcc 0.c -o test.sh -pthread -Wpedantic -fsanitize=address

