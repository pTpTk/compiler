#include "parser.h"

void
Parser::run(std::list<Token> tokens) {
    assert(!tokens.empty());
    prog.function = parseFunc(tokens);
}

Function
Parser::parseFunc(std::list<Token> tokens) {
    Function ret;

    TOKEN_EXPECT(Type::keyword_int);
    ret.returnType = Type::keyword_int;
    tokens.pop_front();
    
    TOKEN_EXPECT(Type::identifier);
    ret.name = *((std::string*)tokens.front().val);
    tokens.pop_front();

    TOKEN_EXPECT(Type::symbol_brace_l);
    tokens.pop_front();

    ret.statement = parseStmt(tokens);
    tokens.pop_front();

    TOKEN_EXPECT(Type::symbol_brace_r);
    tokens.pop_front();

    return ret;
}

Statement
Parser::parseStmt(std::list<Token> tokens) {
    TOKEN_EXPECT(Type::keyword_return);
    tokens.pop_front();

    TOKEN_EXPECT(Type::integer);
    Statement ret = Return(tokens.front().val);
    tokens.pop_front();

    TOKEN_EXPECT(Type::symbol_semicolon);
    tokens.pop_front();

    return ret;
}