#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


char* splitLine(char* line) {
	char* value = strchr(line, '=');
	*value = '\0';
	value++;
	
	value[strlen(value) - 1] = '\0';	
	return value;
}

kvarray_t * readKVs(const char * fname) {
	FILE* f = fopen(fname, "r");
	if (f == NULL) {
		perror("Could not open file");
		return NULL;
	}

// read lines from the file using getline();	
	int numPairs = 0;

	kvarray_t* kvarray = malloc(sizeof(kvarray_t));
	kvarray->pair = NULL; 
	
	char* line = NULL;
	size_t sz = 0;
	while(getline(&line, &sz, f) != -1) {
		if (line[0] == '\n') {
			continue;
		}
		kvarray->pair = realloc(kvarray->pair, ((numPairs + 1) * sizeof (*kvarray->pair)));
		kvarray->pair[numPairs] = malloc((sizeof(*kvarray->pair[numPairs])));
		kvarray->pair[numPairs]->value = splitLine(line);
		kvarray->pair[numPairs]->key = line;
		
		line = NULL;
		numPairs++;
	}
	free(line);
	kvarray->numPairs = numPairs;

	if (fclose(f) != 0) {return NULL;}
	return kvarray;
}

void freeKVs(kvarray_t * pairs) {
	for (int i = 0; i < pairs->numPairs; i++) {
		free(pairs->pair[i]->key);	
//		free(pairs->pair[i]->value);	
		free(pairs->pair[i]);
	}
	free(pairs->pair);
	free(pairs);
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
	for (int i = 0; i < pairs->numPairs; i++) {
		printf("key = '%s' value = '%s'\n", pairs->pair[i]->key, pairs->pair[i]->value);
	}
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
	for (int i = 0; i < pairs->numPairs; i++) {
		if (strcmp(key, pairs->pair[i]->key) == 0) {
			return pairs->pair[i]->value;
		}
	}
	return NULL;
  //WRITE ME
}
