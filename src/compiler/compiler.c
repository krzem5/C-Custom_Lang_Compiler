#include <common.h>
#include <compiler.h>
#include <loader.h>
#include <free.h>
#include <stdio.h>
#include <stdlib.h>



int compiler_run_all(int argc,const char** argv){
	uint32_t fpll=0;
	char** fpl=NULL;
	for (int i=1;i<argc;i++){
		size_t j=0;
		while (*(*(argv+i)+j)=='\t'||*(*(argv+i)+j)=='\n'||*(*(argv+i)+j)=='\r'){
			j++;
		}
		if (*(*(argv+i)+j)==0){
			continue;
		}
		if (*(*(argv+i)+j)=='-'){
			j++;
			switch (*(*(argv+i)+j)){
				case 'I':
					loader_add_search_path((char*)*(argv+i)+j+1);
					break;
				default:
					ERROR("Unknown Switch '%s'\n",*(argv+i));
					return 1;
			}
		}
		else{
			fpll++;
			fpl=realloc(fpl,fpll*sizeof(char*));
			*(fpl+fpll-1)=(char*)*(argv+i);
		}
	}
	if (fpll==0){
		ERROR("No Files Specified. Stopping compilation.\n");
		return 1;
	}
	for (uint32_t i=0;i<fpll;i++){
		FileObject f=loader_load_file(*(fpl+i));
		if (f==NULL){
			ERROR("File '%s' not Found within the Provided Search Path.\n",*(fpl+i));
			return 1;
		}
		ASTObject ast=ast_parse_file(f);
		if (ast==NULL){
			ERROR("AST ERROR!\n");
			return 1;
		}
		free_ast_object(ast);
		free_file_object(f);
	}
	free(fpl);
	return 0;
}
