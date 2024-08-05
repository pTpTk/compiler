#include "ast.h"

// Function
Function::Function() {}

void
Function::print() {
    printf("Function: Name: %s\n", name.c_str());
}

void 
Function::assemble(std::vector<std::string>& insts) {
    insts.emplace_back(FUNCNAME(name));
    insts.emplace_back(PUSH(%rbp));
    insts.emplace_back(MOVQ(%rsp, %rbp));
    block->assemble(insts);
    
    if(insts.back() != RET()) {
        insts.emplace_back(MOVL1($0, %eax));
        insts.emplace_back(MOVQ(%rbp, %rsp));
        insts.emplace_back(POP(%rbp));
        insts.emplace_back(RET());
    }
}

void
Function::declare(Program& prog) {
    prog.fmap.pushDeclaration(name, params.size());
}

void
Function::define(Program& prog) {
    vmap.alloc();
    vmap.pushFuncParams(params);
    prog.fmap.pushDef(name, params.size());
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
    insts.emplace_back(MOVQ(%rbp, %rsp));
    insts.emplace_back(POP(%rbp));
    insts.emplace_back(RET());
}
// Return

// Declare
Declare::Declare(VariableStack _vmap, std::string _name)
: name(_name), vmap(_vmap) { vmap.push(name); }

Declare::Declare(VariableStack _vmap, std::string _name, std::shared_ptr<Expression> _exp)
: name(_name), exp(_exp), vmap(_vmap) { vmap.push(name); }

void
Declare::print() {
    printf("Declaration: int %s\n", name.c_str());
}

void
Declare::assemble(std::vector<std::string>& insts) {
    if(exp.get() != nullptr) {
        exp->assemble(insts);
    }
    insts.emplace_back(PUSH(%rax));
}
// Declare

void
ExprStmt::assemble(std::vector<std::string>& insts) {
    if(exp.get())
        exp->assemble(insts);
}

void
If::assemble(std::vector<std::string>& insts) {
    if(elseStmt.get() != nullptr) {
        std::string elseL = labelMaker();
        std::string end = labelMaker();

        condition->assemble(insts);
        insts.emplace_back(CMPL($0, %eax));
        insts.emplace_back(JE(elseL));
        ifStmt->assemble(insts);
        insts.emplace_back(JMP(end));
        insts.emplace_back(TAG(elseL));
        elseStmt->assemble(insts);
        insts.emplace_back(TAG(end));
    }
    else {
        std::string end = labelMaker();

        condition->assemble(insts);
        insts.emplace_back(CMPL($0, %eax));
        insts.emplace_back(JE(end));
        ifStmt->assemble(insts);
        insts.emplace_back(TAG(end));
    }
}

void
Compound::assemble(std::vector<std::string>& insts) {
    for(auto stmt : statements) {
        stmt->assemble(insts);
    }

    int s = vmap.size();
    if(s && !vmap.first())
        insts.emplace_back(ADDQ2(s, %rsp));
}

void
While::assemble(std::vector<std::string>& insts) {
    std::string start = labelMaker();
    std::string end = labelMaker();

    labelPair->set(start, end);

    insts.emplace_back(TAG(start));
    condition->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(JE(end));
    body->assemble(insts);
    insts.emplace_back(JMP(start));
    insts.emplace_back(TAG(end));

    labelPair->clear();
}

void
Do::assemble(std::vector<std::string>& insts) {
    std::string start = labelMaker();
    std::string end = labelMaker();

    labelPair->set(start, end);

    insts.emplace_back(TAG(start));
    body->assemble(insts);
    condition->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(JE(end));
    insts.emplace_back(JMP(start));
    insts.emplace_back(TAG(end));

    labelPair->clear();
}

void
For::assemble(std::vector<std::string>& insts) {
    std::string cond = labelMaker();
    std::string post = labelMaker();
    std::string end = labelMaker();

    labelPair->set(post, end);

    initialExpr->assemble(insts);
    insts.emplace_back(TAG(cond));
    condition->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(JE(end));
    body->assemble(insts);
    insts.emplace_back(TAG(post));
    postExpr->assemble(insts);
    insts.emplace_back(JMP(cond));
    insts.emplace_back(TAG(end));

    labelPair->clear();
}

void
ForDecl::assemble(std::vector<std::string>& insts) {
    std::string cond = labelMaker();
    std::string post = labelMaker();
    std::string end = labelMaker();

    labelPair->set(post, end);

    initialDecl->assemble(insts);
    insts.emplace_back(TAG(cond));
    condition->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(JE(end));
    body->assemble(insts);
    insts.emplace_back(TAG(post));
    postExpr->assemble(insts);
    insts.emplace_back(JMP(cond));
    insts.emplace_back(TAG(end));

    labelPair->clear();

    int s = vmap.size();
    if(s)
        insts.emplace_back(ADDQ2(s, %rsp));
}

void
Break::assemble(std::vector<std::string>& insts) {
    assert(!labelPair->empty());

    insts.emplace_back(JMP(labelPair->second));
}

void
Continue::assemble(std::vector<std::string>& insts) {
    assert(!labelPair->empty());

    insts.emplace_back(JMP(labelPair->first));
}

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
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(ADDL(%ecx, %eax));
}

void
Subtraction::assemble(std::vector<std::string>& insts) {
    expR->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expL->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(SUBL(%ecx, %eax));
}

void 
Multiplication::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(IMUL(%ecx, %eax));
}

void
Division::assemble(std::vector<std::string>& insts) {
    expR->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expL->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(CDQ());
    insts.emplace_back(IDIVL(%ecx));
}

void
Less::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(CMPL(%eax, %ecx));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETL(%al));
}

void
Greater::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(CMPL(%eax, %ecx));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETG(%al));
}

void
LessEqual::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(CMPL(%eax, %ecx));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETLE(%al));
}

void 
GreaterEqual::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(CMPL(%eax, %ecx));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETGE(%al));
}

void 
Equal::assemble(std::vector<std::string>& insts) {
    expL->assemble(insts);
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(CMPL(%eax, %ecx));
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
    insts.emplace_back(PUSH(%rax));
    expR->assemble(insts);
    insts.emplace_back(POP(%rcx));
    insts.emplace_back(CMPL(%eax, %ecx));
    insts.emplace_back(MOVL1($0, %eax));
    insts.emplace_back(SETNE(%al));
}

void
Assignment::assemble(std::vector<std::string>& insts) {
    int index = vmap.lookup(name);
    exp->assemble(insts);
    insts.emplace_back(MOVL3(%eax, index, %rbp));
}

void
Variable::assemble(std::vector<std::string>& insts) {
    int paramIndex = vmap.lookupParams(name);
    
    // variable is not a function parameter
    if(paramIndex < 0) {
        int index = vmap.lookup(name);
        insts.emplace_back(MOVL4(index, %rbp, %eax));
    }
    // variable is a function parameter
    else {
        switch(paramIndex) {
            case 3:
                insts.emplace_back(MOVL1(%ecx, %eax));
                break;
            case 2:
                insts.emplace_back(MOVL1(%edx, %eax));
                break;
            case 1:
                insts.emplace_back(MOVL1(%esi, %eax));
                break;
            case 0:
                insts.emplace_back(MOVL1(%edi, %eax));
                break;
        }
    }
}

void
Conditional::assemble(std::vector<std::string>& insts) {
    std::string l3 = labelMaker();
    std::string end = labelMaker();

    e1->assemble(insts);
    insts.emplace_back(CMPL($0, %eax));
    insts.emplace_back(JE(l3));
    e2->assemble(insts);
    insts.emplace_back(JMP(end));
    insts.emplace_back(TAG(l3));
    e3->assemble(insts);
    insts.emplace_back(TAG(end));
}

void
FunctionCall::assemble(std::vector<std::string>& insts) {
    int paramCount = params.size();
    assert(paramCount < 5);
    
    switch(paramCount) {
        case 4:
        {
            auto& p = params[3];
            p->assemble(insts);
            insts.emplace_back(MOVL1(%eax, %ecx));
        }
        case 3:
        {
            auto& p = params[2];
            p->assemble(insts);
            insts.emplace_back(MOVL1(%eax, %edx));
        }
        case 2:
        {
            auto& p = params[1];
            p->assemble(insts);
            insts.emplace_back(MOVL1(%eax, %esi));
        }
        case 1:
        {
            auto& p = params[0];
            p->assemble(insts);
            insts.emplace_back(MOVL1(%eax, %edi));
        }
    }

    insts.emplace_back(CALL(name));
}