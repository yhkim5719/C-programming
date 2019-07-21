#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
	const char * const * p1 = vp1;
	const char * const * p2 = vp2;
	return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
	qsort(data, count, sizeof(char *), stringOrder);
	for (int i = 0; i < count; i++) {
		printf("%s", data[i]);
	}
}


void sortPrintData (FILE* input) {
	char** data = NULL;
	
	char* line = NULL;
	size_t sz = 0;
	size_t i = 0;
	while((getline(&line, &sz, input)) >= 0) {
		data = realloc(data, (i + 1) * sizeof(*data));
		data[i] = line;
		line = NULL;
		i++;
	}			// read all lines
	free(line);
	sortData(data, i);	// sort & print TODO a func
	free(data);
}

int main(int argc, char ** argv) {
	FILE* input;
	if (argc == 1) {			//TODO
		perror("Usage: ./sortLines inputFile");
		return EXIT_FAILURE;
	}
/*	if (argc == 1) {
		input = fopen("input.txt", "w+");
		if (input == NULL) {
			return EXIT_FAILURE;
		}
		char* str = NULL;
		printf("Input data: \n");	// Read from std input
		scanf("%s", str);
		fwrite(str, sizeof(char), sizeof(str), input);
			char** data = getLines(input);
			size_t numLine = countLine(input);
			sortData(data, numLine);	
	}
*/
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			input = fopen(argv[i], "r");
			if (input == NULL) {
				perror("Could not open file");
				return EXIT_FAILURE;
			}
			sortPrintData(input);	
			}
	}
	 
	if (fclose(input) != 0) {
		perror("Could not close file");
		return EXIT_FAILURE;
	}
  return EXIT_SUCCESS;
}
