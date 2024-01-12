#pragma once

#include <vector>
#include <string>
#include <memory>

class Instruction;

class Expression
{
  public:
    virtual void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {}
};

class Constant : public Expression
{
  private:
    long val;
  public:
    Constant(long _val) : val(_val) {}

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
};

class Negation : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    Negation(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
};

class BitwiseComplement : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    BitwiseComplement(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
};

class LogicalNegation : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    LogicalNegation(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts);
};

class Assignment : public Expression
{
  private:
    std::string name;
    std::shared_ptr<Expression> exp;
  public:
    Assignment(std::string _name,
               std::shared_ptr<Expression> _exp) 
    : name(_name), exp(_exp) {}
};

class Variable : public Expression
{
  private:
    std::string name;
  public:
    Variable(std::string _name)
    : name(_name) {}
};