#pragma once

#include <vector>

#include "token.h"
#include "ast.h"

class Parser
{
  private:
    void parseProg(std::vector<Token>);
    Function parseFunc(std::vector<Token>);
  public:
    Program prog;

    Parser(){}
    void run(std::vector<Token>);
};