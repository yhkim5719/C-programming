#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
	char* outputFileName = (char*) malloc((strlen(inputName) + 8)*sizeof(outputFileName));
	strcpy (outputFileName, inputName);
	strcat (outputFileName, ".counts");
	return outputFileName;
//WRITE ME
}
