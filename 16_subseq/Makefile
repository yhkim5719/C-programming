test: maxSeq.o test-subseq.o
	gcc -o test maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc -Wall -Werror -pedantic -std=gnu99 -c maxSeq.c
test-subseq.o: test-subseq.c
	gcc -Wall -Werror -pedantic -std=gnu99 -c test-subseq.c
clean:
	rm *.o
