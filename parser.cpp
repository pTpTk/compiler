#include "parser.h"

void
Parser::run(std::vector<Token> tokens) {
    prog.function = parseFunc(tokens);
}

void
Parser::parseProg(std::vector<Token> tokens) {

}

Function
Parser::parseFunc(std::vector<Token> tokens) {
    auto t_iter = tokens.begin();
    if(t_iter->type == Type::keyword && t_iter->val == (long)Keyword::INT) 
}