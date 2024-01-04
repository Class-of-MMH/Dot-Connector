#include "Box.h"
#include "Board.h"
using namespace sf;
////Get those edges
void Edge::inputEdges(int a, int b)
{
	Edges.push_back(std::make_pair(a, b));
	for (int i = 0; i < Edges.size(); i++) {
		// std::cout << Edges[i].first << "  " << Edges[i].second << std::endl;
	}
}

////Get the size to future use----------------------------------------
void Edge::setSize(int size, int totalLines)
{
	this->size = size;
	this->totalLines = totalLines;
}

////This function will check if the edges is valid for box or not.
bool Edge::in(int a, int b) {
	std::pair<int, int> test_pair(std::make_pair(a, b));
	for (auto i : Edges) {
		if (test_pair == i) {
			return true;
		}
	}
	return false;
}
