CC=gcc
CFLAGS=-I$(IDIR) -Wall -Werror

BDIR=bin
ODIR=obj
IDIR=inc
SDIR=src

_DEPS = trie.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
_OBJ = swordx.o trie.o utils.o

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