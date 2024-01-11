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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        insts.emplace_back(new FuncName(name));
        insts.emplace_back(new Push("ebp"));
        insts.emplace_back(new Movl("esp", "ebp"));
        for(auto stmt : statements) {
            stmt->assemble(insts);
        }
    }
};