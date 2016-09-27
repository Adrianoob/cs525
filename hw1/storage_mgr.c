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
	strcpy(pf_str, "\0");

	fwrite(pf_str, sizeof(char), PAGE_SIZE, newPF);
	free(pf_str);
	fclose(newPF);

	return RC_OK;
}

extern RC openPageFile (char *fileName, SM_FileHandle *fHandle) {
	FILE *pf = fopen(fileName, "r+");
	
	if (pf){
		char *str;

		str = (char *) malloc(sizeof(char) * PAGE_SIZE);
		fgets(str, PAGE_SIZE, pf);

		fHandle->fileName = fileName;
		fHandle->totalNumPages = strlen(str)/PAGE_SIZE + 1;
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

extern RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
	
	int seekSuccess;
	size_t readBlockSize;

	/* make sure pageNum is valid */
	if (pageNum >= fHandle->totalNumPages || pageNum < 0)
		return RC_READ_NON_EXISTING_PAGE;

	/* make sure fHandle has a file open */
	if (fHandle->mgmtInfo == NULL)
		return RC_FILE_NOT_FOUND;

	seekSuccess = fseek(fHandle->mgmtInfo, (pageNum+1)*PAGE_SIZE*sizeof(char), SEEK_SET);

	/* checks if the file seek was successful. If yes, reads the file page into mempage. */
	if (seekSuccess == 0){
		readBlockSize = fread(memPage, sizeof(char), PAGE_SIZE, fHandle->mgmtInfo);
		fHandle->curPagePos = pageNum;
		return RC_OK;
	}
	else{
		return RC_READ_NON_EXISTING_PAGE;
	}
}
