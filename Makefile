.PHONY: dep test clean

CC = gcc
CFLAGS = -O3 -g -Wall -Werror -std=gnu11
GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) qtest

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

# queue.o: queue.c queue.h harness.h
# 	$(CC) $(CFLAGS) -c queue.c 

# qtest: qtest.c report.c console.c harness.c queue.o
# 	$(CC) $(CFLAGS) -o qtest qtest.c report.c console.c harness.c queue.o

queue.o: queue.c queue.h harness.h list.h

qtest: qtest.c report.c console.c harness.c queue.o

dep:
	@$(CC) -MM *.c
	@$(CC) -M *.c > depend

test: qtest scripts/driver.py
	scripts/driver.py

clean:
	rm -f *.o *~ qtest depend
	rm -rf *.dSYM
	(cd traces; rm -f *~)
