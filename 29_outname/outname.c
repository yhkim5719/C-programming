#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
	char* outputFileName = malloc(strlen(inputName + 7)*sizeof(outputFileName));
	strcpy (outputFileName, inputName);
	strcat (outputFileName, ".count");
	return outputFileName;
//WRITE ME
}
