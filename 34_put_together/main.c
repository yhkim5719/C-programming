#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
	counts_t* c = createCounts();
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		perror("Invalid file name");
		return NULL;
	}
	
	char* key = NULL;
	size_t sz = 0;
	while (getline(&key, &sz, f) != -1) {
		key[strlen(key) - 1] = '\0';
		addCount(c, lookupValue(kvPairs, key));
	}
	free(key);

	if (fclose(f) != 0) {return NULL;}

	return c;
}

int main(int argc, char ** argv) {
	if (argc < 3) {
		perror("Usage: ./count_value KVpairs file1 file2,.etc.");  //WRITE ME (plus add appropriate error checking!)
		return EXIT_FAILURE;	
	}
	kvarray_t* kv = readKVs(argv[1]);	//read the key/value pairs from the file named by argv[1] (call the result kv)
//	printKVs(kv);	//TODO test
	for (int i = 2; i < argc; i++) { 	//count from 2 to argc (call the number you count i)
		counts_t* c = countFile(argv[i], kv);	//count the values that appear in the file named by argv[i], using kv as the key/value pair
    							//   (call this result c)
		char* outName = computeOutputFileName(argv[i]);
    //compute the output file name from argv[i] (call this outName)


		FILE* f = fopen(outName, "w");    //open the file named by outName (call that f)
		printCounts(c, f);    //print the counts from c into the FILE f
//		fclose(f);    //close f
		free(outName);    //free the memory for outName and c
		freeCounts(c);
	}
	freeKVs(kv);
 //free the memory for kv

  return EXIT_SUCCESS;
}
