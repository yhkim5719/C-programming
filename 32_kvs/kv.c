#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


char* splitLine(char* line) {
	char* value = strchr(line, '=');
	*value++ = '\0';
	
	value[strlen(value)-1] = '\0';
//	free(line);		
	return value;
}

kvarray_t * readKVs(const char * fname) {
	FILE* f = fopen(fname, "r");
	if (f == NULL) {
		perror("Could not open file");
		return NULL;
	}

// read lines from the file using getline();	
	kvarray_t* kvarray = malloc(sizeof(*kvarray));
	kvarray->pair = NULL;
	int numPairs = 0;
	
	char* line = NULL;
	size_t sz = 0;
	while(getline(&line, &sz, f) != -1) {
		if (line[0] == '\n') {
			line = NULL;
			continue;
		}
		kvarray->pair = realloc(kvarray->pair, (numPairs + 1) * sizeof (kvpair_t));
//		kvarray->pair[numPairs].value = realloc(kvarray->pair[numPairs].value, strlen(line) * sizeof(char));
//		kvarray->pair[numPairs].key = realloc(kvarray->pair[numPairs].key, strlen(line) * sizeof(char));
		kvarray->pair[numPairs].value = splitLine(line);
		kvarray->pair[numPairs].key = line;
		
		line = NULL;
		numPairs++;
	}
	free(line);
	kvarray->numPairs = numPairs;

	int close = fclose(f);
	if (close != 0) {return NULL;}
	return kvarray;
}

void freeKVs(kvarray_t * pairs) {
	for (int i = 0; i < pairs->numPairs; i++) {
//		free(pairs[i].pair->value);
//		free(pairs[i].pair->key);
		
//		free(pairs[i].pair);
	}
//		free(pairs->pair);
	free(pairs);
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
	for (int i = 0; i < pairs->numPairs; i++) {
		printf("key : '%s' value = '%s'\n", pairs->pair[i].key, pairs->pair[i].value);
//		printf("length of key, value = %zu, %zu\n", strlen(pairs->pair[i].key), strlen(pairs->pair[i].value));
	}
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
	for (int i = 0; i < pairs->numPairs; i++) {
		if (strcmp(key, pairs->pair[i].key) == 0) {return pairs->pair[i].value;}
	}
	return NULL;
  //WRITE ME
}
