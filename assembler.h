#pragma once

#include <vector>
#include <string>
#include <memory>

#include "ast.h"
#include "asm.h"

class Assembler
{
  private:
  public:
    std::vector<std::string> output;

    Assembler(){}
    void run(Program&);
};