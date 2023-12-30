#pragma once

#include <string>

enum class Opcode
{
    tag,
    movl,
    ret
};

class Instruction
{
  protected:
    Opcode op;
    int imm;
    std::string dst;
  public:
    virtual void print(FILE* fp = stdout){}
};

class Tag : public Instruction
{
  private:
    Opcode op;
    std::string tagName;
  public:
    Tag(std::string _tagName)
    : op(Opcode::tag), tagName(_tagName) {}

    void print(FILE* fp = stdout) {
        fprintf(fp, " .globl %s\n", tagName.c_str());
        fprintf(fp, "%s:\n", tagName.c_str());
    }
};

class Movl : public Instruction
{
  private:
    Opcode op;
    int imm;
    std::string dst;
  public:
    Movl(int _imm, std::string _dst)
    : op(Opcode::movl), imm(_imm), dst(_dst) {}

    void print(FILE* fp = stdout) {
        fprintf(fp, " movl\t$%d, %%%s\n", imm, dst.c_str());
    }
};

class Ret : public Instruction
{
  private:
    Opcode op;
  public:
    Ret()
    : op(Opcode::ret) {}
    
    void print(FILE* fp = stdout) {
        fprintf(fp, " ret\n");
    }
};