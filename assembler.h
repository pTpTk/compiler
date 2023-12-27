#pragma once

#include <vector>
#include <string>
#include <memory>

#include "ast.h"

class Assembler
{
  private:
    void asmFunc(std::shared_ptr<Function>);
    void asmStmt(std::shared_ptr<Statement>);
    void asmReturn(std::shared_ptr<Statement>);
  public:
    std::vector<std::string> output;

    Assembler(){}
    void run(Program&);
};