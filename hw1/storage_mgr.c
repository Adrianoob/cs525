#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage_mgr.h"

extern void initStorageManager (void) {
	// initialize SM
}

extern RC createPageFile (char *fileName) {
	FILE *newPF = fopen(fileName, "w");

	char *pf_str;
	pf_str = (char *) malloc(PAGE_SIZE * sizeof(char));
	strcpy(pf_str, "1\0");

	fwrite(pf_str, sizeof(char), PAGE_SIZE, newPF);
	free(pf_str);
	fclose(newPF);

	return RC_OK;
}

extern RC openPageFile (char *fileName, SM_FileHandle *fHandle){
	FILE *pf = fopen(fileName, "r+");
	
	if (pf){
		char *str;

		str = (char *) malloc(sizeof(char) * PAGE_SIZE);
		fgets(str, PAGE_SIZE, pf);

		fHandle->fileName = fileName;
		fHandle->totalNumPages = atoi(str);
		fHandle->curPagePos = 0;
		fHandle->mgmtInfo = pf;
		
		free(str);
		return RC_OK;
	}
	return RC_FILE_NOT_FOUND;
}

extern RC closePageFile (SM_FileHandle *fHandle) {
	int status = fclose(fHandle->mgmtInfo);
	if(status == 0){
		return RC_OK;
	}
	return RC_FILE_NOT_FOUND;
}

extern RC destroyPageFile (char *fileName){
	int status = remove(fileName);
	if (status == 0){
		return RC_OK;
	}
	return RC_FILE_NOT_FOUND;
}
