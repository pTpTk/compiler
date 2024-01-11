#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

#include "token.h"
#include "ast_expression.h"

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

    void print() {
      printf("Return statement\n");
    }

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        exp->assemble(insts);
        insts.emplace_back(new Movl("ebp", "esp"));
        insts.emplace_back(new Pop("ebp"));
        insts.emplace_back(new Ret);
    }
};

class Declare : public Statement
{
  public:
    std::string varName;
    std::shared_ptr<Expression> exp;

    Declare() = default;
    Declare(std::string _varName) : varName(_varName) {}
    Declare(std::string _varName, std::shared_ptr<Expression> _exp)
    : varName(_varName), exp(_exp) {}

    void print() {
      printf("Declaration: int %s\n", varName.c_str());
    }
};

class ExprStmt : public Statement
{
  public:
    std::shared_ptr<Expression> exp;
    ExprStmt(std::shared_ptr<Expression> _exp)
    : exp(_exp) {}
};