#include <stdio.h>
#include "storage_mgr.h"

int main() {
	initStorageManager();
	
	RC code1 = createPageFile("file1");
	printf("createPageFile: %d\n", code1);
	
	SM_FileHandle f_handle;
	RC code2 = openPageFile("file1", &f_handle);	
	printf("openPageFile:\n\tcode: %d\n\ttotal page:%d\n\tfile name:%s\n", code2, f_handle.totalNumPages, f_handle.fileName);
	
	RC code3 = closePageFile(f_handle);
	printf("closePageFile: %d\n", code3);
	
	RC code4 = destroyPageFile("file1");
	prinft("destroyPageFile: %d\n", code4);
	
	return 0;
}
