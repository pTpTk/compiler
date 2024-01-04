#pragma once

#include <vector>
#include <string>
#include <memory>

#include "token.h"
#include "expression.h"


class Node
{
  public:
    virtual void print() {}
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