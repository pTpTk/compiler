#pragma once

#include <vector>
#include <string>
#include <cassert>

#include "token.h"


class Node
{
  virtual void print() {}
};

class Program : public Node
{
  public:
    Function function;
    void print() {}
};

class Function : public Node
{
  public:
    Type returnType;
    std::string name;
    // need function params
    Statement statement;

    void print() {
      printf("Function: name: %s\n", name.c_str());
    }
};

class Statement : public Node
{
  public:
    virtual long getReturnValue() {
        std::cerr << "Warning: method should not be called in parent class\n";
        assert(false);
    }
};

class Return : public Statement
{
  public:
    long returnValue;

    Return(long rval): returnValue(rval) {}
    long getReturnValue() {return returnValue;}
    void print() {
      printf("Return: returnval: %d\n", returnValue);
    }
};