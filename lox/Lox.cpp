#include <iostream>
#include <string>
#include <fstream>
#include <vector>

static void run(std::string source) {
    // TODO
    std::cout << "This is a test!" << std::endl;
}

static void runFile(std::string path) {
    // Read in the raw file
    std::ifstream bytes (path);
    if (!bytes) throw std::runtime_error("Could not open the file");

    std::string file(
        (std::istreambuf_iterator<char>(bytes)),
        (std::istreambuf_iterator<char>())
    );

    run(file);
}

static void runPrompt() {
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

int main(int argc, char* argv[]){
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
