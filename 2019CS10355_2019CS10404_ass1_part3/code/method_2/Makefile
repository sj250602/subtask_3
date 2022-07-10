CXX=g++
RM=rm -f

compile:source_code.cpp
	$(CXX) source_code.cpp -o output -std=c++11 `pkg-config --cflags --libs opencv`
run:source_code.cpp
	./output
clear:
	$(RM) output