all: nodeiterator edgeiteratorV1 edgeiteratorV2 sqrtDecompn

nodeiterator: nodeIterator.cpp
	g++ nodeIterator.cpp -std=c++11 -o nodeiterator

edgeiteratorV1: edgeIterator_forward.cpp
	g++ edgeIterator_forward.cpp -std=c++11 -o edgeiteratorV1

edgeiteratorV2: edgeIterator_compactforward.cpp
	g++ edgeIterator_compactforward.cpp -std=c++11 -o edgeiteratorV2

sqrtDecompn: sqrtDecompn.cpp
	g++ sqrtDecompn.cpp -std=c++11 -o sqrtDecompn

clean:
	rm nodeiterator edgeiteratorV1 edgeiteratorV2 sqrtDecompn