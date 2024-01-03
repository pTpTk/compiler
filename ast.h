#pragma once

#include <vector>
#include <string>
#include <memory>

#include "token.h"


class Node
{
  public:
    virtual void print() {}
};

class Expression : public Node
{
  public:
    virtual long eval() { return -1; }
};

class Constant : public Expression
{
  private:
    long val;
  public:
    Constant(long _val) : val(_val) {}

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

    long eval() { return !(exp->eval()); }
    void print() {
      printf("!");
      exp->print();
    }
};

class Statement : public Node
{
  public:
    virtual void print() {}
    virtual long getRetVal() {return -1;}
};

class Return : public Statement
{
  public:
    std::shared_ptr<Expression> exp;

    Return() = default;
    Return(std::shared_ptr<Expression> _exp): exp(_exp) {}

    void print() {
      printf("Return: Return value: %ld\n", exp->eval());
      exp->print();
    }

    long getRetVal() {
      return exp->eval();
    }
};

class Function : public Node
{
  public:
    Type returnType;
    std::string name;
    // need function params
    std::shared_ptr<Statement> statement;

    void print() {
      printf("Function: Name: %s\n", name.c_str());
    }
};

class Program : public Node
{
  public:
    std::shared_ptr<Function> function;
};