test: test.o
	gcc test.o -o test
test.o: test.c
	gcc test.c -std=gnu99 -Wall -Werror -pedantic -c
clean:
	rm *.o *.c~ *.h~
