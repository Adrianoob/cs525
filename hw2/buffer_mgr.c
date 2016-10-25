#include <stdio.h>
#include <stdlib.h>
#include "buffer_mgr.h"
// Buffer Manager Interface Pool Handling
RC initBufferPool(BM_BufferPool *const bm, const char *const pageFileName, 
		  const int numPages, ReplacementStrategy strategy, 
		  void *stratData) {
  bm->pageFile = pageFileName;
  bm->numPages = numPages;
  bm->strategy = strategy;
  bm->numReadIO = 0;
  bm->numWriteIO = 0;
  
  BM_PageHandle *pages = malloc(sizeof(BM_PageHandle)*numPages);
  int i;
  for(i = 0; i < numPages; i++) {
    pages[i].pageNum = NO_PAGE;
    pages[i].data = NULL;
    pages[i].dirty = 0;
    pages[i].fixcount = 0;
  }
  bm->mgmtData = ds;
  
  return RC_OK;
}


RC shutdownBufferPool(BM_BufferPool *const bm) {
  // see if there's any page to unpin
  // free memory 
  SM_FileHandle fh;
  openPageFile(bm->pageFile, &fh);
  BM_PageHandle *pages = bm->mgmtData;

  int i;
  for(i = 0; i < bm->numPages; i++) {
    if (pages[i].fixcount > 0)
      return RC_BUFFER_PINNED;
    if (pages[i].dirty == 1)
      writeBlock(pages[i]->pageNum, &fh, pages[i]->data);
    if (pages[i]->data != NULL)
      free(pages[i]->data);
    free(pages[i]);
  }
  closePageFile(&fh);
}


RC forceFlushPool(BM_BufferPool *const bm) {
  BM_PageHandle *pages = (Data_Structure *)bm->mgmtData;
  SM_FileHandle fh;
  openPageFile(bm->pageFile, &fh);
  
  int i;
  for (i = 0; i < bm->numPages; i++) {
    if (pages[i].dirty == 1 && pages[i].fixcount == 0) {
      writeBlock(pages[i].pageNum, &fh, pages[i]->data);
      pages[i].dirty = 0;
    }
  }
  closePageFile(&fh);
  return RC_OK;
}


// Buffer Manager Interface Access Pages
RC markDirty (BM_BufferPool *const bm, BM_PageHandle *const page) {
  PageNumber pageNum = page->pageNum;
  int i;
  for (int i = 0; i < bm->numPages; i++) {
    if (bm->mgmtData[i]->pageNum == pageNum && pageNum != NO_PAGE)
      bm->mgmtData[i].dirty = 1;
  }
  return RC_OK;
}


RC unpinPage (BM_BufferPool *const bm, BM_PageHandle *const page) {
  PageNumber pageNum = page->pageNum;
  int i;
  for (int i = 0; i < bm->numPages; i++) {
    if (bm->mgmtData[i]->pageNum == pageNum && pageNum != NO_PAGE)
      bm->mgmtData[i].fixcount -= 1;
  }
  return RC_OK;
}


RC forcePage (BM_BufferPool *const bm, BM_PageHandle *const page) {
  PageNumber pageNum = page->pageNum;
  int i;
  for (int i = 0; i < bm->numPages; i++) {
    BM_PageHandle ph = bm->mgmtData[i];
    if (ph->pageNum == pageNum && pageNum != NO_PAGE && ph.dirty == 1) {
      SM_FileHandle fh;
      openPageFile(bm->pageFile, &fh);
      writeBlock(pageNum, &fh, ph->data);
      closePageFile(&fh);
      ph.dirty = 0;
    }
  }
  return RC_OK;
}


RC pinPage (BM_BufferPool *const bm, BM_PageHandle *const page, 
	    const PageNumber pageNum) {
  
}

// Statistics Interface
PageNumber *getFrameContents (BM_BufferPool *const bm) {
  BM_PageHandle pages = bm->mgmtData;
  PageNumber *pn = malloc(sizeof(PageNumber) * bm->numPages);

  int i;
  for (i = 0; i < bm->numPages; i++) {
    if (pages[i].pageNum == NO_PAGE)
      pn[i] = NO_PAGE;
    else
      pn[i] = NO_PAGE;
  }
   return pn;
}


bool *getDirtyFlags (BM_BufferPool *const bm) {
  BM_PageHandle pages = bm->mgmtData;
  bool *flags = malloc(sizeof(bool) * bm->numPages);
  
  int i;
  for (i = 0; i < bm->numPages; i++) {
    if (pages[i]->dirty == 1)
      flags[i] = true;
    else
      flags[i] = false;
  }
  return flags
}


int *getFixCounts (BM_BufferPool *const bm) {
  BM_PageHandle pages = bm->mgmtData;
  int *nums = malloc(sizeof(int) * bm->numPages);

  int i;	
  for (i = 0; i < bm->numPages; i++) {
    nums[i] = pages[i]->fixcount;
  }	
  return flags;
}


int getNumReadIO (BM_BufferPool *const bm) {
  return bm->numReadIO;
}


int getNumWriteIO (BM_BufferPool *const bm) {
  return bm->numWriteIO;
}
