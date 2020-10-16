#include "token.h"

unordered_map<string, Token::token_type>
Token::keyword_ = {

#define v(str,token) {str,Token::token},
		TOKEN_LIST(v)
		{"TOK_EOF",Token::TOK_EOF}
#undef v

};

bool
Token::IsKeyword()
{
	if (type_ >= TOK_BEGIN && type_ <= TOK_WRITE)
		return true;
	return false;
}

Token::token_type
Token::LookUp(string str)
{
	auto it = keyword_.find(str);
	if (it != keyword_.end())
	{
		return it->second;
	}
	return Token::TOK_ID;
}

string&
Token::toString()
{
	return lexeme_;
}

string
Token::print()
{
	unordered_map<token_type, string> token_map = {
	#define v(str,tok) {tok,str},
		TOKEN_LIST(v)
		{TOK_EOF,"EOF"}
	#undef v
	};
	string s;
	if (IsKeyword()) {
		s += "(Keyword) " + lexeme_;
		return s;
	}
	auto it = token_map.find(type_);
	s += "(" + it->second + ") " + lexeme_;
	return s;
}