#ifndef SCANNER_H
#define SCANNER_H

	#include <vector>

	#define TOKEN_IMPLEMENTATION
	#include "Token.h"
	class Scanner {
		private:
			std::string source;
			std::vector<Token> tokens;

			int start = 0;
			int current = 0;
			int line = 1;

            bool isAtEnd();
            void scanToken();
		public:
            Scanner(std::string source);
            std::vector<Token> scanTokens();
    };

#endif // SCANNER_H

#ifdef SCANNER_IMPLEMENTATION

	Scanner::Scanner(std::string source) {
		this->source = source;
	}

	std::vector<Token> Scanner::scanTokens() {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}

		tokens.push_back(Token(EOF_TOKEN, "", Literal(), line));
		return tokens;
	}
	
	void Scanner::scanToken() {
		std::cout << "tnsehtn\n";
	}

	bool Scanner::isAtEnd() {
		return static_cast<unsigned long int>(current) >= source.length();
	}

#endif // SCANNER_IMPLEMENTATION
