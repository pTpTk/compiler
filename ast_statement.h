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
    virtual bool isEmpty() { return false; }
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
    VariableStack vmap;

    Declare(VariableStack _vmap, std::string _name);
    Declare(VariableStack _vmap, std::string _name, std::shared_ptr<Expression> _exp);

    void print();
    void assemble(std::vector<std::string>& insts);
};

class ExprStmt : public Statement
{
  public:
    std::shared_ptr<Expression> exp;
    ExprStmt() {}
    ExprStmt(std::shared_ptr<Expression> _exp)
    : exp(_exp) {}

    void assemble(std::vector<std::string>& insts);
    bool isEmpty() { return !exp.get(); }
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

class Compound : public Statement
{
  private:
  public:
    VariableStack vmap;
    std::vector<std::shared_ptr<Statement>> statements;
    Compound() {}

    void assemble(std::vector<std::string>& insts);
};

class For : public Statement
{
  public:
    std::shared_ptr<Statement> initialStmt;
    std::shared_ptr<Statement> condition;
    std::shared_ptr<Expression> postExpr;
    std::shared_ptr<Statement> body;

    For(std::shared_ptr<Statement> _is, std::shared_ptr<Statement> _co,
        std::shared_ptr<Expression> _pe, std::shared_ptr<Statement> _bo)
    : initialStmt(_is), condition(_co), postExpr(_pe), body(_bo) {}
};

class While : public Statement
{
  public:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> body;

    While(std::shared_ptr<Expression> _cond,
          std::shared_ptr<Statement> _bo)
    : condition(_cond), body(_bo) {}
};

class Do : public Statement
{
  public:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> body;

    Do(std::shared_ptr<Statement> _bo, 
       std::shared_ptr<Expression> _cond)
    : condition(_cond), body(_bo) {}
};

class Break : public Statement
{

};

class Continue : public Statement
{
  
};