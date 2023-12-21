all: main.cpp token.h lexer.h lexer.cpp
	g++ main.cpp lexer.cpp -o cint
