#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cassert>

enum class Type
{
    symbol,
    keyword,
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

int main(int argc, char** argv) {
    if (argc !=2) {
        std::cerr << "Wrong input format!!\n";
        return 1;
    }

    FILE* fd = fopen(argv[1], "r");

    if (!fd) {
        std::cerr << "unable to open file " << *argv 
            << std::endl;
        return 1;
    }

    char* token;
    std::vector<Token> tokens;
    
    char *line = (char*)calloc(256, sizeof(char));
    size_t size = 255;
    
    int len;

    while(len = getdelim(&line, &size, ' ', fd) > 0) {
        printf("%s", line);
        token = line;
        while(*token != ' ' && *token != '\0') {
            switch(*token) {
                case '\n':
                    ++token;
                    break;
                // symbols
                case '{': case '}': 
                case '(': case ')':
                case ';': case '=':
                {
                    tokens.emplace_back(Type::symbol, *token);
                    ++token;
                    break;
                }
                case 'i':
                {
                    // int
                    if (len == 4 && strcmp("int ", line) == 0) {
                        tokens.emplace_back(Type::keyword, (int)(Keyword::INT));
                        token += 3;
                    }
                    // identifier
                    else {
                        int idfrLen = 0;
                        char* idfrStart = token;
                        while(isalpha(*token) || isdigit(*token)) {
                            ++idfrLen;
                            ++token;
                        }
                        std::string* idfrPtr = new std::string(idfrStart, idfrLen);
                        tokens.emplace_back(Type::identifier, (long)idfrPtr);
                    }
                    break;
                }
                case 'r':
                {
                    // return
                    if (len == 7 && strcmp("return ", line) == 0) {
                        tokens.emplace_back(Type::keyword, (int)Keyword::RETURN);
                        token += 6;
                    }
                    // identifier
                    else {
                        int idfrLen = 0;
                        char* idfrStart = token;
                        while(isalpha(*token) || isdigit(*token)) {
                            ++idfrLen;
                            ++token;
                        }
                        std::string* idfrPtr = new std::string(idfrStart, idfrLen);
                        tokens.emplace_back(Type::identifier, (long)idfrPtr);
                    }
                    break;
                }
                // identifier
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
                case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q':
                case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
                case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q':
                case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
                {
                    int idfrLen = 0;
                    char* idfrStart = token;
                    while(isalpha(*token) || isdigit(*token)) {
                        ++idfrLen;
                        ++token;
                    }
                    std::string* idfrPtr = new std::string(idfrStart, idfrLen);
                    tokens.emplace_back(Type::identifier, (long)idfrPtr);
                    break;
                }
                // integer
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                {
                    int numLen = 0;
                    char* numStart = token;
                    while(isdigit(*token)) {
                        ++numLen;
                        ++token;
                    }
                    char* numStr = (char*)calloc(numLen+1, sizeof(char));
                    memcpy(numStr, numStart, numLen);
                    long num = atol(numStr);
                    free(numStr);
                    tokens.emplace_back(Type::integer, num);
                    break;
                }
                default:
                    printf("unrecongnized token \"%s\"\n", token);
                    assert(false);
            }
        }
    }

    std::cout << "lexed outputs:\n";
    for(auto& t : tokens) {
        t.print();
        std::cout << " ";
    }

    return 0;
}