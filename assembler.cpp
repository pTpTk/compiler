#include "assembler.h"

void
Assembler::run(Program& prog) {
    asmFunc(prog.function);
}

void
Assembler::asmFunc(std::shared_ptr<Function> func) {
    output.emplace_back(new FuncName(func->name));
    for(auto stmt : func->statements) {
        asmStmt(stmt);
    }
}

void
Assembler::asmStmt(std::shared_ptr<Statement> stmt) {
    asmReturn(stmt);
}

void
Assembler::asmReturn(std::shared_ptr<Statement> stmt) {
    auto retPtr = std::dynamic_pointer_cast<Return>(stmt);
    retPtr->exp->assemble(output);
    output.emplace_back(new Ret);
}

void
Assembler::asmExpr(std::shared_ptr<Expression> expr) {

}