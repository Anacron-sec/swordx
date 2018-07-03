CC=gcc
CFLAGS=-Wall -Werror -Iinc -I../inc -lcunit

MAIN_PROGRAM=../obj/swordx.o
COMMON_O = $(filter-out $(MAIN_PROGRAM), $(wildcard ../obj/*.o))

BDIR=bin
ODIR=obj
IDIR=../inc
IDIRT=inc

_OBJ = test_swordx.o test_utils.o test_trie.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = utils.h trie.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_DEPST = test_utils.h test_trie.h
DEPST = $(patsubst %,$(IDIRT)/%,$(_DEPST))

vpath %.c src


test_swordx: $(OBJ) $(COMMON_O)
	$(CC) -o $(BDIR)/test_swordx $^ $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS) $(DEPST)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean all

clean:
	rm -f $(BDIR)/* $(ODIR)/*

all: test_swordx