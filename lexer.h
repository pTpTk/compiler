#include <iostream>
#include <cstdio>
#include <list>
#include <cstring>
#include <string>
#include <cassert>

#include "token.h"

class Lexer
{
  private:
  public:
    std::list<Token> tokens;

    Lexer(){}
    void run(char*);
};