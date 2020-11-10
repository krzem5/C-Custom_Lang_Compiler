#ifndef __LOADER_H__
#define __LOADER_H__
#include <common.h>
#include <stdio.h>



typedef struct _SEARCH_PATH_LIST SearchPathList;
typedef struct _FILE_OBJECT* FileObject;



struct _SEARCH_PATH_LIST_ELEM{
	uint32_t ln;
	char* p;
};



struct _SEARCH_PATH_LIST{
	uint32_t ln;
	struct _SEARCH_PATH_LIST_ELEM* e;
};



struct _FILE_OBJECT{
	size_t fpl;
	char* fp;
	size_t ln;
	uint8_t* dt;
};



extern SearchPathList loader_search_path_list;



void loader_add_search_path(char* p);



FileObject loader_load_file(char* fp);



#endif
