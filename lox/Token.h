#ifndef TOKEN_H
#define TOKEN_H

	#include <string>

	enum TokenType {
		// Single-character tokens.
		LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
		COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

		// One or two character tokens.
		BANG, BANG_EQUAL,
		EQUAL, EQUAL_EQUAL,
		GREATER, GREATER_EQUAL,
		LESS, LESS_EQUAL,

		// Literals.
		IDENTIFIER, STRING, NUMBER,

		// Keywords.
		AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
		PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

		EOF_TOKEN
	};

	class Token
	{
		private:
			TokenType type;
			std::string lexeme;
			std::string literal;
			int line;

		public:
            Token(TokenType type, std::string lexeme, std::string literal, int line);
			std::string toString();
        };

#endif // TOKEN_H

#ifdef TOKEN_IMPLEMENTATION

	Token::Token(TokenType type, std::string lexeme, std::string literal, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->literal = literal;
		this->line = line;
	}

	std::string Token::toString() {
		return this->type + " " + this->lexeme + " " * this->literal;
	}

#endif // TOKEN_IMPLEMENTATION