#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "lexer.h"
int main(int argc,char* argv[])
{
	if (argc >= 2) {
		auto fp = fopen(argv[1], "r");
		fseek(fp, 0L, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* buf = new char[size + 1];
		memset(buf, 0, size + 1);
		fread(buf, 1, size, fp);

		Lexer lexer(buf);
		while (1) {
			Token token = lexer.NextToken();
			if (token.type_ == Token::TOK_EOF)
				break;
			cout << token.print() << endl;
		}
	}
	else {
		while (1) {
			string s;
			cout << ">> ";
			getline(cin, s);
			Lexer lexer(s);
			while (1) {
				Token token = lexer.NextToken();
				if (token.type_ == Token::TOK_EOF)
					break;
				cout << token.print() << endl;
			}
			cout << endl;
		}
	}
}


