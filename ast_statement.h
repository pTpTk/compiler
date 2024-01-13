#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "token.h"
#include "variable_map.h"

class Instruction;
class Expression;

class Statement
{
  public:
    virtual void assemble(std::vector<std::string>& insts) {}
    virtual void print() {}
};

class Return : public Statement
{
  public:
    std::shared_ptr<Expression> exp;

    Return() = default;
    Return(std::shared_ptr<Expression> _exp): exp(_exp) {}

    void print();
    void assemble(std::vector<std::string>& insts);
};

class Declare : public Statement
{
  public:
    std::string varName;
    std::shared_ptr<Expression> exp;
    VariableMap& vmap;

    Declare(VariableMap& _vmap, std::string _varName);
    Declare(VariableMap& _vmap, std::string _varName, std::shared_ptr<Expression> _exp);

    void print();
};

class ExprStmt : public Statement
{
  public:
    std::shared_ptr<Expression> exp;
    ExprStmt(std::shared_ptr<Expression> _exp)
    : exp(_exp) {}
};