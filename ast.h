#pragma once

#include <vector>
#include <string>

#include "token.h"


class Node
{
};

class Program : public Node
{
  public:
    Function function;
};

class Function : public Node
{
  public:
    Type returnType;
    std::string name;
    // need function params
    Statement statement;
};

class Statement : public Node
{
};

class Return : public Statement
{
  public:
    long returnValue;
};