all: main.cpp token.h lexer.h lexer.cpp
	g++ -g main.cpp lexer.cpp parser.cpp -o cint
