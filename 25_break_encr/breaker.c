#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int count_freq (FILE* input) {
	int count[26] = {0};
	int c;
	c = fgetc(input);
	if (c == EOF) {EXIT_FAILURE;}
	while (c != EOF) {
		if (isalpha(c)) {
			tolower(c);
			c -='a';
			count[c]++;
		}
		c = fgetc(input);
	}
	int max = count[0];
	int idx = 0;
	for (int i = 0; i < 25; i++) {
		printf("count[%d] = %d\t", i, count[i]);	//TODO
		if (max < count[i+1]) {
			max = count[i+1];
			idx = i+1;
		}
	}
	return 'e' - 'a' + idx;
	}


void decrypt (FILE* input, int key) {
	int c;
	while ((c = fgetc(input)) != EOF) {
		if (isalpha(c)) {
//			tolower(c);
//			c -= 'a';
			c += key;
//			c %= 26;
//			c += 'a';
			printf ("%c", c);
		}
	}
	return;
}

int main (int argc, char** argv) {
	if (argc != 2) {
		fprintf (stderr, "USAGE: \"./breaker input.txt");
		EXIT_FAILURE;
	}
	FILE* f = fopen (argv[1], "r"); 
	if (f == NULL) {
		perror ("cannot open file.");
//		fprintf (stderr, "cannot open file.");
		EXIT_FAILURE;
	}
	int key = count_freq (f);
	printf("%d\n", key);
	decrypt (f, key);
		
	return 0;
}
