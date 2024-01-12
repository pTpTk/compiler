#include "ast.h"

// Function
void
Function::print() {
    printf("Function: Name: %s\n", name.c_str());
}

void 
Function::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    insts.emplace_back(new FuncName(name));
    insts.emplace_back(new Push("ebp"));
    insts.emplace_back(new Movl("esp", "ebp"));
    for(auto stmt : statements) {
        stmt->assemble(insts);
    }
}
// Function

// Return
void
Return::print() {
    printf("Return statement\n");
}

void
Return::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    exp->assemble(insts);
    insts.emplace_back(new Movl("ebp", "esp"));
    insts.emplace_back(new Pop("ebp"));
    insts.emplace_back(new Ret);
}
// Return

// Declare
void
Declare::print() {
    printf("Declaration: int %s\n", varName.c_str());
}
// Declare

void
Constant::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    insts.emplace_back(new Movl(val, "eax"));
}

void 
Negation::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    exp->assemble(insts);
    insts.emplace_back(new Neg("eax"));
}

void
BitwiseComplement::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    exp->assemble(insts);
    insts.emplace_back(new Not("eax"));
}

void
LogicalNegation::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    exp->assemble(insts);

    insts.emplace_back(new Cmpl(0, "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Sete("al"));
}

void
Addition::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Addl("ecx", "eax"));
}

void
Subtraction::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expR->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expL->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Subl("ecx", "eax"));
}

void 
Multiplication::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Imul("ecx", "eax"));
}

void
Division::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expR->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expL->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Cdq());
    insts.emplace_back(new Idivl("ecx"));
}

void
Less::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Cmpl("ecx", "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Setl("al"));
}

void
Greater::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Cmpl("ecx", "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Setg("al"));
}

void
LessEqual::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Cmpl("ecx", "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Setle("al"));
}

void 
GreaterEqual::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Cmpl("ecx", "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Setge("al"));
}

void 
Equal::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Cmpl("ecx", "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Sete("al"));
}

void 
LogicalAnd::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    std::string clause2 = labelMaker();
    std::string end = labelMaker();

    expL->assemble(insts);
    insts.emplace_back(new Cmpl(0, "eax"));
    insts.emplace_back(new Jne(clause2));
    insts.emplace_back(new Jmp(end));
    insts.emplace_back(new Tag(clause2));
    expR->assemble(insts);
    insts.emplace_back(new Cmpl(0, "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Setne("al"));
    insts.emplace_back(new Tag(end));
}

void
LogicalOr::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    std::string clause2 = labelMaker();
    std::string end = labelMaker();

    expL->assemble(insts);
    insts.emplace_back(new Cmpl(0, "eax"));
    insts.emplace_back(new Je(clause2));
    insts.emplace_back(new Movl(1, "eax"));
    insts.emplace_back(new Jmp(end));
    insts.emplace_back(new Tag(clause2));
    expR->assemble(insts);
    insts.emplace_back(new Cmpl(0, "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Setne("al"));
    insts.emplace_back(new Tag(end));
}

void
NotEqual::assemble(std::vector<std::shared_ptr<Instruction>>& insts) {
    expL->assemble(insts);
    insts.emplace_back(new Push("eax"));
    expR->assemble(insts);
    insts.emplace_back(new Pop("ecx"));
    insts.emplace_back(new Cmpl("ecx", "eax"));
    insts.emplace_back(new Movl(0, "eax"));
    insts.emplace_back(new Setne("al"));
}