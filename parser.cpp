#include "parser.h"

void
Parser::run(std::list<Token>& tokens) {
    assert(!tokens.empty());
    prog.function = parseFunc(tokens);
}

std::shared_ptr<Function>
Parser::parseFunc(std::list<Token>& tokens) {
    std::shared_ptr<Function> ret(new Function());

    TOKEN_EXPECT(Type::keyword_int);
    ret->returnType = Type::keyword_int;
    tokens.pop_front();
    
    TOKEN_EXPECT(Type::identifier);
    ret->name = *((std::string*)tokens.front().val);
    tokens.pop_front();

    TOKEN_EXPECT(Type::symbol_parenthesis_l);
    tokens.pop_front();

    TOKEN_EXPECT(Type::symbol_parenthesis_r);
    tokens.pop_front();

    TOKEN_EXPECT(Type::symbol_brace_l);
    tokens.pop_front();

    ret->statement = parseStmt(tokens);

    TOKEN_EXPECT(Type::symbol_brace_r);
    tokens.pop_front();

    return ret;
}

std::shared_ptr<Statement>
Parser::parseStmt(std::list<Token>& tokens) {
    TOKEN_EXPECT(Type::keyword_return);
    tokens.pop_front();

    TOKEN_EXPECT(Type::integer);
    std::shared_ptr<Expression> retVal{new Constant(tokens.front().val)};
    std::shared_ptr<Statement> ret{new Return(retVal)};
    tokens.pop_front();

    TOKEN_EXPECT(Type::symbol_semicolon);
    tokens.pop_front();

    return ret;
}