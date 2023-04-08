#include "MethodChangeTwoEdges.h"

MethodChangeTwoEdges::MethodChangeTwoEdges(int verticesAmount)
{
	//srand(time(NULL));
	this->verticesAmount = verticesAmount;
	broodForceWayWeight = 10000000.0;
	GenerateEdgeMatrix();
	PrintEdgeMatrix();
	BroodForceMethod();
	std::cout << std::endl;
	PrintBroodForceMethodWay();
	std::cout << std::endl;
	FindWay();
}

void MethodChangeTwoEdges::BroodForceMethod()
{
	for (int i = 0; i < verticesAmount; ++i) {
		int counter = 0;
		int sumWeight = 0;
		std::vector<int> way;
		way.push_back(i);
		std::vector<bool> checkedPoints;
		checkedPoints.resize(verticesAmount);
		checkedPoints[i] = true;
		BroodForceMethodRecursion(way, counter, sumWeight, i, checkedPoints);
	}
} 

void MethodChangeTwoEdges::FindWay()
{
	//Statistic param
	
	// 
	std::vector<std::vector<bool>> rightEdgesMatrix;
	rightEdgesMatrix.reserve(verticesAmount);
	for (int i = 0; i < verticesAmount; ++i) {
		std::vector<bool> rightEdgesMassive(verticesAmount, false);
		rightEdgesMatrix.push_back(rightEdgesMassive);
	}
	std::list<Edge> minWay;
	int minWayWeight = 0;
	if (true) {
		for (int i = 0; i < verticesAmount - 1; ++i) {
			if (i != verticesAmount - 1) {
				minWay.push_back(edges[i][i + 1]);
				minWayWeight += edges[i][i + 1].GetWeight();
				rightEdgesMatrix[i][i + 1] = true;
			}
			minWay.push_back(edges[verticesAmount - 1][0]);
			minWayWeight += edges[verticesAmount - 1][0].GetWeight();
			rightEdgesMatrix[verticesAmount - 1][0] = true;
		}
	}
	while (false) {
		for (int oneE = 0; oneE < verticesAmount; ++oneE) {
			for (int twoE = 0; twoE < verticesAmount; ++twoE) {
				if (minWay[oneE].GetFirstPoint() != minWay[twoE].GetFirstPoint() && minWay[oneE].GetFirstPoint() != minWay[twoE].GetSecondPoint()
					&& minWay[oneE].GetSecondPoint() != minWay[twoE].GetFirstPoint() && minWay[oneE].GetSecondPoint() != minWay[twoE].GetSecondPoint()) {
					// создаём суммы рёбер для двух взможных вариантов
					Edge firstPairEdgeOne = edges[minWay[oneE].GetFirstPoint()][minWay[twoE].GetFirstPoint()];
					Edge firstPairEdgeTwo = edges[minWay[oneE].GetSecondPoint()][minWay[twoE].GetSecondPoint()];
					int firstPairSum = firstPairEdgeOne.GetWeight() + firstPairEdgeTwo.GetWeight();
					//---
					Edge secondPairEdgeOne = edges[minWay[oneE].GetFirstPoint()][minWay[twoE].GetSecondPoint()];
					Edge secondPairEdgeTwo = edges[minWay[oneE].GetSecondPoint()][minWay[twoE].GetFirstPoint()];
					int secondPairSum = secondPairEdgeOne.GetWeight() + secondPairEdgeTwo.GetWeight();
					//---
					int chooseEdgesSum = minWay[oneE].GetWeight() + minWay[twoE].GetWeight();
					if (chooseEdgesSum < firstPairSum) {
						if (vertices[firstPairEdgeOne.GetFirstPoint()].GetVerticeOne() != firstPairEdgeOne.GetSecondPoint()
							&& vertices[firstPairEdgeOne.GetFirstPoint()].GetVerticeTwo() != firstPairEdgeOne.GetSecondPoint()
							&& vertices[firstPairEdgeTwo.GetFirstPoint()].GetVerticeOne() != firstPairEdgeTwo.GetSecondPoint()
							&& vertices[firstPairEdgeTwo.GetFirstPoint()].GetVerticeTwo() != firstPairEdgeTwo.GetSecondPoint()) {
							// теперь делаем проверку на подходимость для замены рёбер
							std::vector<Vertice> matchVertices = vertices;
							if (matchVertices[minWay[oneE].GetFirstPoint()].GetVerticeOne() == minWay[oneE].GetSecondPoint()) {
								matchVertices[minWay[oneE].GetFirstPoint()].SetVerticeOne() = 
							}
							else {

							}
							int stepsAmount = 0;
							for (int g = 0; g < verticesAmount; ++g) {

							}
						}
						else {

						}
					}
					else if (chooseEdgesSum < secondPairSum) {

					}
				}
			}
		}
	}
	std::cout << "0" << std::endl;
}

void MethodChangeTwoEdges::PrintEdgeMatrix()
{
	for (int i = 0; i < verticesAmount; ++i) {
		for (int j = 0; j < verticesAmount; ++j) {
			std::cout << edges[i][j].GetWeight() << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void MethodChangeTwoEdges::PrintBroodForceMethodWay()
{
	for (auto point : broodForceWayMassive) {
		std::cout << point << "\t";
	}
	std::cout << "Weight - " << broodForceWayWeight << std::endl;
}

void MethodChangeTwoEdges::GenerateEdgeMatrix()
{
	edges.reserve(verticesAmount);
	for (int i = 0; i < verticesAmount; ++i) {
		std::vector<Edge> insideEdgeVector;
		insideEdgeVector.reserve(verticesAmount);
		for (int j = 0; j < verticesAmount; j++) {
			if (!IsEquals(i, j)) {
				int weight = rand() / 10;
				if (!IsMore(i, j)) {
					insideEdgeVector.push_back(Edge(i, j, weight));
				}
				else {
					insideEdgeVector.push_back(Edge(j, i, edges[j][i].GetWeight()));
				}
			}
			else
			{
				insideEdgeVector.push_back(Edge(i, j, 1000000.0));
			}
		}
		edges.push_back(insideEdgeVector);
	}
}

void MethodChangeTwoEdges::BroodForceMethodRecursion(std::vector<int> wayM, int counterM, int sumWeightM, int lastPoint, std::vector<bool> checkedPointsM)
{
	for (int i = 0; i < verticesAmount; i++) {
		int counter = counterM + 1;
		int sumWeight = sumWeightM;
		std::vector<int> way = wayM;
		std::vector<bool> checkedPoints = checkedPointsM;
		if (edges[lastPoint][i].GetWeight() != 0) {
			if (counter < verticesAmount - 1 && !checkedPoints[i]) {
				sumWeight += edges[lastPoint][i].GetWeight();
				way.push_back(i);
				checkedPoints[i] = true;
				BroodForceMethodRecursion(way, counter, sumWeight, i, checkedPoints);
			}
			else if (counter == verticesAmount - 1 && !checkedPoints[i]) {
				sumWeight += edges[i][lastPoint].GetWeight();
				sumWeight += edges[way[0]][i].GetWeight();
				way.push_back(i);
				if (sumWeight < broodForceWayWeight) {
					broodForceWayMassive = way;
					broodForceWayWeight = sumWeight;
				}
			}
		}
	}
}

bool MethodChangeTwoEdges::IsEquals(int oneNumber, int twoNumber)
{
	return oneNumber == twoNumber ? true : false;
}

bool MethodChangeTwoEdges::IsMore(int oneNumber, int twoNumber)
{
	return oneNumber > twoNumber ? true : false;
}
