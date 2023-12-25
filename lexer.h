#include <iostream>
#include <cstdio>
#include <list>
#include <cstring>
#include <string>
#include <cassert>

#include "token.h"

#define PUSH_TOKEN(TYPE) { \
tokens.emplace_back(TYPE); \
++token; \
break; \
}
class Lexer
{
  private:
  public:
    std::list<Token> tokens;

    Lexer(){}
    void run(char*);
};