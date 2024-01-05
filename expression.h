#pragma once

#include <vector>
#include <string>
#include <memory>

#include "asm.h"

class Expression
{
  public:
    virtual void assemble(std::vector<std::shared_ptr<Instruction>>& insts) {}
    void print() {}
    //TODD: is eval needed?
    virtual long eval() { return -1; }
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

    long eval() { return val; }
    void print() {
      printf("Constant: %ld\n", val);
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

    long eval() { return -(exp->eval()); }
    void print() {
      printf("-");
      exp->print();
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

    long eval() { return ~(exp->eval()); }
    void print() {
      printf("~");
      exp->print();
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

    long eval() { return !(exp->eval()); }
    void print() {
      printf("!");
      exp->print();
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
        insts.emplace_back(new Addl("ecx", "eax"));
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