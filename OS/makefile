CC=gcc
myshell: code.o built.o function.o imp.o header.h
	$(CC) -o myshell code.o built.o function.o imp.o -I.
code.o: code.c built.o function.o imp.o header.h
	$(CC) -c code.c -I.
built.o: built.c function.o imp.o header.h
	$(CC) -c built.c -I.
function.o: function.c imp.o header.h
	$(CC) -c function.c -I.
imp.o: imp.c header.h
	$(CC) -c imp.c -I.

.PHONY: clean

clean:
	rm -f *.o
