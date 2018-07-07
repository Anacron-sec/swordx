CC=gcc
CFLAGS= -O2 -I$(IDIR) -Wall -Werror -Wpedantic -flto

BDIR=bin
ODIR=obj
IDIR=inc
SDIR=src

_DEPS = trie.h utils.h sorter.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
_OBJ = swordx.o trie.o utils.o sorter.o

swordx: $(OBJ)
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean all test install uninstall

all: swordx

install:
	cp ./bin/swordx /usr/local/bin/swordx

uninstall:
	rm -f /usr/local/bin/swordx

test:
	make && make -C test && test/bin/test_swordx

clean:
	rm -f $(ODIR)/*.o $(BDIR)/* && make clean -C test