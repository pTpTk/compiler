all: main.cpp types.h lexer.h lexer.cpp
	g++ main.cpp lexer.cpp -o cint