#include "lexer.h"

void Lexer::run(char* filename) {
    FILE* fd = fopen(filename, "r");

    if (!fd) {
        std::cerr << "unable to open file " << filename 
            << std::endl;
        assert(false);
    }

    char* token;

    char *line = (char*)calloc(256, sizeof(char));
    size_t size = 255;
    
    int len;

    while(len = getdelim(&line, &size, ' ', fd) > 0) {
        token = line;
        while(*token != ' ' && *token != '\0') {
            switch(*token) {
                case '\n':
                    ++token;
                    break;
                // symbols
                case '{':
                    PUSH_TOKEN(Type::symbol_brace_l);
                case '}': 
                    PUSH_TOKEN(Type::symbol_brace_r);
                case '(':
                    PUSH_TOKEN(Type::symbol_parenthesis_l);
                case ')':
                    PUSH_TOKEN(Type::symbol_parenthesis_r);
                case ';':
                    PUSH_TOKEN(Type::symbol_semicolon);
                case '=':
                    PUSH_TOKEN(Type::symbol_equal);
                case 'i':
                {
                    // int
                    if (len == 4 && strcmp("int ", line) == 0) {
                        tokens.emplace_back(Type::keyword_int, (int)(Keyword::INT));
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
                        tokens.emplace_back(Type::keyword_return, (int)Keyword::RETURN);
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
}