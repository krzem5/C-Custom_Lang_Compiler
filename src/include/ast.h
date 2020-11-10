#ifndef __PARSER_H__
#define __PARSER_H__
#include <common.h>
#include <loader.h>
#include <stdio.h>



typedef struct _TOKEN Token;
typedef struct _AST_OBJECT* ASTObject;



enum TOKEN_TYPE{
	TOKEN_TYPE_UNKNOWN=0x00,
	TOKEN_TYPE_WHITESPACE=0x01,
	TOKEN_TYPE_MODIFIER=0x02,
	TOKEN_TYPE_KEYWORD=0x03,
	TOKEN_TYPE_INT=0x04,
	TOKEN_TYPE_IDENTIFIER=0x05,
	TOKEN_TYPE_OPERATOR=0x06,
	TOKEN_TYPE_STRING=0x07,
	TOKEN_TYPE_ERROR=0xfe,
	TOKEN_TYPE_EOF=0xff
};



enum TOKEN_MODIFIER{
	TOKEN_MODIFIER_UNKNOWN=0x00,
	TOKEN_MODIFIER_CONST=0x01,
	TOKEN_MODIFIER_PUBLIC=0x02,
	TOKEN_MODIFIER_PRIVATE=0x04,
	TOKEN_MODIFIER_STATIC=0x08,
	TOKEN_MODIFIER_EXPORT=0x10
};



enum TOKEN_KEYWORD{
	TOKEN_KEYWORD_UNKNOWN=0x00,
	TOKEN_KEYWORD_IF=0x01,
	TOKEN_KEYWORD_CLASS=0x02,
	TOKEN_KEYWORD_IMPORT=0x03
};



enum TOKEN_OPERATOR{
	TOKEN_OPERATOR_UNKNOWN=0x00,
	TOKEN_OPERATOR_SEMICOLON=0x01,
	TOKEN_OPERATOR_PERIOD=0x02,
	TOKEN_OPERATOR_COMMA=0x03
};



struct _TOKEN{
	enum TOKEN_TYPE t;
	union _TOKEN_DATA{
		char u;
		enum TOKEN_MODIFIER m;
		enum TOKEN_KEYWORD k;
		enum TOKEN_OPERATOR op;
		struct _TOKEN_DATA_IDENTIFIER{
			size_t il;
			char* i;
		} i;
		struct _TOKEN_DATA_STRING{
			size_t sl;
			char* s;
		} s;
	} dt;
	size_t _off;
};



struct _AST_OBJECT{
	FileObject fo;
};



// typedef struct _TYPE* Type;
// typedef struct _MODULE_DECL* ModuleDecl;
// typedef struct _MODULE_DECL_LIST* ModuleDeclList;
// typedef struct _PARSER_FILE* ParserFile;



// enum MODULE_DECL_FLAGS{
// 	MODULE_DECL_FLAG_VAR=0x00,
// 	MODULE_DECL_FLAG_FUNC=0x01,
// 	MODULE_DECL_FLAG_CLASS=0x02,
// 	MODULE_DECL_FLAG_ENUM=0x03,
// 	MODULE_DECL_FLAG_CONST=0x80
// };



// struct _TYPE{
// 	size_t nml;
// 	const char* nm;
// };



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



ASTObject ast_parse_file(FileObject fo);



uint8_t next_token(FileObject fo,Token* t);



uint8_t parse_string_char(FileObject fo,Token* t,uint8_t* e);



#endif
