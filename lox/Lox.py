import sys
from Scanner import Scanner

class Lox:
	def __init__(self) -> None:
		self.hadError = False

	def main(self, args: list[str]):
		try:
			if len(args) > 1:
				print("Usage: pyLox [script]")
				exit(64)
			elif len(args) == 1:
				self.runFile(args[0])
			else:
				self.runPrompt()
		except IOError as e:
			print(e)

	def runFile(self, path: str):
		with open(path, 'r') as file:
			self.run(file)

			# Indicate an error has occured
			if self.hadError: exit(65)

	def runPrompt(self):
		command = ""
		while command != "exit;":
			line = input("> ")
			if not line: break
			self.run(line)
			self.hadError = False

	def run(self, source: str):
		scanner = Scanner(source)
		tokens = scanner.scanTokens()

		# Just print the tokens for now
		for t in tokens:
			print(t)

	def error(self, line: int, message: str):
		self.__report(line, "", message)

	def __report(self, line: int, where: str, message: str):
		print("Error:")
		print(f"[line {line}] Error {where}: {message}")
		self.hadError = True


if __name__ == "__main__":
	interpreter = Lox()
	interpreter.main(sys.argv[1:])
