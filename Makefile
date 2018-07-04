CC=gcc
CFLAGS= -O2 -I$(IDIR) -Wall -Werror -Wpedantic -flto

BDIR=bin
ODIR=obj
IDIR=inc
SDIR=src

_DEPS = trie.h utils.h trie_counted.h occurrency_sorter.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
_OBJ = swordx.o trie.o trie_counted.o utils.o occurrency_sorter.o

swordx: $(OBJ)
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean all test

all: swordx

test:
	make && make -C test && test/bin/test_swordx

clean:
	rm -f $(ODIR)/*.o $(BDIR)/* && make clean -C test