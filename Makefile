all: $(wildcard *.cpp) $(wildcard *.h)
	g++ -g $(wildcard *.cpp) -o compile

debug: $(wildcard *.cpp) $(wildcard *.h)
	g++ -DD -g $(wildcard *.cpp) -o compile
