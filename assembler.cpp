#include "assembler.h"

void
Assembler::run(Program& prog) {
    asmFunc(prog.function);
}

void
Assembler::asmFunc(std::shared_ptr<Function> func) {
    output.emplace_back(new Tag(func->name));

    asmStmt(func->statement);
}

void
Assembler::asmStmt(std::shared_ptr<Statement> stmt) {
    asmReturn(stmt);
}

void
Assembler::asmReturn(std::shared_ptr<Statement> stmt) {
    output.emplace_back(new Movl(stmt->getRetVal(), "eax"));
    output.emplace_back(new Ret);
}