#include "MethodChangeTwoEdges.h"

MethodChangeTwoEdges::MethodChangeTwoEdges(int verticesAmount)
{
	srand(time(NULL));
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
	std::vector<Edge> minWay;
	int minWayWeight = 0;
	if (true) {
		for (int i = 0; i < verticesAmount - 1; ++i) {
			if (i != verticesAmount - 1) {
				minWay.push_back(edges[i][i + 1]);
				minWayWeight += edges[i][i + 1].GetWeight();
				rightEdgesMatrix[i][i + 1] = true;
				rightEdgesMatrix[i + 1][i] = true;
			}
		}
		minWay.push_back(edges[verticesAmount - 1][0]);
		minWayWeight += edges[verticesAmount - 1][0].GetWeight();
		rightEdgesMatrix[verticesAmount - 1][0] = true;
		rightEdgesMatrix[0][verticesAmount - 1] = true;
	}
	std::cout << "Start weight = " << minWayWeight << std::endl;
	int era = 0;
	while (true) {
		std::cout << "Era - " << era << std::endl;
		era++;
		bool tumbler = false;
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
					//---
					bool firstPairEnter = false;
					bool secondPairEnter = false;
					if (rightEdgesMatrix[firstPairEdgeOne.GetFirstPoint()][firstPairEdgeOne.GetSecondPoint()]
						|| rightEdgesMatrix[firstPairEdgeTwo.GetFirstPoint()][firstPairEdgeTwo.GetSecondPoint()]) {
						firstPairEnter = true;
					}
					if (rightEdgesMatrix[secondPairEdgeOne.GetFirstPoint()][secondPairEdgeOne.GetSecondPoint()]
						|| rightEdgesMatrix[secondPairEdgeTwo.GetFirstPoint()][secondPairEdgeTwo.GetSecondPoint()]) {
						secondPairEnter = true;
					}
					//---
					if (firstPairEnter) {
						if (chooseEdgesSum > secondPairSum) {
							std::cout << "Method - 2" << std::endl;
							std::cout << "Choose edges | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << " | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << std::endl;
							std::cout << "Change edges | " << secondPairEdgeOne.GetFirstPoint() << " - " << secondPairEdgeOne.GetSecondPoint() << " | " << secondPairEdgeTwo.GetFirstPoint() << " - " << secondPairEdgeTwo.GetSecondPoint() << std::endl;
							std::cout << "Minus weight - " << chooseEdgesSum - secondPairSum << std::endl;
							rightEdgesMatrix[minWay[oneE].GetFirstPoint()][minWay[oneE].GetSecondPoint()] = false;
							rightEdgesMatrix[minWay[oneE].GetSecondPoint()][minWay[oneE].GetFirstPoint()] = false;
							rightEdgesMatrix[minWay[twoE].GetFirstPoint()][minWay[twoE].GetSecondPoint()] = false;
							rightEdgesMatrix[minWay[twoE].GetSecondPoint()][minWay[twoE].GetFirstPoint()] = false;
							rightEdgesMatrix[secondPairEdgeOne.GetFirstPoint()][secondPairEdgeOne.GetSecondPoint()] = true;
							rightEdgesMatrix[secondPairEdgeOne.GetSecondPoint()][secondPairEdgeOne.GetFirstPoint()] = true;
							rightEdgesMatrix[secondPairEdgeTwo.GetFirstPoint()][secondPairEdgeTwo.GetSecondPoint()] = true;
							rightEdgesMatrix[secondPairEdgeTwo.GetSecondPoint()][secondPairEdgeTwo.GetFirstPoint()] = true;
							minWay[oneE] = secondPairEdgeOne;
							minWay[twoE] = secondPairEdgeTwo;
							minWayWeight = minWayWeight - chooseEdgesSum + secondPairSum;
							tumbler = true;
							if (true) {
								for (int i = 0; i < verticesAmount; ++i) {
									std::cout << minWay[i].GetFirstPoint() << " - " << minWay[i].GetSecondPoint() << " | ";
								}
								std::cout << minWayWeight << std::endl;
							}
							break;
						}
					} 
					else if (secondPairEnter) {
						if (chooseEdgesSum > firstPairSum) {
							std::cout << "Method - 1" << std::endl;
							std::cout << "Choose edges | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << " | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << std::endl;
							std::cout << "Change edges | " << firstPairEdgeOne.GetFirstPoint() << " - " << firstPairEdgeOne.GetSecondPoint() << " | " << firstPairEdgeTwo.GetFirstPoint() << " - " << firstPairEdgeTwo.GetSecondPoint() << std::endl;
							std::cout << "Minus weight - " << chooseEdgesSum - firstPairSum << std::endl;
							rightEdgesMatrix[minWay[oneE].GetFirstPoint()][minWay[oneE].GetSecondPoint()] = false;
							rightEdgesMatrix[minWay[oneE].GetSecondPoint()][minWay[oneE].GetFirstPoint()] = false;
							rightEdgesMatrix[minWay[twoE].GetFirstPoint()][minWay[twoE].GetSecondPoint()] = false;
							rightEdgesMatrix[minWay[twoE].GetSecondPoint()][minWay[twoE].GetFirstPoint()] = false;
							rightEdgesMatrix[firstPairEdgeOne.GetFirstPoint()][firstPairEdgeOne.GetSecondPoint()] = true;
							rightEdgesMatrix[firstPairEdgeOne.GetSecondPoint()][firstPairEdgeOne.GetFirstPoint()] = true;
							rightEdgesMatrix[firstPairEdgeTwo.GetFirstPoint()][firstPairEdgeTwo.GetSecondPoint()] = true;
							rightEdgesMatrix[firstPairEdgeTwo.GetSecondPoint()][firstPairEdgeTwo.GetFirstPoint()] = true;
							minWay[oneE] = firstPairEdgeOne;
							minWay[twoE] = firstPairEdgeTwo;
							minWayWeight = minWayWeight - chooseEdgesSum + firstPairSum;
							tumbler = true;
							if (true) {
								for (int i = 0; i < verticesAmount; ++i) {
									std::cout << minWay[i].GetFirstPoint() << " - " << minWay[i].GetSecondPoint() << " | ";
								}
								std::cout << minWayWeight << std::endl;
							}
							break;
						}
					}
					else {
						int stepVertice = minWay[oneE].GetFirstPoint();
						int lastVertice = minWay[oneE].GetSecondPoint();
						while (true) {
							bool tumblerEnd = false;
							for (int t = 0; t < verticesAmount; ++t) {
								if (rightEdgesMatrix[stepVertice][t]) {
									if (t != lastVertice) {
										lastVertice = stepVertice;
										stepVertice = t;
										if (t == minWay[twoE].GetFirstPoint()) {
											tumblerEnd = true;
											if (chooseEdgesSum > secondPairSum) {
												std::cout << "Method - 3.2" << std::endl;
												std::cout << "Choose edges | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << " | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << std::endl;
												std::cout << "Change edges | " << secondPairEdgeOne.GetFirstPoint() << " - " << secondPairEdgeOne.GetSecondPoint() << " | " << secondPairEdgeTwo.GetFirstPoint() << " - " << secondPairEdgeTwo.GetSecondPoint() << std::endl;
												std::cout << "Minus weight - " << chooseEdgesSum - secondPairSum << std::endl;
												rightEdgesMatrix[minWay[oneE].GetFirstPoint()][minWay[oneE].GetSecondPoint()] = false;
												rightEdgesMatrix[minWay[oneE].GetSecondPoint()][minWay[oneE].GetFirstPoint()] = false;
												rightEdgesMatrix[minWay[twoE].GetFirstPoint()][minWay[twoE].GetSecondPoint()] = false;
												rightEdgesMatrix[minWay[twoE].GetSecondPoint()][minWay[twoE].GetFirstPoint()] = false;
												rightEdgesMatrix[secondPairEdgeOne.GetFirstPoint()][secondPairEdgeOne.GetSecondPoint()] = true;
												rightEdgesMatrix[secondPairEdgeOne.GetSecondPoint()][secondPairEdgeOne.GetFirstPoint()] = true;
												rightEdgesMatrix[secondPairEdgeTwo.GetFirstPoint()][secondPairEdgeTwo.GetSecondPoint()] = true;
												rightEdgesMatrix[secondPairEdgeTwo.GetSecondPoint()][secondPairEdgeTwo.GetFirstPoint()] = true;
												minWay[oneE] = secondPairEdgeOne;
												minWay[twoE] = secondPairEdgeTwo;
												minWayWeight = minWayWeight - chooseEdgesSum + secondPairSum;
												tumbler = true;
												if (true) {
													for (int i = 0; i < verticesAmount; ++i) {
														std::cout << minWay[i].GetFirstPoint() << " - " << minWay[i].GetSecondPoint() << " | ";
													}
													std::cout << minWayWeight << std::endl;
												}
											}
										}
										else if (t == minWay[twoE].GetSecondPoint()) {
											tumblerEnd = true;
											if (chooseEdgesSum > firstPairSum) {
												std::cout << "Method - 3.1" << std::endl;
												std::cout << "Choose edges | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << " | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << std::endl;
												std::cout << "Change edges | " << firstPairEdgeOne.GetFirstPoint() << " - " << firstPairEdgeOne.GetSecondPoint() << " | " << firstPairEdgeTwo.GetFirstPoint() << " - " << firstPairEdgeTwo.GetSecondPoint() << std::endl;
												std::cout << "Minus weight - " << chooseEdgesSum - firstPairSum << std::endl;
												rightEdgesMatrix[minWay[oneE].GetFirstPoint()][minWay[oneE].GetSecondPoint()] = false;
												rightEdgesMatrix[minWay[oneE].GetSecondPoint()][minWay[oneE].GetFirstPoint()] = false;
												rightEdgesMatrix[minWay[twoE].GetFirstPoint()][minWay[twoE].GetSecondPoint()] = false;
												rightEdgesMatrix[minWay[twoE].GetSecondPoint()][minWay[twoE].GetFirstPoint()] = false;
												rightEdgesMatrix[firstPairEdgeOne.GetFirstPoint()][firstPairEdgeOne.GetSecondPoint()] = true;
												rightEdgesMatrix[firstPairEdgeOne.GetSecondPoint()][firstPairEdgeOne.GetFirstPoint()] = true;
												rightEdgesMatrix[firstPairEdgeTwo.GetFirstPoint()][firstPairEdgeTwo.GetSecondPoint()] = true;
												rightEdgesMatrix[firstPairEdgeTwo.GetSecondPoint()][firstPairEdgeTwo.GetFirstPoint()] = true;
												minWay[oneE] = firstPairEdgeOne;
												minWay[twoE] = firstPairEdgeTwo;
												minWayWeight = minWayWeight - chooseEdgesSum + firstPairSum;
												tumbler = true;
												if (true) {
													for (int i = 0; i < verticesAmount; ++i) {
														std::cout << minWay[i].GetFirstPoint() << " - " << minWay[i].GetSecondPoint() << " | ";
													}
													std::cout << minWayWeight << std::endl;
												}
											}
										}
										break;
									}
								}
							}
							if (tumblerEnd) { break; }
						}
					}

				}
				if (!rightEdgesMatrix[minWay[oneE].GetFirstPoint()][twoE] && !rightEdgesMatrix[minWay[oneE].GetSecondPoint()][twoE]) {
					// найдём правильные вершины из вершины twoE
					int oneV = -1;
					int twoV = -1;
					for (int i = 0; i < verticesAmount; ++i) {
						if (rightEdgesMatrix[twoE][i]) {
							if (oneV == -1) {
								oneV = i;
							}
							else {
								twoV = i;
							}
						}
					}
					// теперь нужно удалить новонайденые рёбра и выбраное ребро и найти номера нововыбраных рёбер
					int oneEdgeN = -1;
					int twoEdgeN = -1;
					for (int i = 0; i < verticesAmount; ++i) {
						if ((minWay[i].GetFirstPoint() == oneV && minWay[i].GetSecondPoint() == twoE) || (minWay[i].GetFirstPoint() == twoE && minWay[i].GetSecondPoint() == oneV)) {
							oneEdgeN = i;
						}
						if ((minWay[i].GetFirstPoint() == twoV && minWay[i].GetSecondPoint() == twoE) || (minWay[i].GetFirstPoint() == twoE && minWay[i].GetSecondPoint() == twoV)) {
							twoEdgeN = i;
						}
					}
					int chooseEdgesSum = minWay[oneE].GetWeight() + minWay[oneEdgeN].GetWeight() + minWay[twoEdgeN].GetWeight();
					int cheeckEdgesSum = edges[oneV][twoV].GetWeight() + edges[twoE][minWay[oneE].GetFirstPoint()].GetWeight() + edges[twoE][minWay[oneE].GetSecondPoint()].GetWeight();
					if (chooseEdgesSum > cheeckEdgesSum) {
						// то произвести замену
						std::cout << "Method - 4" << std::endl;
						std::cout << "Choose edges | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << " | " << oneV << " - " << twoE << " | " << twoV << " - " << twoE << std::endl;
						std::cout << "Change edges | " << oneV << " - " << twoV << " | " << minWay[oneE].GetFirstPoint() << " - " << twoE << " | " << minWay[oneE].GetSecondPoint() << " - " << twoE << std::endl;
						std::cout << "Minus weight - " << chooseEdgesSum - cheeckEdgesSum << std::endl;
						rightEdgesMatrix[oneV][twoE] = false;
						rightEdgesMatrix[twoE][oneV] = false;
						rightEdgesMatrix[twoV][twoE] = false;
						rightEdgesMatrix[twoE][twoV] = false;
						rightEdgesMatrix[minWay[oneE].GetFirstPoint()][minWay[oneE].GetSecondPoint()] = false;
						rightEdgesMatrix[minWay[oneE].GetSecondPoint()][minWay[oneE].GetFirstPoint()] = false;
						rightEdgesMatrix[oneV][twoV] = true;
						rightEdgesMatrix[twoV][oneV] = true;
						rightEdgesMatrix[minWay[oneE].GetFirstPoint()][twoE] = true;
						rightEdgesMatrix[twoE][minWay[oneE].GetFirstPoint()] = true;
						rightEdgesMatrix[minWay[oneE].GetSecondPoint()][twoE] = true;
						rightEdgesMatrix[twoE][minWay[oneE].GetSecondPoint()] = true;
						minWayWeight = minWayWeight - chooseEdgesSum + cheeckEdgesSum;
						minWay[oneEdgeN] = edges[minWay[oneE].GetFirstPoint()][twoE];
						minWay[twoEdgeN] = edges[minWay[oneE].GetSecondPoint()][twoE];
						minWay[oneE] = edges[oneV][twoV];
						tumbler = true;
						if (true) {
							for (int i = 0; i < verticesAmount; ++i) {
								std::cout << minWay[i].GetFirstPoint() << " - " << minWay[i].GetSecondPoint() << " | ";
							}
							std::cout << minWayWeight << std::endl;
						}
						break;
					}
				}
				/////////
			}
			if (tumbler) { break; }
		}
		if (!tumbler) { break; }
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
