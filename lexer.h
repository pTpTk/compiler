#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cassert>

#include "types.h"

class Lexer
{
  private:
  public:
    std::vector<Token> tokens;

    Lexer(){}
    void run(char*);
};