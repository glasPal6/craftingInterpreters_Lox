from TokenType import TokenType
from Token import Token

class Scanner:
	def __init__(self, source: str) -> None:
		self.__source = source
		self.__tokens: list[Token] = []

		# Track where the scanner is in the source code
		self.start: int = 0		# Start of the lexme
		self.current: int = 0	# Current character
		self.line: int = 1		# Line number

	def scanTokens(self) -> list[Token]:
		while (not self.isAtEnd()):
			start = self.current
			self.scanToken()

		self.__tokens.append(Token(TokenType.EOF, "", None, self.line))
		return self.__tokens

	def scanToken(self):
		c: chr = self.advance()
		match c:
			case '(': self.addToken(TokenType.LEFT_PAREN)
			case ')': self.addToken(TokenType.RIGHT_PAREN)
			case '{': self.addToken(TokenType.LEFT_BRACE)
			case '}': self.addToken(TokenType.RIGHT_BRACE)
			case ',': self.addToken(TokenType.COMMA)
			case '.': self.addToken(TokenType.DOT)
			case '-': self.addToken(TokenType.MINUS)
			case '+': self.addToken(TokenType.PLUS)
			case ';': self.addToken(TokenType.SEMICOLON)
			case '*': self.addToken(TokenType.STAR)

	def isAtEnd(self) -> bool:
		return self.current >= len(self.__source)

	def advance(self) -> chr:
		self.current += 1
		return self.__source[self.current-1]

	def addToken(self, type: TokenType):
		self.addToken(self, type, None)

	def addToken(self, type: TokenType, literal: object):
		text: str = self.__source[self.start, self.current]
		self.__tokens.append(Token(type, text, literal, self.line))


