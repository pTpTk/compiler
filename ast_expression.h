#pragma once

#include <vector>
#include <string>
#include <memory>

#include "asm.h"

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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        insts.emplace_back(new Movl(val, "eax"));
    }
};

class Negation : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    Negation(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        exp->assemble(insts);
        
        insts.emplace_back(new Neg("eax"));
    }
};

class BitwiseComplement : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    BitwiseComplement(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        exp->assemble(insts);
        
        insts.emplace_back(new Not("eax"));
    }
};

class LogicalNegation : public Expression
{
  private:
    std::shared_ptr<Expression> exp;
  public:
    LogicalNegation(std::shared_ptr<Expression> _exp) : exp(_exp) {}

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        exp->assemble(insts);

        insts.emplace_back(new Cmpl(0, "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Sete("al"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Addl("ecx", "eax"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expR->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expL->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Subl("ecx", "eax"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Imul("ecx", "eax"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expR->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expL->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Cdq());
        insts.emplace_back(new Idivl("ecx"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Cmpl("ecx", "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Setl("al"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Cmpl("ecx", "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Setg("al"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Cmpl("ecx", "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Setle("al"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Cmpl("ecx", "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Setge("al"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Cmpl("ecx", "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Sete("al"));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        std::string clause2 = labelMaker();
        std::string end = labelMaker();

        expL->assemble(insts);
        insts.emplace_back(new Cmpl(0, "eax"));
        insts.emplace_back(new Jne(clause2));
        insts.emplace_back(new Jmp(end));
        insts.emplace_back(new Tag(clause2));
        expR->assemble(insts);
        insts.emplace_back(new Cmpl(0, "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Setne("al"));
        insts.emplace_back(new Tag(end));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        std::string clause2 = labelMaker();
        std::string end = labelMaker();

        expL->assemble(insts);
        insts.emplace_back(new Cmpl(0, "eax"));
        insts.emplace_back(new Je(clause2));
        insts.emplace_back(new Movl(1, "eax"));
        insts.emplace_back(new Jmp(end));
        insts.emplace_back(new Tag(clause2));
        expR->assemble(insts);
        insts.emplace_back(new Cmpl(0, "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Setne("al"));
        insts.emplace_back(new Tag(end));
    }
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

    void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
        expL->assemble(insts);
        insts.emplace_back(new Push("eax"));
        expR->assemble(insts);
        insts.emplace_back(new Pop("ecx"));
        insts.emplace_back(new Cmpl("ecx", "eax"));
        insts.emplace_back(new Movl(0, "eax"));
        insts.emplace_back(new Setne("al"));
    }
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