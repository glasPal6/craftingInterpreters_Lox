import sys

class GenerateAST:

	def __init__(self) -> None:
		pass

	def main(self, args: list[str]):
		if len(args) != 1:
			print("Usage: generate_ast <output directory>")
			exit(64)
		
		outputDir: str = args[0]

		# Name of class : List of fields (type and name)
		self.defineAST(outputDir, "Expr", [
			"Binary		: Expr left, Token operator, Expr right",
			"Grouping	: Expr expression"
			"Literal	: Object value"
			"Unary		: Token operator, Expr right",
		])
	
	def defineAST(outputDir: str, basename: str, types: list[str]):
		raise NotImplementedError