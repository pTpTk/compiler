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
    std::shared_ptr<Statement> ret;
    TOKEN_EXPECT(Type::keyword_return);
    tokens.pop_front();

    ret = std::make_shared<Return>(parseExpr(tokens));

    TOKEN_EXPECT(Type::symbol_semicolon);
    tokens.pop_front();

    return ret;
}

std::shared_ptr<Expression>
Parser::parseExpr(std::list<Token>& tokens) {
    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());
    
    if(tokens.front().type == Type::integer) {
        ret = std::make_shared<Constant>(tokens.front().val);
        tokens.pop_front();
        return ret;
    }

    if(tokens.front().type == Type::symbol_negation) {
        tokens.pop_front();
        ret = std::make_shared<Negation>(parseExpr(tokens));
        return ret;
    }

    if(tokens.front().type == Type::symbol_bit_complement) {
        tokens.pop_front();
        ret = std::make_shared<BitwiseComplement>(parseExpr(tokens));
        return ret;
    }

    if(tokens.front().type == Type::symbol_logical_negation) {
        tokens.pop_front();
        ret = std::make_shared<LogicalNegation>(parseExpr(tokens));
        return ret;
    }

    std::cout << "syntax err, unrecognized token \"";
    tokens.front().print();
    std::cout << " \"" << std::endl;

    assert(false);
}