CC = gcc
CFLAGS=-w -I. -I/usr/include/glib-2.0 -I/usr/include/libgsf-1 -I/usr/include/libxml2 `pkg-config --cflags gtk+-3.0`
LDFLAGS=`pkg-config --libs gtk+-3.0`

goffice:algolyzer.o
	$(CC) -o algolyzer algolyzer.o $(LDFLAGS) $(CFLAGS)

run:algolyzer
	./algolyzer

.PHONY: clean

clean:
	rm *.o
