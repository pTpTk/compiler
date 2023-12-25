#pragma once

#include <cstdio>
#include <iostream>
#include <string>

enum class Type
{
    symbol,
    keyword,
    identifier,
    integer
};

class Token
{
  public:
    Type type;
    long val;

    Token(Type _type, long _val): type(_type), val(_val) {}
    
    void print()
    {
        switch(type) {
            case Type::symbol:
                printf("%c", (char)val);
                break;
            case Type::keyword:
            {
                Keyword key = (Keyword)val;
                switch(key) {
                    case Keyword::INT:
                        printf("int");
                        break;
                    case Keyword::RETURN:
                        printf("return");
                        break;
                }
                break;
            }
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