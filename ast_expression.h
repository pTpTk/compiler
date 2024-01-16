#pragma once

#include <vector>
#include <string>
#include <memory>

#include "variable_map.h"

class Instruction;

class Expression
{
  public:
    virtual void assemble(std::vector<std::string>& insts) {}
};

class Constant : public Expression
{
  private:
    long val;
  public:
    Constant(long _val) : val(_val) {}

    void assemble(std::vector<std::string>& insts);
};

class Negation : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    Negation(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::string>& insts);
};

class BitwiseComplement : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    BitwiseComplement(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::string>& insts);
};

class LogicalNegation : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    LogicalNegation(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::string>& insts);
};

class Addition : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    Addition(std::shared_ptr<Expression> _expL,
             std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class Subtraction : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    Subtraction(std::shared_ptr<Expression> _expL,
                std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class Multiplication : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    Multiplication(std::shared_ptr<Expression> _expL,
                   std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class Division : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    Division(std::shared_ptr<Expression> _expL,
             std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class Less : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    Less(std::shared_ptr<Expression> _expL,
         std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class Greater : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    Greater(std::shared_ptr<Expression> _expL,
            std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class LessEqual : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    LessEqual(std::shared_ptr<Expression> _expL,
              std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class GreaterEqual : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    GreaterEqual(std::shared_ptr<Expression> _expL,
                 std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class Equal : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    Equal(std::shared_ptr<Expression> _expL,
          std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class LogicalAnd : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    LogicalAnd(std::shared_ptr<Expression> _expL,
               std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class LogicalOr : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    LogicalOr(std::shared_ptr<Expression> _expL,
             std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class NotEqual : public Expression
{
  private:
    std::shared_ptr<Expression> expL;
    std::shared_ptr<Expression> expR;
  public:
    NotEqual(std::shared_ptr<Expression> _expL,
             std::shared_ptr<Expression> _expR) 
    : expL(_expL), expR(_expR) {}

    void assemble(std::vector<std::string>& insts);
};

class Assignment : public Expression
{
  private:
    std::string name;
    std::shared_ptr<Expression> exp;
    std::shared_ptr<VariableMap> vmap;
  public:
    Assignment(std::shared_ptr<VariableMap> _vmap, std::string _name,
               std::shared_ptr<Expression> _exp) 
    : vmap(_vmap), name(_name), exp(_exp) {}

    void assemble(std::vector<std::string>& insts);
};

class Variable : public Expression
{
  private:
    std::string name;
    std::shared_ptr<VariableMap> vmap;
  public:
    Variable(std::shared_ptr<VariableMap> _vmap, std::string _name) 
    : vmap(_vmap), name(_name) {}

    void assemble(std::vector<std::string>& insts);
};

// e1 ? e2 : e3
class Conditional : public Expression
{
  private:
    std::shared_ptr<Expression> e1;
    std::shared_ptr<Expression> e2;
    std::shared_ptr<Expression> e3;
  public:
    Conditional(std::shared_ptr<Expression> _e1,
                std::shared_ptr<Expression> _e2,
                std::shared_ptr<Expression> _e3)
    : e1(_e1), e2(_e2), e3(_e3) {}

    void assemble(std::vector<std::string>& insts);
};