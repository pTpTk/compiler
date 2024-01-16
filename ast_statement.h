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
    std::string name;
    std::shared_ptr<Expression> exp;
    std::shared_ptr<VariableMap> vmap;

    Declare(std::shared_ptr<VariableMap> _vmap, std::string _name);
    Declare(std::shared_ptr<VariableMap> _vmap, std::string _name, std::shared_ptr<Expression> _exp);

    void print();
    void assemble(std::vector<std::string>& insts);
};

class ExprStmt : public Statement
{
  public:
    std::shared_ptr<Expression> exp;
    ExprStmt(std::shared_ptr<Expression> _exp)
    : exp(_exp) {}

    void assemble(std::vector<std::string>& insts);
};

class If : public Statement
{
  public:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> ifStmt;
    std::shared_ptr<Statement> elseStmt;

    If(std::shared_ptr<Expression> _cond,
       std::shared_ptr<Statement> _if,
       std::shared_ptr<Statement> _else)
    : condition(_cond), ifStmt(_if), elseStmt(_else) {}

    If(std::shared_ptr<Expression> _cond,
       std::shared_ptr<Statement> _if)
    : condition(_cond), ifStmt(_if) {}

    void assemble(std::vector<std::string>& insts);
};