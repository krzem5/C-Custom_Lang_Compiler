#include <common.h>
#include <free.h>
#include <loader.h>
#include <ast.h>
#include <stdio.h>
#include <stdlib.h>



void free_file_object(FileObject fo){
	assert(fo->fp!=NULL);
	assert(fo->dt!=NULL);
	free(fo->fp);
	free(fo->dt);
	free(fo);
}



void free_ast_object(ASTObject ast){
	free(ast);
}
