#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		perror("Usage: rotateMatrix input");
		return EXIT_FAILURE;
	}
	FILE* f = fopen(argv[1], "r");
	if (f == NULL) {
		perror("Could not open file");
		return EXIT_FAILURE;
	}
	char matrix[10][10];
	int c = fgetc(f);
	int i = 0;
	int j = 0;
	while (c != EOF) {
		while (j != 10) {
			matrix[i][j] = c;
			c = fgetc(f);
			++j;
			if (c == '\n') {
				if (j < 10) {
					perror("Line is too short");
					return EXIT_FAILURE;
				} else if (j > 10) {
					perror("Line is too long");
					return EXIT_FAILURE;
				}
				c = fgetc(f);
				continue;
			}
			if (c == EOF && j < 10) {
				perror("Line is too short");
				return EXIT_FAILURE;
			}
			if (c == EOF && j > 10) {
				perror("Line is too long");
				return EXIT_FAILURE;
			}
			if (i >= 10 || j >= 10) {
				perror("File is too long");
				return EXIT_FAILURE;
			}
		}
		i++;
		j = 0;
	}
	if (i < 10) {
		perror("File is too short");
		return EXIT_FAILURE;
	}
	if (i > 10) {
		perror("File is too long");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			printf("%c", matrix[9 - j][i]);
		}
		printf("\n");
	}
//	FILE* out = fopen("output.out", "w");

	if(fclose(f) != 0) {
		perror("Could not close file");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
