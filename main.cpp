#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cassert>
#include "lexer.h"
#include "parser.h"
#include "assembler.h"

int main(int argc, char** argv) {
    if (argc !=2) {
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

    parser.prog.function->print();
    parser.prog.function->statement->print();

    Assembler assembler;
    assembler.run(parser.prog);

    for(auto& v : assembler.output) {
        v->print();
    }

    return 0;
}