#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cassert>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "assembler.h"

std::string labelMaker() {
    static int count = 0;
    return "_L" + std::to_string(count++);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Wrong input format!!\n";
        return 1;
    }

    Lexer lexer;
    lexer.run(argv[1]);

    std::cout << "lexed outputs:\n";
    for(auto& t : lexer.tokens) {
        t.print();
        std::cout << " ";
    }
    std::cout << std::endl;

    Parser parser;
    parser.run(lexer.tokens);

    Assembler assembler;
    assembler.run(parser.prog);

    std::ofstream ofs(argv[2]);

    for(auto& v : assembler.output) {
        ofs << v;
    }

    return 0;
}