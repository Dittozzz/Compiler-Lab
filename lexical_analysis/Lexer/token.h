#ifndef TOKEN_H
#define TOKEN_H
#include <unordered_map>
#include<string>
using namespace std;

#define KEYWORD_TOKEN(v)			\
	v("begin",TOK_BEGIN)			\
	v("call",TOK_CALL)				\
	v("const",TOK_CONST)			\
	v("do",TOK_DO)				    \
	v("end",TOK_END)				\
	v("if",TOK_IF)					\
	v("odd",TOK_ODD)				\
	v("procedure",TOK_PROCEDURE)	\
	v("read",TOK_READ)				\
	v("then",TOK_THEN)				\
	v("var",TOK_VAR)				\
	v("while",TOK_WHILE)			\
	v("write",TOK_WRITE)			

#define TOKEN_LIST(v)				\
	v("number",TOK_NUMB)			\
	v("id",TOK_ID)					\
	v("(",TOK_LPAREN)				\
	v(")",TOK_RPAREN)				\
	v(",",TOK_COMMA)				\
	v(".",TOK_DOT)					\
	v(";",TOK_SEMIC)				\
	v("+",TOK_PLUS)					\
	v("-",TOK_SUB)					\
	v("*",TOK_MUL)					\
	v("/",TOK_DIV)					\
	v(":=",TOK_ASSIGN)				\
	v("<",TOK_LESS)					\
	v("<=",TOK_LQ)					\
	v(">",TOK_GREATE)				\
	v(">=",TOK_GQ)					\
	v("#",TOK_POUND)				\
	KEYWORD_TOKEN(v)		

class Token
{
public:
	enum token_type
	{
	#define v(str,TOK) TOK,
		TOKEN_LIST(v)
		TOK_EOF
	#undef v
	};
	Token(){}
	Token(token_type type, string lexeme,int line) :type_(type), lexeme_(lexeme),line_(line) {}
	Token(token_type type,int line) :type_(type),line_(line) {}
	token_type type_;
	string lexeme_;
	int line_;
	bool IsKeyword();
	static unordered_map<string, Token::token_type> keyword_;
	static token_type LookUp(string str);
	string& toString();
	string print();
};

#endif // !TOKEN_H