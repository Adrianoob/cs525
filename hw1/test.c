#include <stdio.h>
#include "storage_mgr.c"

int main() {
	initStorageManager();
	printf("%s\n", "hello world");
	return 0;
}
