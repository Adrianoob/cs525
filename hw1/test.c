#include <stdio.h>
#include "storage_mgr.h"

int main() {
	initStorageManager();
	RC code1 = createPageFile("file1");
	RC code2 = openPageFile();
	printf("%s\n", "hello world");
	printf("createPageFile: %d\n", code1);
	printf("openPageFIle: %d\n", code2);
	return 0;
}
