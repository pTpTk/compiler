#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "token.h"
#include "ast_statement.h"

class Function
{
  public:
    Type returnType;
    std::string name;
    // need function params
    std::vector<std::shared_ptr<Statement>> statements;

    void print() {
      printf("Function: Name: %s\n", name.c_str());
    }
};