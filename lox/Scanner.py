from TokenType import TokenType
from Token import Token
from Errors import Errors

class Scanner:
	def __init__(self, source: str) -> None:
		self.errors = Errors()
		self.__source = source
		self.__tokens: list[Token] = []

		# Track where the scanner is in the source code
		self.__start: int = 0		# Start of the lexme
		self.__current: int = 0	# Current character
		self.__line: int = 1		# Line number
		self.__keywords: dict = {
			"and" : 	TokenType.AND,
			"class" : 	TokenType.CLAS,
			"else" : 	TokenType.ELSE,
			"false" : 	TokenType.FALSE,
			"for" : 	TokenType.FOR,
			"fun" : 	TokenType.FUN,
			"if" : 		TokenType.IF,
			"nil" : 	TokenType.NIL,
			"or" : 		TokenType.OR,
			"print" : 	TokenType.PRINT,
			"return" : 	TokenType.RETURN,
			"super" : 	TokenType.SUPER,
			"this" : 	TokenType.THIS,
			"true" : 	TokenType.TRUE,
			"var" : 	TokenType.VAR,
			"while" : 	TokenType.WHILE,
		}

	def scanTokens(self) -> list[Token]:
		while (not self.__isAtEnd()):
			self.__start = self.__current
			self.__scanToken()

		self.__tokens.append(Token(TokenType.EOF, "", None, self.__line))
		return self.__tokens

	def __scanToken(self):
		c: chr = self.__advance()

		match c:
			# Single character tokens
			case '(': self.__addToken(TokenType.LEFT_PAREN)
			case ')': self.__addToken(TokenType.RIGHT_PAREN)
			case '{': self.__addToken(TokenType.LEFT_BRACE)
			case '}': self.__addToken(TokenType.RIGHT_BRACE)
			case ',': self.__addToken(TokenType.COMMA)
			case '.': self.__addToken(TokenType.DOT)
			case '-': self.__addToken(TokenType.MINUS)
			case '+': self.__addToken(TokenType.PLUS)
			case ';': self.__addToken(TokenType.SEMICOLON)
			case '*': self.__addToken(TokenType.STAR)

			# One or more character tokens	
			case '!': self.__addToken(TokenType.BANG_EQUAL if self.__match('=') else TokenType.BANG)
			case '=': self.__addToken(TokenType.EQUAL_EQUAL if self.__match('=') else TokenType.EQUAL)
			case '<': self.__addToken(TokenType.LESS_EQUAL if self.__match('=') else TokenType.LESS)
			case '>': self.__addToken(TokenType.GREATER_EQUAL if self.__match('=') else TokenType.GREATER)

			# For comments and division
			case '/':
				if self.__match('/'):
					while self.__peek() != '\n' and not self.__isAtEnd(): self.__advance()
				else: self.__addToken(TokenType.SLASH)

			# Useless characters
			case ' ' | '\r' | '\t': None
			case '\n':
				self.__line += 1

			# Literals
			case '"': self.__string()

			case _:
				if self.__isDigit(c): self.__number()
				elif self.__isAlpha(c): self.__identifier()
				else: self.errors.error(self.__line, "Unexpected character.")

	def __identifier(self):
		while self.__isAlphaNumeric(self.__peek()): self.__advance()

		text: str = self.__source[self.__start:self.__current]
		if text in self.__keywords: tType: TokenType = self.__keywords[text]
		else: tType = TokenType.IDENTIFIER

		self.__addToken(tType)

	def __number(self):
		while self.__isDigit(self.__peek()): self.__advance()

		# Look for the fractional part
		if self.__peek() == '.' and self.__isDigit(self.__peekNext()):
			# Go over the '.'
			self.__advance()

			while self.__isDigit(self.__peek()): self.__advance()

		self.__addToken(TokenType.NUMBER, float(self.__source[self.__start:self.__current]))

	def __string(self):
		while p:=self.__peek() != '"' and not self.__isAtEnd():
			if p == '\n': self.__line += 1
			self.__advance()

		if self.__isAtEnd():
			self.errors.error(self.__line, "Unterminated string.")
			return
		
		# The closing "
		self.__advance()

		# Trim the quotes and add the token
		value: str = self.__source[self.__start+1:self.__current-1]
		self.__addToken(TokenType.STRING, value)

	def __isAtEnd(self) -> bool:
		return self.__current >= len(self.__source)

	def __advance(self) -> chr:
		self.__current += 1
		return self.__source[self.__current-1]

	def __addToken(self, tType: TokenType, literal: object=None):
		text: str = self.__source[self.__start:self.__current]
		self.__tokens.append(Token(tType, text, literal, self.__line))

	def __match(self, expected: chr) -> bool:
		if self.__isAtEnd(): return False
		if self.__source[self.__current] != expected: return False

		self.__current += 1
		return True

	def __peek(self) -> chr:
		if self.__isAtEnd(): return '\0'
		return self.__source[self.__current]
	
	def __peekNext(self) -> chr:
		if self.__current + 1 >= len(self.__source): return '\0'
		return self.__source[self.__current + 1]

	def __isDigit(self, c: chr) -> bool:
		return c >= '0' and c <= '9'

	def __isAlpha(self, c: chr) -> bool:
		return (
			(c >= 'a' and c <= 'z') or
			(c >= 'A' and c <= 'Z') or 
			c == '_'
		)
	
	def __isAlphaNumeric(self, c: chr) -> bool:
		return self.__isAlpha(c) or self.__isDigit(c)

