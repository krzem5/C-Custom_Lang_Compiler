#include <common.h>
#include <ast.h>
#include <loader.h>
#include <stdlib.h>
#include <stdio.h>



#define CHR_CMP_RET(c,v) \
	if (*(fo->dt+t->_off)==c){ \
		t->t=AST_TOKEN_TYPE_OPERATOR; \
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



void print_token(ASTToken t){
	switch (t.t){
		case AST_TOKEN_TYPE_UNKNOWN:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_UNKNOWN,\n    err_char = '%c'\n    next_offset = %llu\n};\n",t.dt.u,t._off);
			break;
		case AST_TOKEN_TYPE_STRING:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_STRING,\n    str = '%s'\n    next_offset = %llu\n};\n",t.dt.s.s,t._off);
			break;
		case AST_TOKEN_TYPE_CHAR:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_CHAR,\n    char = '%c'\n    next_offset = %llu\n};\n",t.dt.c,t._off);
			break;
		case AST_TOKEN_TYPE_INT:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_INT,\n    int = %lld\n    next_offset = %llu\n};\n",t.dt.i,t._off);
			break;
		case AST_TOKEN_TYPE_FLOAT:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_FLOAT,\n    float = %lf\n    next_offset = %llu\n};\n",t.dt.f,t._off);
			break;
		case AST_TOKEN_TYPE_KEYWORD:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_KEYWORD,\n    keyword = 0x%hhx\n    next_offset = %llu\n};\n",t.dt.k,t._off);
			break;
		case AST_TOKEN_TYPE_MODIFIER:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_MODIFIER,\n    modifier = 0x%hhx\n    next_offset = %llu\n};\n",t.dt.m,t._off);
			break;
		case AST_TOKEN_TYPE_IDENTIFIER:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_IDENTIFIER,\n    identifier = %s\n    next_offset = %llu\n};\n",t.dt.id.i,t._off);
			break;
		case AST_TOKEN_TYPE_OPERATOR:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_OPERATOR,\n    operator = 0x%hhx\n    next_offset = %llu\n};\n",t.dt.op,t._off);
			break;
		case AST_TOKEN_TYPE_WHITESPACE:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_WHITESPACE,\n    next_offset = %llu\n};\n",t._off);
			break;
		case AST_TOKEN_TYPE_ERROR:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_ERROR,\n    next_offset = %llu\n};\n",t._off);
			break;
		case AST_TOKEN_TYPE_EOF:
			printf("ASTToken = {\n    type = AST_TOKEN_TYPE_EOF\n};\n");
			break;
	}
}



ASTObject ast_parse_file(FileObject fo){
	ASTObject o=malloc(sizeof(struct _AST_OBJECT));
	o->fo=fo;
	ASTToken t={
		AST_TOKEN_TYPE_UNKNOWN,
		._off=0
	};
	assert(next_token(fo,&t)==0);
	INFO("Starting AST Parsing of File '%s'\n",fo->fp);
	while (t.t!=AST_TOKEN_TYPE_EOF){
		assert(t.t!=AST_TOKEN_TYPE_UNKNOWN);
		switch (t.t){
			default:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_UNKNOWN:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_STRING:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_CHAR:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_INT:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_FLOAT:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_KEYWORD:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_MODIFIER:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_IDENTIFIER:
			case AST_TOKEN_TYPE_OPERATOR:
				ast_parse_expression(fo,&t);
				break;
			case AST_TOKEN_TYPE_WHITESPACE:
				assert(!"Not Implemented!");
				break;
			case AST_TOKEN_TYPE_ERROR:
				assert(!"Not Implemented!");
				break;
		}
		print_token(t);
		assert(next_token(fo,&t)==0);
	}
	return o;
}



ASTExpression ast_parse_expression(FileObject fo,ASTToken* t){
	ASTExpression o=malloc(sizeof(struct _AST_EXPRESSION));
	o->t=AST_EXPRESSION_TYPE_EMPTY;
	o->bl=0;
	o->b=NULL;
	switch (t->t){
		default:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_UNKNOWN:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_STRING:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_CHAR:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_INT:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_FLOAT:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_KEYWORD:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_MODIFIER:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_IDENTIFIER:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_OPERATOR:
			ASTToken nt;
			switch (t->dt.op){
				default:
					assert(!"Not Implemented!");
					break;
				case AST_TOKEN_OPERATOR_AMP:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_AT:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_CIRCUMFLEX:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_CLOSE_BRACKET:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_COLON:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_COMMA:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_EQUALS:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_EXCLAMATION_MARK:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_GRATER:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_LEFT_BRACES:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_LEFT_PARENTHESIS:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_LESS:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_MINUS:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_MODULO:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_OPEN_BRACKET:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_PERIOD:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_PLUS:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_QUESTION_MARK:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_RIGHT_BRACES:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_RIGHT_PARENTHESIS:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_SEMICOLON:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_SLASH:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_STAR:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_TILDA:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
				case AST_TOKEN_OPERATOR_VERTICAL_BAR:
					nt._off=t->_off;
					assert(next_token(fo,&nt)==0);
					assert(0);
					break;
			}
			break;
		case AST_TOKEN_TYPE_WHITESPACE:
			assert(!"Not Implemented!");
			break;
		case AST_TOKEN_TYPE_ERROR:
			assert(!"Not Implemented!");
			break;
	}
	return o;
}



uint8_t next_token(FileObject fo,ASTToken* t){
	if (t->_off>=fo->ln){
		t->t=AST_TOKEN_TYPE_EOF;
		return 0;
	}
	t->t=AST_TOKEN_TYPE_UNKNOWN;
	while (*(fo->dt+t->_off)==' '||*(fo->dt+t->_off)=='\t'||*(fo->dt+t->_off)=='\n'||*(fo->dt+t->_off)=='\r'){
		t->t=AST_TOKEN_TYPE_WHITESPACE;
		t->_off++;
	}
	if (t->t==AST_TOKEN_TYPE_WHITESPACE){
		return 0;
	}
	if (*(fo->dt+t->_off)=='"'){
		t->_off++;
		t->t=AST_TOKEN_TYPE_STRING;
		t->dt.s.sl=1;
		t->dt.s.s=NULL;
		uint8_t e=0;
		while (*(fo->dt+t->_off)!='"'){
			uint8_t c=parse_string_char(fo->dt,&(t->_off),&e);
			if (e!=0){
				return e;
			}
			t->dt.s.sl++;
			t->dt.s.s=realloc(t->dt.s.s,t->dt.s.sl*sizeof(char));
			*(t->dt.s.s+t->dt.s.sl-2)=c;
		}
		t->dt.s.sl--;
		*(t->dt.s.s+t->dt.s.sl)=0;
		t->_off++;
		return 0;
	}
	CHR_CMP_RET('&',AST_TOKEN_OPERATOR_AMP)
	CHR_CMP_RET('@',AST_TOKEN_OPERATOR_AT)
	CHR_CMP_RET('^',AST_TOKEN_OPERATOR_CIRCUMFLEX)
	CHR_CMP_RET(']',AST_TOKEN_OPERATOR_CLOSE_BRACKET)
	CHR_CMP_RET(':',AST_TOKEN_OPERATOR_COLON)
	CHR_CMP_RET(',',AST_TOKEN_OPERATOR_COMMA)
	CHR_CMP_RET('=',AST_TOKEN_OPERATOR_EQUALS)
	CHR_CMP_RET('!',AST_TOKEN_OPERATOR_EXCLAMATION_MARK)
	CHR_CMP_RET('>',AST_TOKEN_OPERATOR_GRATER)
	CHR_CMP_RET('{',AST_TOKEN_OPERATOR_LEFT_BRACES)
	CHR_CMP_RET('(',AST_TOKEN_OPERATOR_LEFT_PARENTHESIS)
	CHR_CMP_RET('<',AST_TOKEN_OPERATOR_LESS)
	CHR_CMP_RET('-',AST_TOKEN_OPERATOR_MINUS)
	CHR_CMP_RET('%',AST_TOKEN_OPERATOR_MODULO)
	CHR_CMP_RET('[',AST_TOKEN_OPERATOR_OPEN_BRACKET)
	CHR_CMP_RET('.',AST_TOKEN_OPERATOR_PERIOD)
	CHR_CMP_RET('+',AST_TOKEN_OPERATOR_PLUS)
	CHR_CMP_RET('?',AST_TOKEN_OPERATOR_QUESTION_MARK)
	CHR_CMP_RET('}',AST_TOKEN_OPERATOR_RIGHT_BRACES)
	CHR_CMP_RET(')',AST_TOKEN_OPERATOR_RIGHT_PARENTHESIS)
	CHR_CMP_RET(';',AST_TOKEN_OPERATOR_SEMICOLON)
	CHR_CMP_RET('/',AST_TOKEN_OPERATOR_SLASH)
	CHR_CMP_RET('*',AST_TOKEN_OPERATOR_STAR)
	CHR_CMP_RET('~',AST_TOKEN_OPERATOR_TILDA)
	CHR_CMP_RET('|',AST_TOKEN_OPERATOR_VERTICAL_BAR)
	size_t i;
	STR_CMP_RET("as",2,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_AS)
	STR_CMP_RET("assert",6,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_ASSERT)
	STR_CMP_RET("class",5,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_CLASS)
	STR_CMP_RET("def",3,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_DEF)
	STR_CMP_RET("debugger",8,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_DEBUGGER)
	STR_CMP_RET("delete",6,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_DELETE)
	STR_CMP_RET("elif",4,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_ELIF)
	STR_CMP_RET("else",4,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_ELSE)
	STR_CMP_RET("for",3,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_FOR)
	STR_CMP_RET("if",2,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_IF)
	STR_CMP_RET("import",6,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_IMPORT)
	STR_CMP_RET("raise",5,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_RAISE)
	STR_CMP_RET("return",6,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_RETURN)
	STR_CMP_RET("while",5,k,AST_TOKEN_TYPE_KEYWORD,AST_TOKEN_KEYWORD_WHILE)
	STR_CMP_RET("public",6,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_PUBLIC)
	STR_CMP_RET("private",7,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_PRIVATE)
	STR_CMP_RET("static",6,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_STATIC)
	STR_CMP_RET("export",6,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_EXPORT)
	STR_CMP_RET("frozen",6,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_FROZEN)
	STR_CMP_RET("frozentype",10,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_FROZENTYPE)
	STR_CMP_RET("const",5,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_CONST)
	STR_CMP_RET("operator",8,m,AST_TOKEN_TYPE_MODIFIER,AST_TOKEN_MODIFIER_OPERATOR)
	t->dt.id.il=1;
	t->dt.id.i=NULL;
	while ((*(fo->dt+t->_off)>47&&*(fo->dt+t->_off)<58)||(*(fo->dt+t->_off)>64&&*(fo->dt+t->_off)<91)||*(fo->dt+t->_off)==95||(*(fo->dt+t->_off)>96&&*(fo->dt+t->_off)<123)||*(fo->dt+t->_off)>126){
		t->dt.id.il++;
		t->dt.id.i=realloc(t->dt.id.i,t->dt.id.il+1);
		*((char*)t->dt.id.i+t->dt.id.il-2)=*(fo->dt+t->_off);
		t->_off++;
	}
	if (t->dt.id.il>1){
		t->dt.id.il--;
		t->t=AST_TOKEN_TYPE_IDENTIFIER;
		*(t->dt.id.i+t->dt.id.il)=0;
		return 0;
	}
	assert(t->t==AST_TOKEN_TYPE_UNKNOWN);
	t->dt.u=*(fo->dt+t->_off);
	return 0;
}



uint8_t parse_string_char(uint8_t* s,size_t* i,uint8_t* e){
	*e=0;
	if (*(s+*i)=='\\'){
		(*i)+=2;
		switch (*(s+*i-1)){
			case 'b':
				return 0x08;
			case 'd':
				{
					uint8_t o=0;
					bool f=false;
					while (48<=*(s+*i)&&*(s+*i)<=57){
						if (o<255){
							f=true;
							if ((unsigned short)o*10+*(s+*i)-48>255){
								o=255;
								break;
							}
							o=o*10+*(s+*i)-48;
						}
						(*i)++;
					}
					if (f==false){
						*e=2;
						return 0;
					}
					return o;
				}
			case 'e':
				return 0x1b;
			case 'f':
				return 0x0c;
			case 'n':
				return 0x0a;
			case 'o':
				{
					uint8_t o=0;
					bool f=false;
					while (48<=*(s+*i)&&*(s+*i)<=55){
						if (o<255){
							f=true;
							if ((unsigned short)o*8+*(s+*i)-48>255){
								o=255;
								break;
							}
							o=o*8+*(s+*i)-48;
						}
						(*i)++;
					}
					if (f==false){
						*e=3;
						return 0;
					}
					return o;
				}
			case 'r':
				return 0x0d;
			case 't':
				return 0x09;
			case 'v':
				return 0x0b;
			case 'x':
				{
					uint8_t o=0;
					bool f=false;
					while ((48<=*(s+*i)&&*(s+*i)<=57)||(97<=*(s+*i)&&*(s+*i)<=102)){
						if (o<255){
							f=true;
							if ((unsigned short)o*16+(*(s+*i)<=57?*(s+*i)-48:*(s+*i)-87)>255){
								o=255;
								break;
							}
							o=o*16+(*(s+*i)<=57?*(s+*i)-48:*(s+*i)-87);
						}
						(*i)++;
					}
					if (f==false){
						*e=4;
						return 0;
					}
					return o;
				}
			case '\'':
				return 0x27;
			case '\"':
				return 0x22;
			default:
				(*i)--;
				*e=1;
				return 0;
		}
	}
	uint8_t o=*(s+*i);
	(*i)++;
	return o;
}
