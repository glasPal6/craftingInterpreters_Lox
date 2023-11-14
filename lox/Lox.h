#ifndef LOX_H
#define LOX_H

    #include <iostream>
    #include <string>
    #include <fstream>
    #include <vector>

    #define SCANNER_IMPLEMENTATION
    #include "Scanner.h"
    // #include "Token.h"

    class Lox
    {
        private:
            bool hasError = false; 
        public:
            int main(int argc, char* argv[]);

            static void runPrompt();
            static void runFile(std::string path);
            static void run(std::string source);

            static void error(int line, std::string message);
            static void report(int line, std::string where, std::string message);
    };
    
#endif //LOX_H

#ifdef LOX_IMPLEMENTATION

    static void Lox::run(std::string source) {
        std::cout << "This is yet to come!!!" << source << std::endl;

        // Scanner scanner = new Scanner(source);
        // Token[] tokens = scanner.scanTokens();

        // // Just print the tokens now
        // for (Token token : tokens) {
        //     std::cout << token.toString() << std::endl;
        // }
    }

    static void Lox::error(int line, std::string message) {
        report(line, "", message);
    }

    static void Lox::report(int line, std::string where, std::string message) {
        perror(
            "[line " + (line) //+ "] Error " + where + ": " + message
        );
        hadError = true;
    }

    static void Lox::runFile(std::string path) {
        // Read in the raw file
        std::ifstream bytes (path);
        if (!bytes) throw std::runtime_error("Could not open the file");

        std::string file(
            (std::istreambuf_iterator<char>(bytes)),
            (std::istreambuf_iterator<char>())
        );

        run(file);
    }

    static void Lox::runPrompt() {
        while (true) {
            try {
                std::string line;
                std::cout << "> ";
                std::getline(std::cin, line);
                
                if (line.empty()) return;

                run(line);
            } catch (const std::exception& e) {
                throw;
            }
        }
    }

    int Lox::main(int argc, char* argv[]){
        try {
            if (argc > 2) {
                std::cout << "Usage: slowInterpreter [script]" << std::endl;
                return 64;
            } else if (argc == 2) {
                runFile(argv[1]);
            } else {
                runPrompt();
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        return 0;
    }

#endif // LOX_IMPLEMENTATION
