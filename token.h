#pragma once

#include <cstdio>
#include <iostream>
#include <string>

enum class Type
{
    symbol_brace_l,
    symbol_brace_r,
    symbol_parenthesis_l,
    symbol_parenthesis_r,
    symbol_bracket_l,
    symbol_bracket_r,
    symbol_semicolon,
    symbol_assign,
    symbol_negation,
    symbol_bit_complement,
    symbol_logical_negation,
    symbol_logical_and,
    symbol_logical_or,
    symbol_addition,
    symbol_multiplication,
    symbol_division,
    symbol_equal,
    symbol_not_equal,
    symbol_less,
    symbol_less_equal,
    symbol_greater,
    symbol_greater_equal,
    symbol_colon,
    symbol_question_mark,

    keyword_int,
    keyword_return,
    keyword_if,
    keyword_else,
    keyword_for,
    keyword_do,
    keyword_while,
    keyword_break,
    keyword_continue,

    identifier,
    integer
};

enum class Keyword
{
    INT, RETURN
};

class Token
{
  public:
    Type type;
    long val;

    Token(Type _type, long _val = 0): type(_type), val(_val) {}
    
    void print()
    {
        switch(type) {
            case Type::symbol_brace_l:
                printf("{");
                break;
            case Type::symbol_brace_r: 
                printf("}");
                break;
            case Type::symbol_parenthesis_l: 
                printf("(");
                break;
            case Type::symbol_parenthesis_r: 
                printf(")");
                break;
            case Type::symbol_bracket_l: 
                printf("[");
                break;
            case Type::symbol_bracket_r: 
                printf("]");
                break;
            case Type::symbol_semicolon: 
                printf(";");
                break;
            case Type::symbol_assign: 
                printf("=");
                break;
            case Type::symbol_negation:
                printf("-");
                break;
            case Type::symbol_bit_complement:
                printf("~");
                break;
            case Type::symbol_logical_negation:
                printf("!");
                break;
            case Type::symbol_addition:
                printf("+");
                break;
            case Type::symbol_multiplication:
                printf("*");
                break;
            case Type::symbol_division:
                printf("/");
                break;
            case Type::symbol_logical_and:
                printf("&&");
                break;
            case Type::symbol_logical_or:
                printf("||");
                break;
            case Type::symbol_equal:
                printf("==");
                break;
            case Type::symbol_not_equal:
                printf("!=");
                break;
            case Type::symbol_less:
                printf("<");
                break;
            case Type::symbol_less_equal:
                printf("<=");
                break;
            case Type::symbol_greater:
                printf(">");
                break;
            case Type::symbol_greater_equal:
                printf(">=");
                break;
            case Type::symbol_colon:
                printf(":");
                break;
            case Type::symbol_question_mark:
                printf("?");
                break;
            case Type::keyword_int:
            case Type::keyword_return:
            case Type::keyword_if:
            case Type::keyword_else:
            case Type::keyword_for:
            case Type::keyword_do:
            case Type::keyword_while:
            case Type::keyword_break:
            case Type::keyword_continue:
            case Type::identifier:
            {
                std::string* strPtr = (std::string*)val;
                std::cout << *strPtr;
                break;
            }
            case Type::integer:
                printf("%ld", val);
                break;
        }
    }

};