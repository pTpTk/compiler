#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "token.h"

class Instruction;
class Expression;

class Statement
{
  public:
    virtual void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {}
    virtual void print() {}
};

class Return : public Statement
{
  public:
    std::shared_ptr<Expression> exp;

    Return() = default;
    Return(std::shared_ptr<Expression> _exp): exp(_exp) {}

    void print();
    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
};

class Declare : public Statement
{
  public:
    std::string varName;
    std::shared_ptr<Expression> exp;

    Declare(std::string _varName) : varName(_varName) {}
    Declare(std::string _varName, std::shared_ptr<Expression> _exp)
    : varName(_varName), exp(_exp) {}

    void print();
};

class ExprStmt : public Statement
{
  public:
    std::shared_ptr<Expression> exp;
    ExprStmt(std::shared_ptr<Expression> _exp)
    : exp(_exp) {}
};