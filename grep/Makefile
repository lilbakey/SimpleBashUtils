CC=gcc
CFLAGS=-Werror -Wextra -Wall -std=c11

s21_grep: s21_grep.c ../common/utils.c
	$(CC) $(CFLAGS) -c s21_grep.c
	$(CC) $(CFLAGS) -c ../common/utils.c
	$(CC) $(CFLAGS) s21_grep.o utils.o -o s21_grep

clean:
	rm -fr *.o s21_grep

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.h
	valgrind --tool=memcheck --leak-check=yes ./s21_grep -o hello -i ../tests/test_grep1.txt