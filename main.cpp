#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cassert>
#include "lexer.h"

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

    return 0;
}