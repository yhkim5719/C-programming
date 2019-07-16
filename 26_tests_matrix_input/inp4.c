#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv){
	if (argc != 2) {EXIT_FAILURE;}
	
	FILE * f = fopen(argv[1], "w+");
	if (f == NULL) {EXIT_FAILURE;}
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 9; ++j) {
			fprintf(f,"%d", j);
		}
		fprintf(f, "%c\n", 255);
	}
	if (fclose(f) != 0) {EXIT_FAILURE;}
	EXIT_SUCCESS;
}
