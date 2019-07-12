#include <stdio.h>
#include <stdlib.h>

int count_freq (FILE* input) {
	int count[26] = {0};
	int c;
	while ((c = fgetc(input)) != EOF) {
		if (isalpha(c)) {
			tolower(c);
			c -='a';
			count[c]++;
		}
	}
	int max = count[0];
	for (int i = 0; i < 25; i++) {
		if (max <= count[i+1]) {
			max = count[i+1];
		}
	}
	printf("max = %d\n", max);
	return max+1;
	}

void print_encrypt (FILE* input, int freq) {
	int c;
	while ((c = fgetc(input)) != EOF) {
		if (isalpha(c)) {
			c += freq;
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
		fprintf (stderr, "cannot open file.");
		EXIT_FAILURE;
	}
	int freq = count_freq (f);
	print_encrypt (f, freq);
		
	return 0;
	}
