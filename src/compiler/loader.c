#include <common.h>
#include <loader.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>



SearchPathList loader_search_path_list={
	0,
	NULL
};



void loader_add_search_path(char* p){
	assert(p!=NULL);
	uint32_t ln=0;
	while (*(p+ln)!=0){
		ln++;
	}
	assert(ln>0);
	if (*(p+ln-1)!='/'&&*(p+ln-1)!='\\'){
		*(p+ln)='/';
		ln++;
	}
	loader_search_path_list.ln++;
	loader_search_path_list.e=realloc(loader_search_path_list.e,loader_search_path_list.ln*sizeof(struct _SEARCH_PATH_LIST_ELEM));
	(loader_search_path_list.e+loader_search_path_list.ln-1)->ln=ln;
	(loader_search_path_list.e+loader_search_path_list.ln-1)->p=malloc((ln+1)*sizeof(char));
	*((loader_search_path_list.e+loader_search_path_list.ln-1)->p+ln)=0;
	while (ln>0){
		ln--;
		*((loader_search_path_list.e+loader_search_path_list.ln-1)->p+ln)=*(p+ln);
	}
	INFO("Adding Search Path '%s'\n",(loader_search_path_list.e+loader_search_path_list.ln-1)->p);
}



FileObject loader_load_file(char* fp){
	assert(fp!=NULL);
	INFO("Looking for File '%s'\n",fp);
	FileObject o=malloc(sizeof(struct _FILE_OBJECT));
	o->fpl=0;
	o->fp=NULL;
	o->ln=0;
	o->dt=NULL;
	INFO("Trying '%s'\n",fp);
	FILE* f=NULL;
	errno_t e=fopen_s(&f,fp,"rb");
	if (e!=0){
		if (e!=ENOENT){
			ERROR("fopen_s returned Error Code '%u'\n",e);
			free(o);
			return NULL;
		}
		uint32_t fpln=0;
		for (uint32_t i=0;i<loader_search_path_list.ln;i++){
			if (fpln==0){
				while (*(fp+fpln)!=0){
					fpln++;
				}
				assert(fpln>0);
			}
			o->fpl=(loader_search_path_list.e+i)->ln+fpln;
			o->fp=malloc((o->fpl+1)*sizeof(char));
			uint32_t j=0;
			for (;j<(loader_search_path_list.e+i)->ln;j++){
				*(o->fp+j)=*((loader_search_path_list.e+i)->p+j);
			}
			for (;j<(loader_search_path_list.e+i)->ln+fpln;j++){
				*(o->fp+j)=*(fp+j-(loader_search_path_list.e+i)->ln);
			}
			*(o->fp+j)=0;
			INFO("Trying '%s'\n",o->fp);
			e=fopen_s(&f,o->fp,"rb");
			if (e==0){
				char* tmp=o->fp;
				o->fp=malloc(_MAX_PATH*sizeof(char));
				assert(_fullpath(o->fp,tmp,_MAX_PATH)!=NULL);
				free(tmp);
				o->fpl=0;
				while (*(o->fp+o->fpl)!=0){
					o->fpl++;
				}
				assert(o->fpl>0);
				o->fp=realloc(o->fp,(o->fpl+1)*sizeof(char));
				break;
			}
			free(o->fp);
			if (e==ENOENT){
				continue;
			}
			ERROR("fopen_s returned Error Code '%u'\n",e);
			free(o);
			return NULL;
		}
	}
	else{
		o->fp=malloc(_MAX_PATH*sizeof(char));
		assert(_fullpath(o->fp,fp,_MAX_PATH)!=NULL);
		while (*(o->fp+o->fpl)!=0){
			o->fpl++;
		}
		assert(o->fpl>0);
		o->fp=realloc(o->fp,(o->fpl+1)*sizeof(char));
	}
	if (f==NULL){
		free(o);
		return NULL;
	}
	fseek(f,0,SEEK_END);
	o->ln=ftell(f);
	fseek(f,0,SEEK_SET);
	o->dt=malloc(o->ln*sizeof(uint8_t));
	assert(fread(o->dt,sizeof(uint8_t),o->ln,f)==o->ln);
	fclose(f);
	INFO("Found File '%s' as '%s'\n",fp,o->fp);
	return o;
}
