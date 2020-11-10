#ifndef __PARSER_H__
#define __PARSER_H__
#include <common.h>
#include <stdio.h>



typedef struct _TYPE* Type;
typedef struct _MODULE_DECL* ModuleDecl;
typedef struct _MODULE_DECL_LIST* ModuleDeclList;
typedef struct _PARSER_FILE* ParserFile;



enum MODULE_DECL_FLAGS{
	MODULE_DECL_FLAG_VAR=0x00,
	MODULE_DECL_FLAG_FUNC=0x01,
	MODULE_DECL_FLAG_CLASS=0x02,
	MODULE_DECL_FLAG_ENUM=0x03,
	MODULE_DECL_FLAG_CONST=0x80
};



struct _TYPE{
	size_t nml;
	const char* nm;
};



/*struct _MODULE_DECL{
	size_t nml;
	char* nm;
	uint8_t f;
	union _MODULE_DECL_DATA{
		struct _MODULE_DECL_DATA_VAR{
			Type t;
		} v;
		struct _MODULE_DECL_DATA_FUNC{
			Type rt;
			uint8_t al;
			struct _MODULE_DECL_DATA_FUNC_ARG{
				Type t;
				bool opt;
			}* a;
		} f;
		struct _MODULE_DECL_DATA_CLASS{
			uint8_t bl;
			Type* b;
		} c;
		struct _MODULE_DECL_DATA_ENUM{
			uint8_t bl;
			Type* b;
		} c;
	} dt;
};*/



struct _MODULE_DECL_LIST{
	ParserFile f;
	size_t dc;
	struct _MODULE_DECL* d;
};



struct _PARSER_FILE{
	const char* fp;
	size_t ln;
	FILE* f;
};



#endif
