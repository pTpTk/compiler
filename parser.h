#pragma once

#include <iostream>
#include <list>
#include <cassert>
#include <string>
#include <memory>

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

class Parser
{
  private:
    std::unique_ptr<Function> parseFunc(std::list<Token>&);
    std::unique_ptr<Statement> parseStmt(std::list<Token>&);
  public:
    Program prog;

    Parser(){}
    void run(std::list<Token>&);
};