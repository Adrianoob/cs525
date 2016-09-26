#include <stdio.h>
#include "storage_mgr.h"

int main() {
	initStorageManager();
	
	RC code1 = createPageFile("file1");
	printf("createPageFile: %d\n", code1);
	
	SM_FileHandle f_handler;
	RC code2 = openPageFile("file1", &f_handler);	
	printf("openPageFIle:\n\tcode: %d\n\ttotal page:%d\n\tfile name:%s\n", code2, f_handler->totalNumPages, f_handler->fileName);
	
	return 0;
}
