#pragma once

#include <vector>
#include <string>
#include <memory>

#include "token.h"


class Node
{
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
    long returnValue;

    Return(long rval): returnValue(rval) {}

    void print() {
      printf("Return: Return value: %ld\n", returnValue);
    }

    long getRetVal() {
      return returnValue;
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