#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "token.h"

class Instruction;
class Statement;

class Function
{
  public:
    Type returnType;
    std::string name;
    // need function params
    std::vector<std::shared_ptr<Statement>> statements;

    void print();
    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
};