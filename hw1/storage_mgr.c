#include <stdio.h>
#include "storage_mgr.h"

extern void initStorageManager (void) {
	// initialize SM
}

// extern RC createPageFile (char *fileName) {
// 	FILE *pagef = fopen(fileName, "w");
//     char *totalpg_str, *first_page;

//     totalpg_str = (char *) calloc(PAGE_SIZE, sizeof(char));  /* allocate "first" page to store total number of pages information */
//     first_page = (char *) calloc(PAGE_SIZE, sizeof(char));   /* considered as actual first page for the data */

//     strcat(totalpg_str,"1\n");

//     fwrite(totalpg_str, sizeof(char), PAGE_SIZE, pagef);
//     fwrite(first_page, sizeof(char), PAGE_SIZE, pagef);

//     free(totalpg_str);
//     free(first_page);

//     fclose(pagef);

//     return RC_OK;
// }
