#pragma once

#include <vector>
#include <string>
#include <memory>

#include "ast.h"
#include "asm.h"

class Assembler
{
  private:
    void asmFunc(std::shared_ptr<Function>);
    void asmStmt(std::shared_ptr<Statement>);
    void asmReturn(std::shared_ptr<Statement>);
  public:
    std::vector<std::shared_ptr<Instruction>> output;

    Assembler(){}
    void run(Program&);
};