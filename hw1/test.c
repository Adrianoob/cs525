#include <stdio.h>
#include "storage_mgr.h"

int main() {
	initStorageManager();
	
	RC code1 = createPageFile("file1");
	printf("createPageFile: %d\n", code1);
	
	SM_FileHandle f_handle;
	RC code2 = openPageFile("file1", &f_handle);	
	printf("openPageFIle:\n\tcode: %d\n\ttotal page:%d\n\tfile name:%s\n", code2, f_handle.totalNumPages, f_handle->fileName);
	
	return 0;
}
