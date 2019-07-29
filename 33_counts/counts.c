#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
	counts_t* c = malloc(sizeof(*c));
	c->count = NULL;
	c->nCount = 0;
	c->nNull = 0;
	return c;
  //WRITE ME
}

void addCount(counts_t * c, const char * name) {
	if (name == NULL) {
		c->nNull++;
		return;
	}
	for (int i = 0; i < c->nCount; i++) {
		if (strcmp(c->count[i]->name, name) == 0) {
			c->count[i]->count++;
			return;
		}
	}
	c->count = realloc(c->count, (c->nCount + 1) * sizeof(*c->count));
	c->count[c->nCount] = malloc(sizeof(*c->count[c->nCount]));
	c->count[c->nCount]->name = malloc((strlen(name) + 1 ) * sizeof(*c->count[c->nCount]->name));
	strcpy(c->count[c->nCount]->name, name);
	c->count[c->nCount]->count = 1;
	c->nCount++;
  //WRITE ME
}
void printCounts(counts_t * c, FILE * outFile) {
	if (outFile == NULL) {
		perror("Invalid file");
		return;
	}
	for (int i = 0; i < c->nCount; i++) {
		fprintf(outFile, "%s: %d\n", c->count[i]->name, c->count[i]->count);
	}
	
	if (c->nNull != 0) {
		fprintf(outFile, "<unknown> : %d\n", c->nNull);
	}
	fclose(outFile);
  //WRITE ME
}

void freeCounts(counts_t * c) {
	for (int i = 0; i < c->nCount; i++) {
		free(c->count[i]->name);
		free(c->count[i]);
	}
	free(c->count);
	free(c);
  //WRITE ME
}
