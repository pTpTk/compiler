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
    virtual void setLabelPair(LabelPair* lp) {}
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
    std::shared_ptr<Expression> initialExpr;
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Expression> postExpr;
    std::shared_ptr<Statement> body;

    For(std::shared_ptr<Expression> _ie, std::shared_ptr<Expression> _co,
        std::shared_ptr<Expression> _pe, std::shared_ptr<Statement> _bo)
    : initialExpr(_ie), condition(_co), postExpr(_pe), body(_bo) {}
    
    void assemble(std::vector<std::string>& insts);

    LabelPair* labelPair;
    void setLabelPair(LabelPair* lp) { labelPair = lp; }
};

class ForDecl : public Statement
{
  public:
    std::shared_ptr<Statement> initialDecl;
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Expression> postExpr;
    std::shared_ptr<Statement> body;
    VariableStack vmap;

    ForDecl(VariableStack _vmap,
        std::shared_ptr<Statement> _id, std::shared_ptr<Expression> _co,
        std::shared_ptr<Expression> _pe, std::shared_ptr<Statement> _bo)
    : initialDecl(_id), condition(_co), postExpr(_pe), body(_bo), vmap(_vmap) {}
    
    void assemble(std::vector<std::string>& insts);

    LabelPair* labelPair;
    void setLabelPair(LabelPair* lp) { labelPair = lp; }
};

class While : public Statement
{
  public:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> body;

    While(std::shared_ptr<Expression> _cond,
          std::shared_ptr<Statement> _bo)
    : condition(_cond), body(_bo) {}

    void assemble(std::vector<std::string>& insts);

    LabelPair* labelPair;
    void setLabelPair(LabelPair* lp) { labelPair = lp; }
};

class Do : public Statement
{
  public:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> body;

    Do(std::shared_ptr<Statement> _bo, 
       std::shared_ptr<Expression> _cond)
    : condition(_cond), body(_bo) {}

    void assemble(std::vector<std::string>& insts);

    LabelPair* labelPair;
    void setLabelPair(LabelPair* lp) { labelPair = lp; }
};

class Break : public Statement
{
  public:
    void assemble(std::vector<std::string>& insts);

    LabelPair* labelPair;
    void setLabelPair(LabelPair* lp) { labelPair = lp; }
};

class Continue : public Statement
{
  public:
    void assemble(std::vector<std::string>& insts);

    LabelPair* labelPair;
    void setLabelPair(LabelPair* lp) { labelPair = lp; }
};