#include "parser.h"

void
Parser::run(std::list<Token>& tokens) {
    assert(!tokens.empty());
    prog.function = parseFunc(tokens);
}

std::shared_ptr<Function>
Parser::parseFunc(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Function> ret(new Function());
    prog.vmap = ret->vmap;

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

    while(tokens.front().type != Type::symbol_brace_r)
        ret->statements.emplace_back(parseBlock(tokens));

    TOKEN_EXPECT(Type::symbol_brace_r);
    tokens.pop_front();

    return ret;
}

std::shared_ptr<Statement>
Parser::parseBlock(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Statement> ret;
    assert(!tokens.empty());

    if(tokens.front().type == Type::keyword_int) {
        tokens.pop_front();
        TOKEN_EXPECT(Type::identifier);
        std::string varName = *(std::string*)tokens.front().val;
        tokens.pop_front();
        
        if(tokens.front().type == Type::symbol_semicolon)
            ret = std::make_shared<Declare>(prog.vmap, varName);
        else {
            TOKEN_EXPECT(Type::symbol_assign);
            tokens.pop_front();
            ret = std::make_shared<Declare>(prog.vmap, varName, parseExpr(tokens));
        }
        TOKEN_EXPECT(Type::symbol_semicolon);
        tokens.pop_front();
        return ret;
    }

    ret = parseStmt(tokens);
    return ret;
}

std::shared_ptr<Statement>
Parser::parseStmt(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Statement> ret;
    assert(!tokens.empty());

    switch(tokens.front().type) {
        case Type::keyword_return:
            tokens.pop_front();
            ret = std::make_shared<Return>(parseExpr(tokens));
            break;
        case Type::keyword_if:
        {
            tokens.pop_front();
            TOKEN_EXPECT(Type::symbol_parenthesis_l);
            tokens.pop_front();
            auto condition = parseExpr(tokens);
            TOKEN_EXPECT(Type::symbol_parenthesis_r);
            tokens.pop_front();
            auto ifStmt = parseStmt(tokens);
            if(tokens.front().type == Type::keyword_else) {
                tokens.pop_front();
                auto elseStmt = parseStmt(tokens);
                ret = std::make_shared<If>(condition, ifStmt, elseStmt);
            } else {
                ret = std::make_shared<If>(condition, ifStmt);
            }
            return ret;
        }
        default:
        {
            ret = std::make_shared<ExprStmt>(parseExpr(tokens));
        }
    }    

    TOKEN_EXPECT(Type::symbol_semicolon);
    tokens.pop_front();

    return ret;
}

// <exp> ::= <id> "=" <exp> | <conditional-exp>
std::shared_ptr<Expression>
Parser::parseExpr(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());

    auto tokenIter = tokens.begin();

    if(tokenIter->type == Type::identifier && 
        (++tokenIter)->type == Type::symbol_assign) {

        --tokenIter;
        std::string varName = *(std::string*)tokens.front().val;
        tokens.pop_front();

        TOKEN_EXPECT(Type::symbol_assign);
        tokens.pop_front();

        auto val = parseExpr(tokens);
        ret = std::make_shared<Assignment>(prog.vmap, varName, val);
    }
    else {
        --tokenIter;
        ret = parseConditional(tokens);
    }

    return ret;
}

// <conditional-exp> ::= <logical-or-exp> [ "?" <exp> ":" <conditional-exp> ]
std::shared_ptr<Expression>
Parser::parseConditional(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());
    
    ret = parseLOr(tokens);

    if(tokens.front().type == Type::symbol_question_mark) {
        tokens.pop_front();
        auto e2 = parseExpr(tokens);
        TOKEN_EXPECT(Type::symbol_colon);
        tokens.pop_front();
        auto e3 = parseConditional(tokens);
        ret = std::make_shared<Conditional>(ret, e2, e3);
    }

    return ret;
}

// <logical-or-exp> ::= <logical-and-exp> { "||" <logical-and-exp> }
std::shared_ptr<Expression>
Parser::parseLOr(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());

    ret = parseLAnd(tokens);
    auto tkType = tokens.front().type;
    while(tkType == Type::symbol_logical_or) {
        tokens.pop_front();
        auto termR = parseLAnd(tokens);
        ret = std::make_shared<LogicalOr>(ret, termR);

        tkType = tokens.front().type;
    }

    return ret;
}

// <logical-and-exp> ::= <equality-exp> { "&&" <equality-exp> }
std::shared_ptr<Expression>
Parser::parseLAnd(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());

    ret = parseEquality(tokens);
    auto tkType = tokens.front().type;
    while(tkType == Type::symbol_logical_and) {
        tokens.pop_front();
        auto termR = parseEquality(tokens);
        ret = std::make_shared<LogicalAnd>(ret, termR);

        tkType = tokens.front().type;
    }

    return ret;
}

// <equality-exp> ::= <relational-exp> { ("!=" | "==") <relational-exp> }
std::shared_ptr<Expression>
Parser::parseEquality(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());

    ret = parseRelational(tokens);
    auto tkType = tokens.front().type;
    while(tkType == Type::symbol_equal ||
          tkType == Type::symbol_not_equal) {
        switch(tkType) {
            case Type::symbol_equal:
            {
                tokens.pop_front();
                auto termR = parseRelational(tokens);
                ret = std::make_shared<Equal>(ret, termR);
                break;
            }
            case Type::symbol_not_equal:
            {
                tokens.pop_front();
                auto termR = parseRelational(tokens);
                ret = std::make_shared<NotEqual>(ret, termR);
                break;
            }
        }

        tkType = tokens.front().type;
    }

    return ret;
}

// <relational-exp> ::= <additive-exp> { ("<" | ">" | "<=" | ">=") <additive-exp> }
std::shared_ptr<Expression>
Parser::parseRelational(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());

    ret = parseAdditive(tokens);
    auto tkType = tokens.front().type;
    while(tkType == Type::symbol_less       ||
          tkType == Type::symbol_less_equal ||
          tkType == Type::symbol_greater    ||
          tkType == Type::symbol_greater_equal) {
        switch(tkType) {
            case Type::symbol_less:
            {
                tokens.pop_front();
                auto termR = parseAdditive(tokens);
                ret = std::make_shared<Less>(ret, termR);
                break;
            }
            case Type::symbol_less_equal:
            {
                tokens.pop_front();
                auto termR = parseAdditive(tokens);
                ret = std::make_shared<LessEqual>(ret, termR);
                break;
            }
            case Type::symbol_greater:
            {
                tokens.pop_front();
                auto termR = parseAdditive(tokens);
                ret = std::make_shared<Greater>(ret, termR);
                break;
            }
            case Type::symbol_greater_equal:
            {
                tokens.pop_front();
                auto termR = parseAdditive(tokens);
                ret = std::make_shared<GreaterEqual>(ret, termR);
                break;
            }
        }

        tkType = tokens.front().type;
    }

    return ret;
}

// <additive-exp> ::= <term> { ("+" | "-") <term> }
std::shared_ptr<Expression>
Parser::parseAdditive(std::list<Token>& tokens) {
    DEBUG();

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
    DEBUG();

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

// <factor> ::= "(" <exp> ")" | <unary_op> <factor> | <int> | <id>
std::shared_ptr<Expression>
Parser::parseFactor(std::list<Token>& tokens) {
    DEBUG();

    std::shared_ptr<Expression> ret;

    assert(!tokens.empty());
    
    //<factor> ::= "(" <exp> ")"
    if(tokens.front().type == Type::symbol_parenthesis_l) {
        tokens.pop_front();
        ret = parseExpr(tokens);
        TOKEN_EXPECT(Type::symbol_parenthesis_r);
        tokens.pop_front();
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

    if(tokens.front().type == Type::identifier) {
        auto name = *(std::string*) tokens.front().val;
        tokens.pop_front();
        ret = std::make_shared<Variable>(prog.vmap, name);
        return ret;
    }

    std::cout << "syntax err, unrecognized token \"";
    tokens.front().print();
    std::cout << "\"" << std::endl;

    assert(false);
}