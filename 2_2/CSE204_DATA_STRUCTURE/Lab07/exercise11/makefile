exercise11: exercise11.o TextEditor.o
	g++ -std=c++14 -Wall -o exercise11 exercise11.o TextEditor.o

exercise11.o: exercise11.cpp TextEditor.h
	g++ -std=c++14 -Wall -c exercise11.cpp

TextEditor.o: TextEditor.cpp TextEditor.h
	g++ -std=c++14 -Wall -c TextEditor.cpp