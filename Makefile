CXXFLAGS="-std=c++14"

all: main.cpp
	g++ $(CXXFLAGS) main.cpp -o typeracer -lncurses
