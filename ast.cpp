#include "ast.h"

// Function
Function::Function() : vmap(new VariableMap) {}

void
Function::print() {
    printf("Function: Name: %s\n", name.c_str());
}

void 
Function::assemble(std::vector<std::string>& insts) {
    insts.emplace_back(FUNCNAME(name));
    insts.emplace_back(PUSH(%ebp));
    insts.emplace_back(MOVL1(%esp, %ebp));
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
Return::assemble(std::vector<std::string>& insts) {
    exp->assemble(insts);
    insts.emplace_back(MOVL1(%ebp, %esp));
    insts.emplace_back(POP(%ebp));
    insts.emplace_back(RET());
}
// Return

// Declare
Declare::Declare(std::shared_ptr<VariableMap> _vmap, std::string _name)
: name(_name), vmap(_vmap) { vmap->push(name); }

Declare::Declare(std::shared_ptr<VariableMap> _vmap, std::string _name, std::shared_ptr<Expression> _exp)
: name(_name), exp(_exp), vmap(_vmap) { 
    vmap->push(name);
    exp = std::make_shared<Assignment>(vmap, name, exp);
}

void
Declare::print() {
    printf("Declaration: int %s\n", name.c_str());
}

void
Declare::assemble(std::vector<std::string>& insts) {
    if(exp.get() != nullptr) {
        exp->assemble(insts);
    }
}
// Declare

void
Constant::assemble(std::vector<std::string>& insts) {
    insts.emplace_back(MOVL2(val, %eax));
}

void 
Negation::assemble(std::vector<std::string>& insts) {
    exp->assemble(insts);
    insts.emplace_back(NEG(%eax));
}

void
BitwiseComplement::assemble(std::vector<std::string>& insts) {
    exp->assemble(insts);
    insts.emplace_back(NOT(%eax));
}

void
LogicalNegation::assemble(std::vector<std::string>& insts) {
    exp->assemble(insts);

    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETE(%al));
}

void
Addition::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(ADDL(%ecx, %eax));
}

void
Subtraction::assemble(std::vector<std::string>& insts) {
    expR->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expL->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(SUBL(%ecx, %eax));
}

void 
Multiplication::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(IMUL(%ecx, %eax));
}

void
Division::assemble(std::vector<std::string>& insts) {
    expR->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expL->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(CDQ());
    insts.emplace_back(IDIVL(%ecx));
}

void
Less::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(CMPL(%ecx, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETL(%al));
}

void
Greater::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(CMPL(%ecx, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETG(%al));
}

void
LessEqual::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(CMPL(%ecx, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETLE(%al));
}

void 
GreaterEqual::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(CMPL(%ecx, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETGE(%al));
}

void 
Equal::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(CMPL(%ecx, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETE(%al));
}

void 
LogicalAnd::assemble(std::vector<std::string>& insts) {
    std::string clause2 = labelMaker();
    std::string end = labelMaker();

    expL->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(JNE(clause2));
    insts.emplace_back(JMP(end));
    insts.emplace_back(TAG(clause2));
    expR->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETNE(%al));
    insts.emplace_back(TAG(end));
}

void
LogicalOr::assemble(std::vector<std::string>& insts) {
    std::string clause2 = labelMaker();
    std::string end = labelMaker();

    expL->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(JE(clause2));
    insts.emplace_back(MOVL1($1, %eax));
    insts.emplace_back(JMP(end));
    insts.emplace_back(TAG(clause2));
    expR->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETNE(%al));
    insts.emplace_back(TAG(end));
}

void
NotEqual::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%eax));
    expR->assemble(insts);
    insts.emplace_back(POP(%ecx));
    insts.emplace_back(CMPL(%ecx, %eax));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETNE(%al));
}

void
Assignment::assemble(std::vector<std::string>& insts) {
    int index = vmap->lookup(name);
    exp->assemble(insts);
    insts.emplace_back(MOVL3(%eax, index, %ebp));
}

void
Variable::assemble(std::vector<std::string>& insts) {
    int index = vmap->lookup(name);
    insts.emplace_back(MOVL4(index, %ebp, %eax));
}