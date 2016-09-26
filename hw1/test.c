#include <stdio.h>
#include "storage_mgr.h"

int main() {
	initStorageManager();
	RC code = createFilePage("file1");
	printf("%s\n", "hello world");
	printf("%d\n", code);
	return 0;
}
