#pragma once

#include <iostream>
#include <list>
#include <cassert>
#include <string>

#include "token.h"
#include "ast.h"

#define TOKEN_EXPECT(T) { \
assert(!tokens.empty()); \
if(tokens.front().type != T) { \
  std::cerr << "syntax err, expecting token " \
  << #T << std::endl; \
  assert(false); \
} \
}

class Parser
{
  private:
    void parseProg(std::list<Token>);
    Function parseFunc(std::list<Token>);
    Statement parseStmt(std::list<Token>);
  public:
    Program prog;

    Parser(){}
    void run(std::list<Token>);
};