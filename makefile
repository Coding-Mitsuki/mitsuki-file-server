CC=gcc
CFLAGS=-I$(IDIR) -g -Werror -Wpedantic -Wall

IDIR=include
ODIR=obj
SRCDIR=src

LIBS=

_DEPS=http_server.h headers.h request.h response.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o http_server.o headers.o request.o response.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mitsuki-file-server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
