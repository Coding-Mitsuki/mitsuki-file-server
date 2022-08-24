CC=gcc
CFLAGS=-I$(IDIR) -g -Werror -Wpedantic -Wall

IDIR=include
ODIR=obj
SRCDIR=src

LIBS=

_DEPS=http_server.h headers.h request.h response.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=http_server.o headers.o request.o response.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mitsuki-http-server: $(OBJ) obj/main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

library: $(OBJ)
	$(CC) -shared -o mitsuki-http-server.so $^

PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ mitsuki-http-server*
