#include "main.h"
#include "MethodChangeTwoEdges.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	MethodChangeTwoEdges methodChangeTwoEdges(4);
}
/*std::vector<std::vector<bool>> rightEdgesMatrix;
	rightEdgesMatrix.reserve(verticesAmount);
	for (int i = 0; i < verticesAmount; ++i) {
		std::vector<bool> rightEdgesMassive(verticesAmount, false);
		rightEdgesMatrix.push_back(rightEdgesMassive);
	}
	std::list<Edge> minWay;
	int minWayWeight = 0;
	if (true) {
		for (int i = 0; i < verticesAmount - 1; ++i) {
			minWay.push_back(edges[i][i + 1]);
			rightEdgesMatrix[i][i + 1] = true;
			minWayWeight += edges[i + 1][i].GetWeight();
		}
		minWay.push_back(edges[verticesAmount - 1][0]);
		rightEdgesMatrix[verticesAmount - 1][0] = true;
		minWayWeight += edges[verticesAmount - 1][0].GetWeight();
	}
	while (false) {
		for (auto oneE = minWay.begin(); oneE != minWay.end(); ++oneE) {
			for (auto twoE = minWay.begin(); twoE != minWay.end(); ++twoE) {
				if ()
			}
		}
	}
	std::cout << "-0-" << std::endl;*/