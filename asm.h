#pragma once

#include <string>

enum class Opcode
{
    nop,
    tag,
    movl,
    ret
};

class Instruction
{
  public:
    Opcode op = Opcode::nop;

    virtual void print(FILE* fp = stdout){}
};

class Tag : public Instruction
{
  private:
    std::string tagName;
  public:
    Tag(std::string _tagName)
    : tagName(_tagName) { op = Opcode::tag; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " .globl %s\n", tagName.c_str());
        fprintf(fp, "%s:\n", tagName.c_str());
    }
};

class Movl : public Instruction
{
  private:
  public:
    int imm;
    std::string dst;
    
    Movl(int _imm, std::string _dst)
    : imm(_imm), dst(_dst) { op = Opcode::movl; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " movl\t$%d, %%%s\n", imm, dst.c_str());
    }
};

class Ret : public Instruction
{
  public:
    Ret()
    { op = Opcode::ret; }
    
    void print(FILE* fp = stdout) {
        fprintf(fp, " ret\n");
    }
};