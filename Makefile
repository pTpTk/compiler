all: $(wildcard *.cpp) $(wildcard *.h)
	g++ -g $(wildcard *.cpp) -o cint
