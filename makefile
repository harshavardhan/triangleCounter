all: nodeiterator edgeiterator

nodeiterator: nodeIterator.cpp
	g++ nodeIterator.cpp -std=c++11 -o nodeiterator

edgeiterator: edgeiterator.cpp
	g++ edgeiterator.cpp -std=c++11 -o edgeiterator

clean:
	rm edgeiterator nodeiterator
