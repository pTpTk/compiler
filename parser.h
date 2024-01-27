#pragma once

#include <iostream>
#include <list>
#include <cassert>
#include <string>
#include <memory>
#include <utility>

#include "util.h"
#include "token.h"
#include "ast.h"

#define TOKEN_EXPECT(T) { \
assert(!tokens.empty()); \
if(tokens.front().type != T) { \
  std::cerr << "syntax err, expecting token " \
  << #T << std::endl; \
  printf("token type: %d, ", (int)tokens.front().type); \
  tokens.front().print(); \
  std::cout << std::endl; \
  assert(false); \
} \
}

#define TOKEN_POP(T) { \
TOKEN_EXPECT(T); \
tokens.pop_front(); \
}

class Parser
{
  private:
    std::shared_ptr<Function>   parseFunc(std::list<Token>&);
    std::shared_ptr<Statement>  parseBlock(std::list<Token>&);
    std::shared_ptr<Statement>  parseBlockItem(std::list<Token>&);
    std::shared_ptr<Statement>  parseStmt(std::list<Token>&);
    std::shared_ptr<Expression> parseExpr(std::list<Token>&);
    std::shared_ptr<Expression> parseConditional(std::list<Token>&);
    std::shared_ptr<Expression> parseLOr(std::list<Token>&);
    std::shared_ptr<Expression> parseLAnd(std::list<Token>&);
    std::shared_ptr<Expression> parseEquality(std::list<Token>&);
    std::shared_ptr<Expression> parseRelational(std::list<Token>&);
    std::shared_ptr<Expression> parseAdditive(std::list<Token>&);
    std::shared_ptr<Expression> parseTerm(std::list<Token>&);
    std::shared_ptr<Expression> parseFactor(std::list<Token>&);
  public:
    Program prog;

    Parser(){}
    void run(std::list<Token>&);
};