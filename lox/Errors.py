
class Errors:
	def __init__(self) -> None:
		self.hadError = False

	def error(self, line: int, message: str):
		self.__report(line, "", message)

	def __report(self, line: int, where: str, message: str):
		print("Error:")
		print(f"[line {line}] Error {where}: {message}")
		self.hadError = True