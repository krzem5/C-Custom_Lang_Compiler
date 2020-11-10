#include <common.h>
#include <ast.h>
#include <loader.h>
#include <stdlib.h>
#include <stdio.h>



#define CHR_CMP_RET(c,v) \
	if (*(fo->dt+t->_off)==c){ \
		t->t=TOKEN_TYPE_OPERATOR; \
		t->dt.op=v; \
		t->_off++; \
		return 0; \
	}
#define STR_CMP_RET(s,l,_t,tt,tv) \
	if (t->_off+l<=fo->ln){ \
		for (i=0;i<l;i++){ \
			if (*(fo->dt+t->_off+i)!=*(s+i)){ \
				i=INTMAX_MAX; \
				break; \
			} \
		} \
		if (i!=INTMAX_MAX&&(t->_off+l==fo->ln||(!((*(fo->dt+t->_off+l)>47&&*(fo->dt+t->_off+l)<58)||(*(fo->dt+t->_off+l)>64&&*(fo->dt+t->_off+l)<91)||*(fo->dt+t->_off+l)==95||(*(fo->dt+t->_off+l)>96&&*(fo->dt+t->_off+l)<123)||*(fo->dt+t->_off+l)>126)))){ \
			t->t=tt; \
			t->dt._t=tv; \
			t->_off+=l; \
			return 0; \
		} \
	}



ASTObject ast_parse_file(FileObject fo){
	ASTObject o=malloc(sizeof(struct _AST_OBJECT));
	o->fo=fo;
	Token t={
		TOKEN_TYPE_UNKNOWN,
		._off=0
	};
	INFO("Starting AST Parsing of File '%s'\n",fo->fp);
	while (t.t!=TOKEN_TYPE_EOF){
		assert(next_token(fo,&t)==0);
		printf("Token Type: %u, Off=%llu\n",t.t,t._off);
		assert(t.t!=TOKEN_TYPE_UNKNOWN);
	}
	return o;
}



uint8_t next_token(FileObject fo,Token* t){
	if (t->_off>=fo->ln){
		t->t=TOKEN_TYPE_EOF;
		return 0;
	}
	t->t=TOKEN_TYPE_UNKNOWN;
	while (*(fo->dt+t->_off)==' '||*(fo->dt+t->_off)=='\t'||*(fo->dt+t->_off)=='\n'||*(fo->dt+t->_off)=='\r'){
		t->t=TOKEN_TYPE_WHITESPACE;
		t->_off++;
	}
	if (t->t==TOKEN_TYPE_WHITESPACE){
		return 0;
	}
	CHR_CMP_RET(';',TOKEN_OPERATOR_SEMICOLON)
	CHR_CMP_RET('.',TOKEN_OPERATOR_PERIOD)
	CHR_CMP_RET(',',TOKEN_OPERATOR_COMMA)
	if (*(fo->dt+t->_off)=='"'){
		t->_off++;
		t->t=TOKEN_TYPE_STRING;
		t->dt.s.sl=0;
		t->dt.s.s=NULL;
		uint8_t e=0;
		while (*(fo->dt+t->_off)!='"'){
			uint8_t c=parse_string_char(fo,t,&e);
			if (e!=0){
				return e;
			}
			t->dt.s.sl++;
			t->dt.s.s=realloc(t->dt.s.s,t->dt.s.sl*sizeof(char));
			*(t->dt.s.s+t->dt.s.sl-1)=c;
		}
		t->_off++;
		return 0;
	}
	size_t i;
	STR_CMP_RET("import",6,k,TOKEN_TYPE_KEYWORD,TOKEN_KEYWORD_IMPORT)
	t->dt.i.il=0;
	t->dt.i.i=NULL;
	while ((*(fo->dt+t->_off)>47&&*(fo->dt+t->_off)<58)||(*(fo->dt+t->_off)>64&&*(fo->dt+t->_off)<91)||*(fo->dt+t->_off)==95||(*(fo->dt+t->_off)>96&&*(fo->dt+t->_off)<123)||*(fo->dt+t->_off)>126){
		t->dt.i.il++;
		t->dt.i.i=realloc(t->dt.i.i,t->dt.i.il+1);
		*((char*)t->dt.i.i+t->dt.i.il-1)=*(fo->dt+t->_off);
		t->_off++;
	}
	if (t->dt.i.il>0){
		t->t=TOKEN_TYPE_IDENTIFIER;
		return 0;
	}
	assert(t->t==TOKEN_TYPE_UNKNOWN);
	t->dt.u=*(fo->dt+t->_off);
	return 0;
}



uint8_t parse_string_char(FileObject fo,Token* t,uint8_t* e){
	*e=0;/****/
	t->_off++;
	return 0;
}
