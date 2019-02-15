all: traceGen

traceGen: 
	g++ -std=c++14 -o trace main.cpp
	./trace.exe
