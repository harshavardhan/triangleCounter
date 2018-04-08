all: nodeiterator edgeiteratorV1 edgeiteratorV2

nodeiterator: nodeIterator.cpp
	g++ nodeIterator.cpp -std=c++11 -o nodeiterator

edgeiteratorV1: edgeIterator_forward.cpp
	g++ edgeIterator_forward.cpp -std=c++11 -o edgeiteratorV1

edgeiteratorV2: edgeIterator_compactforward.cpp
	g++ edgeIterator_compactforward.cpp -std=c++11 -o edgeiteratorV2

clean:
	rm nodeiterator edgeiteratorV1 edgeiteratorV2