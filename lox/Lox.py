import sys
from Scanner import Scanner

class Lox:
	def __init__(self) -> None:
		self.hadError = False
		self.scanner = None

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
			self.run(file.read())

			# Indicate an error has occured
			if self.scanner.errors.hadError: exit(65)

	def runPrompt(self):
		command = ""
		while command != "exit;":
			line = input("> ")
			if not line: break
			self.run(line)
			self.scanne.errors.hadError = False

	def run(self, source: str):
		self.scanner = Scanner(source)
		tokens = self.scanner.scanTokens()

		# Just print the tokens for now
		for t in tokens:
			print(t)

if __name__ == "__main__":
	interpreter = Lox()
	# interpreter.main(sys.argv[1:])
	interpreter.main(["test.txt"])
