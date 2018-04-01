CC      = gcc
CFLAGS  = -std=gnu99
CFLAGS += -g3
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1

test: tests.out
	@./tests.out

memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: test/test_getaddrinfo_example.c src/getaddrinfo_example.c src/getaddrinfo_example.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/getaddrinfo_example.c ../vendor/unity/unity.c test/test_getaddrinfo_example.c -o tests.out
