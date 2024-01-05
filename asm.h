#pragma once

#include <string>

enum class Opcode
{
    Nop, Tag, Movl, Ret, Neg, Not, Cmpl, Sete, Push,
    Pop, Addl, Imul, Subl, Idivl, Cdq
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

class Push : public Instruction
{
  private:
  public:
    std::string dst;
    
    Push(std::string _dst)
    : dst(_dst) { op = Opcode::Push; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " push\t%%%s\n", dst.c_str());
    }
};

class Pop : public Instruction
{
  private:
  public:
    std::string dst;
    
    Pop(std::string _dst)
    : dst(_dst) { op = Opcode::Pop; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " pop\t%%%s\n", dst.c_str());
    }
};

class Addl : public Instruction
{
  private:
  public:
    std::string src;
    std::string dst;
    
    Addl(std::string _src, std::string _dst)
    : src(_src), dst(_dst) { op = Opcode::Addl; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " addl\t%%%s, %%%s\n", src.c_str(), dst.c_str());
    }
};

class Subl : public Instruction
{
  private:
  public:
    std::string src;
    std::string dst;
    
    Subl(std::string _src, std::string _dst)
    : src(_src), dst(_dst) { op = Opcode::Subl; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " subl\t%%%s, %%%s\n", src.c_str(), dst.c_str());
    }
};

class Imul : public Instruction
{
  private:
  public:
    std::string src;
    std::string dst;
    
    Imul(std::string _src, std::string _dst)
    : src(_src), dst(_dst) { op = Opcode::Imul; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " imul\t%%%s, %%%s\n", src.c_str(), dst.c_str());
    }
};

class Idivl : public Instruction
{
  private:
  public:
    std::string dst;
    
    Idivl(std::string _dst)
    :dst(_dst) { op = Opcode::Idivl; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " idivl\t%%%s\n", dst.c_str());
    }
};

class Cdq : public Instruction
{
  public:
    Cdq()
    { op = Opcode::Cdq; }
    
    void print(FILE* fp = stdout) {
        fprintf(fp, " cdq\n");
    }
};