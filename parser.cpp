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

// <exp> ::= <term> { ("+" | "-") <term> }
std::shared_ptr<Expression>
Parser::parseExpr(std::list<Token>& tokens) {
    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());

    ret = parseTerm(tokens);
    auto tkType = tokens.front().type;
    while(tkType == Type::symbol_addition ||
          tkType == Type::symbol_negation) {
        switch(tkType) {
            case Type::symbol_addition:
            {
                tokens.pop_front();
                auto termR = parseTerm(tokens);
                ret = std::make_shared<Addition>(ret, termR);
                break;
            }
            case Type::symbol_negation:
            {
                tokens.pop_front();
                auto termR = parseTerm(tokens);
                ret = std::make_shared<Subtraction>(ret, termR);
                break;
            }
        }

        tkType = tokens.front().type;
    }

    return ret;
}

// <term> ::= <factor> { ("*" | "/") <factor> }
std::shared_ptr<Expression>
Parser::parseTerm(std::list<Token>& tokens) {
    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());

    ret = parseFactor(tokens);
    auto tkType = tokens.front().type;
    while(tkType == Type::symbol_multiplication ||
          tkType == Type::symbol_division) {
        switch(tkType) {
            case Type::symbol_multiplication:
            {
                tokens.pop_front();
                auto termR = parseFactor(tokens);
                ret = std::make_shared<Multiplication>(ret, termR);
                break;
            }
            case Type::symbol_division:
            {
                tokens.pop_front();
                auto termR = parseFactor(tokens);
                ret = std::make_shared<Division>(ret, termR);
                break;
            }
        }

        tkType = tokens.front().type;
    }

    return ret;
}

// <factor> ::= "(" <exp> ")" | <unary_op> <factor> | <int>
std::shared_ptr<Expression>
Parser::parseFactor(std::list<Token>& tokens) {
    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());
    
    //<factor> ::= "(" <exp> ")"
    if(tokens.front().type == Type::symbol_parenthesis_l) {
        tokens.pop_front();
        ret = parseExpr(tokens);
        TOKEN_EXPECT(Type::symbol_parenthesis_r);
        return ret;
    }

    //<factor> ::= <int>
    if(tokens.front().type == Type::integer) {
        ret = std::make_shared<Constant>(tokens.front().val);
        tokens.pop_front();
        return ret;
    }

    //<factor> ::= <unary_op> <factor>
    if(tokens.front().type == Type::symbol_negation) {
        tokens.pop_front();
        ret = std::make_shared<Negation>(parseFactor(tokens));
        return ret;
    }

    if(tokens.front().type == Type::symbol_bit_complement) {
        tokens.pop_front();
        ret = std::make_shared<BitwiseComplement>(parseFactor(tokens));
        return ret;
    }

    if(tokens.front().type == Type::symbol_logical_negation) {
        tokens.pop_front();
        ret = std::make_shared<LogicalNegation>(parseFactor(tokens));
        return ret;
    }

    std::cout << "syntax err, unrecognized token \"";
    tokens.front().print();
    std::cout << " \"" << std::endl;

    assert(false);
}