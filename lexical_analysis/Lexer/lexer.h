#ifndef LEXER_H
#define LEXER_H

#include "token.h"
using namespace std;
class Lexer
{
public:
	Lexer(string src) :src_(src), pos_(0), next_pos_(0), line_no_(0){ read_char(); }
	Token NextToken();
private:
	string src_;
	char chr_;//当前读取的字符
	int pos_;//当前所在的位置
	int next_pos_;//下一个字符所在的位置
	int line_no_;
	Token read_number();
	Token read_id();
	void read_char();
	char peek_char();
	void skip_whitespace();
};

#endif