CC=gcc
CFLAGS=-Werror -Wextra -Wall -std=c11

s21_cat: s21_cat.c ../common/utils.c
	$(CC) $(CFLAGS) -c s21_cat.c
	$(CC) $(CFLAGS) -c ../common/utils.c
	$(CC) $(CFLAGS) s21_cat.o utils.o -o s21_cat

clean:
	rm -fr *.o s21_cat

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.h
	valgrind --tool=memcheck --leak-check=yes ./s21_cat -ebnst ../tests/test_cat.txt
	