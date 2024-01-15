#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "token.h"
#include "variable_map.h"

class Instruction;
class Statement;

class Function
{
  public:
    Type returnType;
    std::string name;
    // need function params
    std::vector<std::shared_ptr<Statement>> statements;
    std::shared_ptr<VariableMap> vmap;

    Function();
    void print();
    void assemble(std::vector<std::string>& insts);
};