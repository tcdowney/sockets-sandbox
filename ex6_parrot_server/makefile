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

parrot_server: src/parrot_server.c src/parrot_server.h
	@echo Compiling $@
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

test: tests.out
	@./tests.out

memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM parrot_server

tests.out: test/test_parrot_server.c src/parrot_server.c src/parrot_server.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) $(LDFLAGS) src/parrot_server.c ../vendor/unity/unity.c test/test_parrot_server.c -o tests.out
