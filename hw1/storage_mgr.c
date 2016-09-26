#include <stdio.h>
#include <stdlib.h>
#include "storage_mgr.h"

extern void initStorageManager (void) {
	// initialize SM
}

extern RC createPageFile (char *fileName) {
	FILE *newPF = fopen(fileName, "w");
	char *pf_str;

	pf_str = (char *) malloc(PAGE_SIZE * sizeof(char));  /* allocate "first" page to store total number of pages information */
	strcpy(pf_str, "/0");

	fwrite(pf_str, sizeof(char), PAGE_SIZE, newPF);
	free(pf_str);
	fclose(newPF);

	return RC_OK;
}
