#ifndef TOKEN_H
#define TOKEN_H

	#define STR_SIZE 1024

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

	enum Literal_tag {
		STR,
		NUM,
		NOTHING
	};

	union Literal_value {
		char s[STR_SIZE];
		int i; 
	};

	struct Literal {
		Literal_tag type;
		Literal_value value;
	};

	class Token
	{
		private:
			TokenType type;
			std::string lexeme;
			Literal literal;
			int line;

            std::string literalToString(const Literal &literal);
		public:
            Token(TokenType type, std::string lexeme, Literal literal, int line);
            std::string toString();
    };

#endif // TOKEN_H

#ifdef TOKEN_IMPLEMENTATION

	Token::Token(TokenType type, std::string lexeme, Literal literal, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->literal.type = literal.type;
		switch (literal.type) {
			case STR:
				std::copy(std::begin(literal.value.s), std::end(literal.value.s), std::begin(this->literal.value.s));	
				break;
			case NUM:
				this->literal.value.i = literal.value.i;
				break;
			case NOTHING:
				this->literal.value.i = 0;
				break;
		}
		this->line = line;
	}

	std::string Token::toString() {
		return this->type + " " + this->lexeme + " " + literalToString(this->literal);
	}

	std::string Token::literalToString(const Literal& literal) {
		switch (literal.type) {
			case STR:
				return std::string{literal.value.s};
			case NUM:
				return std::to_string(literal.value.i);
			default:
				return "Nothing";
		}
	}

#endif // TOKEN_IMPLEMENTATION