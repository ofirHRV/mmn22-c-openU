myset: myset.o set.o input.o
	gcc -g -Wall -ansi -pedantic myset.o set.o input.o -o myset
myset.o: myset.c set.h
	gcc -c -g -Wall -ansi -pedantic myset.c -o myset.o
set.o: set.c set.h
	gcc -c -g -Wall -ansi -pedantic set.c -o set.o
input.o: input.c set.h
	gcc -c -g -Wall -ansi -pedantic input.c -o input.o
