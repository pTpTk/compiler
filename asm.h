#pragma once

#include <string>

enum class Opcode
{
    Nop,
    Tag,
    Movl,
    Ret,
    Neg,
    Not,
    Cmpl,
    Sete
};

class Instruction
{
  public:
    Opcode op = Opcode::Nop;

    virtual void print(FILE* fp = stdout){}
};

class Tag : public Instruction
{
  private:
    std::string tagName;
  public:
    Tag(std::string _tagName)
    : tagName(_tagName) { op = Opcode::Tag; }

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
    : imm(_imm), dst(_dst) { op = Opcode::Movl; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " movl\t$%d, %%%s\n", imm, dst.c_str());
    }
};

class Ret : public Instruction
{
  public:
    Ret()
    { op = Opcode::Ret; }
    
    void print(FILE* fp = stdout) {
        fprintf(fp, " ret\n");
    }
};

class Neg : public Instruction
{
  private:
  public:
    std::string dst;
    
    Neg(std::string _dst)
    : dst(_dst) { op = Opcode::Neg; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " neg\t%%%s\n", dst.c_str());
    }
};

class Not : public Instruction
{
  private:
  public:
    std::string dst;
    
    Not(std::string _dst)
    : dst(_dst) { op = Opcode::Not; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " not\t%%%s\n", dst.c_str());
    }
};

class Cmpl : public Instruction
{
  private:
  public:
    int imm;
    std::string dst;
    
    Cmpl(int _imm, std::string _dst)
    : imm(_imm), dst(_dst) { op = Opcode::Cmpl; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " cmpl\t$%d, %%%s\n", imm, dst.c_str());
    }
};

class Sete : public Instruction
{
  private:
  public:
    std::string dst;
    
    Sete(std::string _dst)
    : dst(_dst) { op = Opcode::Sete; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " sete\t%%%s\n", dst.c_str());
    }
};