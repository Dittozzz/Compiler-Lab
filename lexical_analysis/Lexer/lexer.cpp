#include "lexer.h"
#include <iostream>
#include <cstring>
#include <cctype>
void
Lexer::read_char()
{
	if (next_pos_ >= src_.length()) {
		chr_ = 0;
		pos_ = next_pos_;
		return;
	}
	chr_ = src_[next_pos_];
	pos_ = next_pos_;
	next_pos_ += 1;
}

char 
Lexer::peek_char()
{
	if (next_pos_ >= src_.length()) {
		return 0;
	}
	return src_[next_pos_];
}

void
Lexer::skip_whitespace()
{
	char white[] = { '\n',' ','\r','\t' };
	while (std::find(begin(white), end(white), chr_) != end(white))
	{
		if (chr_ == '\n')
			line_no_ += 1;
		read_char();
	}
}

Token 
Lexer::read_number()
{
	int pos = pos_;
	while (isdigit(chr_)) {
		read_char();
	}
	return Token(Token::TOK_NUMB, src_.substr(pos, pos_ - pos), line_no_);
}

Token
Lexer::read_id()
{
	int pos = pos_;
	while (isalnum(chr_) || chr_ == '_') {
		read_char();
	}
	string lexeme = src_.substr(pos, pos_ - pos);
	auto type = Token::LookUp(lexeme);
	return Token(type, lexeme, line_no_);
}

Token
Lexer::NextToken()
{
	Token token(Token::TOK_EOF,line_no_);
	skip_whitespace();
	switch (chr_)
	{
	case '(':
		token = Token(Token::TOK_LPAREN, "(", line_no_);
		break;
	case ')':
		token = Token(Token::TOK_RPAREN, ")", line_no_);
		break;
	case ',':
		token = Token(Token::TOK_COMMA, ",", line_no_);
		break;
	case '.':
		token = Token(Token::TOK_DOT, ".", line_no_);
		break;
	case ';':
		token = Token(Token::TOK_SEMIC, ";", line_no_);
		break;
	case '+':
		token = Token(Token::TOK_PLUS, "+", line_no_);
		break;
	case '-':
		token = Token(Token::TOK_SUB, "-", line_no_);
		break;
	case '*':
		token = Token(Token::TOK_MUL, "*", line_no_);
		break;
	case '/':
		if (peek_char() == '*')//×¢ÊÍ
		{
			read_char();//ÏûºÄµô'/' , chr_ = '*'
			read_char();//ÏûºÄµô'*' , chr_ = ?
 			while (chr_ != '*') {
				read_char();
			}
			read_char();
		}
		else {
			token = Token(Token::TOK_DIV, "/", line_no_);
		}
		break;
	case ':':
		if (peek_char() == '=') {
			read_char();
			token = Token(Token::TOK_ASSIGN, ":=", line_no_);
		}
		else {
			std::cerr << "Lexer: except '=' after ':' in line " + std::to_string(line_no_) << std::endl;
			return token;
		}
		break;
	case '<':
		token = Token(Token::TOK_LESS, "<", line_no_);
		break;
	case '<=':
		token = Token(Token::TOK_LQ, "<=", line_no_);
		break;
	case '>':
		token = Token(Token::TOK_GREATE, ">", line_no_);
		break;
	case '>=':
		token = Token(Token::TOK_GQ, ">=", line_no_);
		break;
	case '#':
		token = Token(Token::TOK_POUND, "#", line_no_);
		break;
	case '{':
			read_char();//ÏûºÄµô'{'
			while (chr_ != '}')
				read_char();
			break;
	default:
		if (isdigit(chr_)){
			token = read_number();
			return token;
		}
		else if (isalpha(chr_)) {
			token = read_id();
			return token;
		}
		else {
			if (chr_ == 0)
				break;
			std::cerr << "unexpected char '"<<chr_<<"' in line " << to_string(line_no_) << endl;
		}
		break;
	}
	read_char();
	return token;
}