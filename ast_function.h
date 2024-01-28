#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "token.h"
#include "variable_map.h"

class Instruction;
class Statement;
class Program;

class Function
{
  public:
    Type returnType;
    std::string name;
    std::vector<std::string> params;
    std::shared_ptr<Statement> block;
    VariableStack vmap;

    Function();
    void print();
    void assemble(std::vector<std::string>& insts);
    void declare(Program&);
    void define(Program&);
};