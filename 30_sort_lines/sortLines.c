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
		free(data[i]);
	}
}

/*
int main(int argc, char ** argv) {
  
  if (argc == 0) {
    fprintf(stderr,"Not enough arguments \n");
    return EXIT_FAILURE;
  }
  else if (argc == 1){
    //read from stdio
    char** data = NULL;
    char* line = NULL;
    size_t sz = 0;
    int i = 0; 
    while(getline(&line, &sz, stdin) >= 0){
      data = realloc(data, (i + 1) * sizeof(*data));
      data[i] = line;
      line = NULL;
      i++;
    }
    free(line);
    sortData(data, i);
    for (int j=0; j < i; j++){
      printf("%s", data[j]);
      free(data[j]);
    }
    free(data);
  }
  else {
    for( int k = 1; k < argc; k++){
      char** data = NULL;
      char* line = NULL;
      size_t sz = 0;
      int i = 0; 
      FILE * f = fopen(argv[k], "r");
      if (f == NULL){
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      while(getline(&line, &sz, f) >= 0){
        data = realloc(data,(i + 1) * sizeof(*data));
        data[i] = line;
        line = NULL;
        i++;
      }
      free(line);
      sortData(data, i);
      for(int j = 0;j < i; j++){
        printf("%s", data[j]);
        free(data[j]);
      }
      free(data);
      if (fclose(f) != 0) {
	perror("Failed to close the input file!");
	return EXIT_FAILURE;
      }
      //read from file 
    }
  
  
    //WRITE YOUR CODE HERE!
  
    return EXIT_SUCCESS;
  }
}

*/

void proc (FILE* input) {
	char** data = NULL;
	
	char* line = NULL;
	size_t sz = 0;
	int i = 0;
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

void nonArgProc () {
	
	size_t sz = 0;
	int i = 0;
	char** data = (char**) malloc(sizeof(*data));
	char* line = NULL;
	while((getline(&line, &sz, stdin)) >= 0) {
/*		if (sz == 0) {
			line = NULL;
			free(line);
			sortData(data, i);
			free(data);
			return;
*///		}
		data = realloc(data, (i + 1) * sizeof(*data));
		data[i] = line;
//		printf("data[%d] = %s", i, data[i]);
//		printf("line = %s", line);
		i++;
		line = NULL;
	}			// read all lines
	free(line);
	sortData(data, i);	// sort & print TODO a func
	free(data);
}

int main(int argc, char ** argv) {
	if (argc == 1) {
//		printf("Input data:\n");	// Read from std input
		nonArgProc();
	}
	else if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			FILE* input;
			input = fopen(argv[i], "r");
			if (input == NULL) {
				perror("Could not open file");
				return EXIT_FAILURE;
			}
			proc(input);	
			if (fclose(input) != 0) {
				perror("Could not close file");
				return EXIT_FAILURE;
			}
		}
	}
  return EXIT_SUCCESS;
}


