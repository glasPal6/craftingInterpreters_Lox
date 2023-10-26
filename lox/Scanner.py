from TokenType import TokenType
from Token import Token
from Lox import Lox
class Scanner:
	def __init__(self, source: str) -> None:
		self.__source = source
		self.__tokens: list[Token] = []

		# Track where the scanner is in the source code
		self.start: int = 0		# Start of the lexme
		self.current: int = 0	# Current character
		self.line: int = 1		# Line number

	def scanTokens(self) -> list[Token]:
		while (not self.__isAtEnd()):
			start = self.current
			self.__scanToken()

		self.__tokens.append(Token(TokenType.EOF, "", None, self.line))
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

			case _:
				Lox.error(self.line, "Unexpected character.")

	def __isAtEnd(self) -> bool:
		return self.current >= len(self.__source)

	def __advance(self) -> chr:
		self.current += 1
		return self.__source[self.current-1]

	def __addToken(self, type: TokenType):
		self.__addToken(self, type, None)

	def __addToken(self, type: TokenType, literal: object):
		text: str = self.__source[self.start, self.current]
		self.__tokens.append(Token(type, text, literal, self.line))

	def __match(self, expected: chr) -> bool:
		if self.__isAtEnd(): return False
		if self.__source[self.current] != expected: return False

		self.current += 1
		return True

	def __peek(self) -> chr:
		if self.__isAtEnd(): return '\0'
		return self.__source[self.current]
