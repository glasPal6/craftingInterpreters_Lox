#ifndef LOX_H
#define LOX_H

    #include <iostream>
    #include <string>
    #include <fstream>

    #define SCANNER_IMPLEMENTATION
    #include "Scanner.h"
    // #include "Token.h"

    class Lox
    {   
        private:
            static bool hadError; 

            void runPrompt();
            void runFile(std::string path);
            void run(std::string source);

            void error(int line, std::string message);
            void report(int line, std::string where, std::string message);

        public:
            static int main(int argc, char* argv[]);

    };
    
#endif //LOX_H

#ifdef LOX_IMPLEMENTATION

    bool Lox::hadError = false;

    int Lox::main(int argc, char* argv[]){
        try {
            if (argc > 2) {
                std::cout << "Usage: slowInterpreter [script]" << std::endl;
                return 64;
            } else if (argc == 2) {
                Lox lox; lox.runFile(argv[1]);
            } else {
                Lox lox; lox.runPrompt();
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        return 0;
    }

    void Lox::runPrompt() {
        while (true) {
            try {
                std::string line;
                std::cout << "> ";
                std::getline(std::cin, line);
                
                if (line.empty()) return;

                run(line);
                Lox::hadError = false;
            } catch (const std::exception& e) {
                throw;
            }
        }
    }

    void Lox::runFile(std::string path) {
        // Read in the raw file
        std::ifstream bytes (path);
        if (!bytes) throw std::runtime_error("Could not open the file");

        std::string file(
            (std::istreambuf_iterator<char>(bytes)),
            (std::istreambuf_iterator<char>())
        );

        run(file);
        if (Lox::hadError) return;
    }

    void Lox::run(std::string source) {
        Scanner scanner(source);
        std::vector<Token> tokens = scanner.scanTokens();

        // Just print the tokens now
        for (Token token : tokens) {
            std::cout << token.toString() << std::endl;
        }

        if (hadError) return;
    }

    void Lox::error(int line, std::string message) {
        report(line, "", message);
    }

    void Lox::report(int line, std::string where, std::string message) {
        // perror("[line " + std::to_string(line) + "] error " + where + ": " + message);
        std::cout << ("[line " + std::to_string(line) + "] error " + where + ": " + message) << std::endl;
        Lox::hadError = true;
    }

#endif // LOX_IMPLEMENTATION
