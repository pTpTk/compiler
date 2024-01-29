#pragma once

#include <string>

std::string labelMaker();

#define TAG(X) X + ":\n"
#define FUNCNAME(X) " .globl " + X + "\n" + TAG(X)

#define ADDL(X,Y)    " addl\t" #X ", " #Y "\n"
#define ADDL2(X,Y)   " addl\t" "$" + std::to_string(X) + ", " #Y "\n"
#define CALL(X)      " call\t" + X + "\n"
#define CDQ()        " cdq\n"
#define CMPL(X,Y)    " cmpl\t" #X ", " #Y "\n"
#define IDIVL(X)     " idivl\t" #X "\n"
#define IMUL(X,Y)    " imul\t" #X ", " #Y "\n"
#define JE(X)        " je\t" + X + "\n"
#define JMP(X)       " jmp\t" + X + "\n"
#define JNE(X)       " jne\t" + X + "\n"
#define MOVL1(X,Y)   " movl\t" #X ", " #Y "\n"
#define MOVL2(X,Y)   " movl\t$" + std::to_string(X) + ", " #Y "\n"
#define MOVL3(X,Y,Z) " movl\t" #X ", " + std::to_string(Y) + "(" #Z ")" "\n"
#define MOVL4(X,Y,Z) " movl\t" + std::to_string(X) + "(" #Y ")" ", " #Z "\n"
#define NEG(X)       " neg\t" #X "\n"
#define NOT(X)       " not\t" #X "\n"
#define POP(X)       " pop\t" #X "\n"
#define PUSH(X)      " push\t" #X "\n"
#define RET()        " ret\n"
#define SETE(X)      " sete\t" #X "\n"
#define SETG(X)      " setg\t" #X "\n"
#define SETGE(X)     " setge\t" #X "\n"
#define SETL(X)      " setl\t" #X "\n"
#define SETLE(X)     " setle\t" #X "\n"
#define SETNE(X)     " setne\t" #X "\n"
#define SUBL(X,Y)    " subl\t" #X ", " #Y "\n"