all: $(wildcard *.cpp) $(wildcard *.h)
	g++ -g $(wildcard *.cpp) -o cint

debug: $(wildcard *.cpp) $(wildcard *.h)
	g++ -DD -g $(wildcard *.cpp) -o cint
