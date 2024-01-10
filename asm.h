#pragma once

#include <string>

std::string labelMaker();

enum class Opcode
{
    Nop, Tag, Movl, Ret, Neg, Not, Cmpl, Sete, Push,
    Pop, Addl, Imul, Subl, Idivl, Cdq, Setne, Je, Jne,
    Jmp, Setl, Setg, Setle, Setge
};

class Instruction
{
  public:
    Opcode op = Opcode::Nop;

    virtual void print(FILE* fp = stdout){}
};

class FuncName : public Instruction
{
  private:
    std::string tagName;
  public:
    FuncName(std::string _tagName)
    : tagName(_tagName) { op = Opcode::Tag; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " .globl %s\n", tagName.c_str());
        fprintf(fp, "%s:\n", tagName.c_str());
    }
};

class Tag : public Instruction
{
  private:
    std::string tagName;
  public:
    Tag(std::string _tagName)
    : tagName(_tagName) { op = Opcode::Tag; }

    void print(FILE* fp = stdout) {
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
    std::string src;
    std::string dst;
    bool has_imm;
    
    Cmpl(int _imm, std::string _dst)
    : imm(_imm), dst(_dst), has_imm(true) { op = Opcode::Cmpl; }\

    Cmpl(std::string _src, std::string _dst)
    : src(_src), dst(_dst), has_imm(false) { op = Opcode::Cmpl; }

    void print(FILE* fp = stdout) {
        if(has_imm) fprintf(fp, " cmpl\t$%d, %%%s\n", imm, dst.c_str());
        else        fprintf(fp, " cmpl\t$%%%s, %%%s\n", src.c_str(), dst.c_str());
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

class Setne : public Instruction
{
  private:
  public:
    std::string dst;
    
    Setne(std::string _dst)
    : dst(_dst) { op = Opcode::Setne; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " setne\t%%%s\n", dst.c_str());
    }
};

class Setl : public Instruction
{
  private:
  public:
    std::string dst;
    
    Setl(std::string _dst)
    : dst(_dst) { op = Opcode::Setne; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " setl\t%%%s\n", dst.c_str());
    }
};

class Setg : public Instruction
{
  private:
  public:
    std::string dst;
    
    Setg(std::string _dst)
    : dst(_dst) { op = Opcode::Setne; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " setg\t%%%s\n", dst.c_str());
    }
};

class Setle : public Instruction
{
  private:
  public:
    std::string dst;
    
    Setle(std::string _dst)
    : dst(_dst) { op = Opcode::Setne; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " setle\t%%%s\n", dst.c_str());
    }
};

class Setge : public Instruction
{
  private:
  public:
    std::string dst;
    
    Setge(std::string _dst)
    : dst(_dst) { op = Opcode::Setne; }

    void print(FILE* fp = stdout) {
        fprintf(fp, " setge\t%%%s\n", dst.c_str());
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
    : dst(_dst) { op = Opcode::Idivl; }

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

class Je : public Instruction
{
  public:
    std::string label;
    Je(std::string _label)
    : label(_label) {}

    void print(FILE* fp = stdout) {
        fprintf(fp, " je %s\n", label.c_str());
    }
};

class Jmp : public Instruction
{
  public:
    std::string label;
    Jmp(std::string _label)
    : label(_label) {}

    void print(FILE* fp = stdout) {
        fprintf(fp, " jmp %s\n", label.c_str());
    }
};

class Jne : public Instruction
{
  public:
    std::string label;
    Jne(std::string _label)
    : label(_label) {}

    void print(FILE* fp = stdout) {
        fprintf(fp, " jne %s\n", label.c_str());
    }
};