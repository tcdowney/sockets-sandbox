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

LDFLAGS  = -pthread
LDFLAGS += -lpthread

test: tests.out
	@./tests.out

memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: test/test_send_example.c src/send_example.c src/send_example.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) $(LDFLAGS) src/send_example.c ../vendor/unity/unity.c test/test_send_example.c -o tests.out
