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
	char chr_;//��ǰ��ȡ���ַ�
	int pos_;//��ǰ���ڵ�λ��
	int next_pos_;//��һ���ַ����ڵ�λ��
	int line_no_;
	Token read_number();
	Token read_id();
	void read_char();
	char peek_char();
	void skip_whitespace();
};

#endif