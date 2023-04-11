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
					std::cout << "";
					if ("MEthod for swap three Edges -PART ONE-") {
						// В этом случае первое ребро оставляем, второе удаляем
						int oldWeight = 0 + minWay[twoE].GetWeight();
						int newWeight = 0;
						Edge oneDeleteEdge;
						Edge twoDeleteEdge;
						int oneDeleteEdgeV = -1;
						int twoDeleteEdgeV = -1;
						for (int i = 0; i < verticesAmount; ++i) {
							if (rightEdgesMatrix[minWay[oneE].GetFirstPoint()][i] && i != minWay[oneE].GetSecondPoint()) {
								oneDeleteEdge = edges[minWay[oneE].GetFirstPoint()][i];
								oneDeleteEdgeV = i;
								oldWeight += oneDeleteEdge.GetWeight();
							}
							if (rightEdgesMatrix[minWay[oneE].GetSecondPoint()][i] && i != minWay[oneE].GetFirstPoint()) {
								twoDeleteEdge = edges[minWay[oneE].GetSecondPoint()][i];
								twoDeleteEdgeV = i;
								oldWeight += twoDeleteEdge.GetWeight();
							}
						}
						newWeight = edges[oneDeleteEdgeV][twoDeleteEdgeV].GetWeight();
						int oneDeleteEdgeN = -1;
						int twoDeleteEdgeN = -1;
						for (int i = 0; i < verticesAmount; ++i)
						{
							if ((minWay[i].GetFirstPoint() == oneDeleteEdge.GetFirstPoint() || minWay[i].GetFirstPoint() == oneDeleteEdge.GetSecondPoint())
								&& (minWay[i].GetSecondPoint() == oneDeleteEdge.GetFirstPoint() || minWay[i].GetSecondPoint() == oneDeleteEdge.GetSecondPoint())) {
								oneDeleteEdgeN = i;
							}
							if ((minWay[i].GetFirstPoint() == twoDeleteEdge.GetFirstPoint() || minWay[i].GetFirstPoint() == twoDeleteEdge.GetSecondPoint())
								&& (minWay[i].GetSecondPoint() == twoDeleteEdge.GetFirstPoint() || minWay[i].GetSecondPoint() == twoDeleteEdge.GetSecondPoint())) {
								twoDeleteEdgeN = i;
							}
						}
						Edge newEdge = edges[oneDeleteEdgeV][twoDeleteEdgeV];
						// надо проверить какая пара рёбер имеет меньший вес
						// FirstCase
						Edge firstCaseEdgeOne = edges[minWay[oneE].GetFirstPoint()][minWay[twoE].GetFirstPoint()];
						Edge firstCaseEdgeTwo = edges[minWay[oneE].GetSecondPoint()][minWay[twoE].GetSecondPoint()];
						int firstCaseEdgeWeight = firstCaseEdgeOne.GetWeight() + firstCaseEdgeTwo.GetWeight();
						// SecondCase
						Edge secondCaseEdgeOne = edges[minWay[oneE].GetFirstPoint()][minWay[twoE].GetSecondPoint()];
						Edge secondCaseEdgeTwo = edges[minWay[oneE].GetSecondPoint()][minWay[twoE].GetFirstPoint()];
						int secondCaseEdgeWeight = secondCaseEdgeOne.GetWeight() + secondCaseEdgeTwo.GetWeight();
						if (firstCaseEdgeWeight < secondCaseEdgeWeight) {
							newWeight += firstCaseEdgeWeight;
							if (oldWeight > newWeight) {
								std::cout << "Method - 5.1.1" << std::endl;
								std::cout << "Right Edge | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << std::endl;
								std::cout << "Choose edges | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << " | " << oneDeleteEdge.GetFirstPoint() << " - " << oneDeleteEdge.GetSecondPoint() << " | " << twoDeleteEdge.GetFirstPoint() << " - " << twoDeleteEdge.GetSecondPoint() << std::endl;
								std::cout << "Change edges | " << newEdge.GetFirstPoint() << " - " << newEdge.GetSecondPoint() << " | " << firstCaseEdgeOne.GetFirstPoint() << " - " << firstCaseEdgeOne.GetSecondPoint() << " | " << firstCaseEdgeTwo.GetFirstPoint() << " - " << firstCaseEdgeTwo.GetSecondPoint() << std::endl;
								// теперь удалим рёбра в матрице правильных рёбер
								rightEdgesMatrix[minWay[twoE].GetFirstPoint()][minWay[twoE].GetSecondPoint()] = false;
								rightEdgesMatrix[minWay[twoE].GetSecondPoint()][minWay[twoE].GetFirstPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetFirstPoint()][oneDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetSecondPoint()][oneDeleteEdge.GetFirstPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetFirstPoint()][twoDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetSecondPoint()][twoDeleteEdge.GetFirstPoint()] = false;
								// добавляем правильные рёбра
								rightEdgesMatrix[oneDeleteEdgeV][twoDeleteEdgeV] = true;
								rightEdgesMatrix[twoDeleteEdgeV][oneDeleteEdgeV] = true;
								// для данного варианта рёбра
								rightEdgesMatrix[firstCaseEdgeOne.GetFirstPoint()][firstCaseEdgeOne.GetSecondPoint()] = true;
								rightEdgesMatrix[firstCaseEdgeOne.GetSecondPoint()][firstCaseEdgeOne.GetFirstPoint()] = true;
								rightEdgesMatrix[firstCaseEdgeTwo.GetFirstPoint()][firstCaseEdgeTwo.GetSecondPoint()] = true;
								rightEdgesMatrix[firstCaseEdgeTwo.GetSecondPoint()][firstCaseEdgeTwo.GetFirstPoint()] = true;
								minWay[twoE] = newEdge;
								minWay[oneDeleteEdgeN] = firstCaseEdgeOne;
								minWay[twoDeleteEdgeN] = firstCaseEdgeTwo;
								minWayWeight = minWayWeight - oldWeight + newWeight;
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
							newWeight += secondCaseEdgeWeight;
							if (oldWeight > newWeight) {
								std::cout << "Method - 5.1.2" << std::endl;
								std::cout << "Right Edge | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << std::endl;
								std::cout << "Choose edges | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << " | " << oneDeleteEdge.GetFirstPoint() << " - " << oneDeleteEdge.GetSecondPoint() << " | " << twoDeleteEdge.GetFirstPoint() << " - " << twoDeleteEdge.GetSecondPoint() << std::endl;
								std::cout << "Change edges | " << newEdge.GetFirstPoint() << " - " << newEdge.GetSecondPoint() << " | " << secondCaseEdgeOne.GetFirstPoint() << " - " << secondCaseEdgeOne.GetSecondPoint() << " | " << secondCaseEdgeTwo.GetFirstPoint() << " - " << secondCaseEdgeTwo.GetSecondPoint() << std::endl;
								// теперь удалим рёбра в матрице правильных рёбер
								// теперь удалим рёбра в матрице правильных рёбер
								rightEdgesMatrix[minWay[twoE].GetFirstPoint()][minWay[twoE].GetSecondPoint()] = false;
								rightEdgesMatrix[minWay[twoE].GetSecondPoint()][minWay[twoE].GetFirstPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetFirstPoint()][oneDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetSecondPoint()][oneDeleteEdge.GetFirstPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetFirstPoint()][twoDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetSecondPoint()][twoDeleteEdge.GetFirstPoint()] = false;
								// добавляем правильные рёбра
								rightEdgesMatrix[oneDeleteEdgeV][twoDeleteEdgeV] = true;
								rightEdgesMatrix[twoDeleteEdgeV][oneDeleteEdgeV] = true;
								// для данного варианта рёбра
								rightEdgesMatrix[secondCaseEdgeOne.GetFirstPoint()][secondCaseEdgeOne.GetSecondPoint()] = true;
								rightEdgesMatrix[secondCaseEdgeOne.GetSecondPoint()][secondCaseEdgeOne.GetFirstPoint()] = true;
								rightEdgesMatrix[secondCaseEdgeTwo.GetFirstPoint()][secondCaseEdgeTwo.GetSecondPoint()] = true;
								rightEdgesMatrix[secondCaseEdgeTwo.GetSecondPoint()][secondCaseEdgeTwo.GetFirstPoint()] = true;
								minWay[twoE] = newEdge;
								minWay[oneDeleteEdgeN] = secondCaseEdgeOne;
								minWay[twoDeleteEdgeN] = secondCaseEdgeTwo;
								minWayWeight = minWayWeight - oldWeight + newWeight;
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
					}
					if ("MEthod for swap three Edges -PART TWO-") {
						// В этом случае второе ребро оставляем, первое удаляем
						int oldWeight = 0 + minWay[oneE].GetWeight();
						int newWeight = 0;
						Edge oneDeleteEdge;
						Edge twoDeleteEdge;
						int oneDeleteEdgeV = -1;
						int twoDeleteEdgeV = -1;
						for (int i = 0; i < verticesAmount; ++i) {
							if (rightEdgesMatrix[minWay[twoE].GetFirstPoint()][i] && i != minWay[twoE].GetSecondPoint()) {
								oneDeleteEdge = edges[i][minWay[twoE].GetFirstPoint()];
								oneDeleteEdgeV = i;
								oldWeight += oneDeleteEdge.GetWeight();
							}
							if (rightEdgesMatrix[minWay[twoE].GetSecondPoint()][i] && i != minWay[twoE].GetFirstPoint()) {
								twoDeleteEdge = edges[minWay[twoE].GetSecondPoint()][i];
								twoDeleteEdgeV = i;
								oldWeight += twoDeleteEdge.GetWeight();
							}
						}
						newWeight = edges[oneDeleteEdgeV][twoDeleteEdgeV].GetWeight();
						int oneDeleteEdgeN = -1;
						int twoDeleteEdgeN = -1;
						for (int i = 0; i < verticesAmount; ++i)
						{
							if ((minWay[i].GetFirstPoint() == oneDeleteEdge.GetFirstPoint() || minWay[i].GetFirstPoint() == oneDeleteEdge.GetSecondPoint())
								&& (minWay[i].GetSecondPoint() == oneDeleteEdge.GetFirstPoint() || minWay[i].GetSecondPoint() == oneDeleteEdge.GetSecondPoint())) {
								oneDeleteEdgeN = i;
							}
							if ((minWay[i].GetFirstPoint() == twoDeleteEdge.GetFirstPoint() || minWay[i].GetFirstPoint() == twoDeleteEdge.GetSecondPoint())
								&& (minWay[i].GetSecondPoint() == twoDeleteEdge.GetFirstPoint() || minWay[i].GetSecondPoint() == twoDeleteEdge.GetSecondPoint())) {
								twoDeleteEdgeN = i;
							}
						}
						Edge newEdge = edges[oneDeleteEdgeV][twoDeleteEdgeV];
						// надо проверить какая пара рёбер имеет меньший вес
						// FirstCase
						Edge firstCaseEdgeOne = edges[minWay[twoE].GetFirstPoint()][minWay[oneE].GetFirstPoint()];
						Edge firstCaseEdgeTwo = edges[minWay[twoE].GetSecondPoint()][minWay[oneE].GetSecondPoint()];
						int firstCaseEdgeWeight = firstCaseEdgeOne.GetWeight() + firstCaseEdgeTwo.GetWeight();
						// SecondCase
						Edge secondCaseEdgeOne = edges[minWay[twoE].GetFirstPoint()][minWay[oneE].GetSecondPoint()];
						Edge secondCaseEdgeTwo = edges[minWay[twoE].GetSecondPoint()][minWay[oneE].GetFirstPoint()];
						int secondCaseEdgeWeight = secondCaseEdgeOne.GetWeight() + secondCaseEdgeTwo.GetWeight();
						if (firstCaseEdgeWeight < secondCaseEdgeWeight) {
							newWeight += firstCaseEdgeWeight;
							if (oldWeight > newWeight) {
								std::cout << "Method - 5.2.1" << std::endl;
								std::cout << "Right Edge | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << std::endl;
								std::cout << "Choose edges | " << minWay[oneE].GetFirstPoint() << " - " << minWay[oneE].GetSecondPoint() << " | " << oneDeleteEdge.GetFirstPoint() << " - " << oneDeleteEdge.GetSecondPoint() << " | " << twoDeleteEdge.GetFirstPoint() << " - " << twoDeleteEdge.GetSecondPoint() << std::endl;
								std::cout << "Change edges | " << newEdge.GetFirstPoint() << " - " << newEdge.GetSecondPoint() << " | " << firstCaseEdgeOne.GetFirstPoint() << " - " << firstCaseEdgeOne.GetSecondPoint() << " | " << firstCaseEdgeTwo.GetFirstPoint() << " - " << firstCaseEdgeTwo.GetSecondPoint() << std::endl;
								// теперь удалим рёбра в матрице правильных рёбер
								rightEdgesMatrix[minWay[oneE].GetFirstPoint()][minWay[oneE].GetSecondPoint()] = false;
								rightEdgesMatrix[minWay[oneE].GetSecondPoint()][minWay[oneE].GetFirstPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetFirstPoint()][oneDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetSecondPoint()][oneDeleteEdge.GetFirstPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetFirstPoint()][twoDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetSecondPoint()][twoDeleteEdge.GetFirstPoint()] = false;
								// добавляем правильные рёбра
								rightEdgesMatrix[oneDeleteEdgeV][twoDeleteEdgeV] = true;
								rightEdgesMatrix[twoDeleteEdgeV][oneDeleteEdgeV] = true;
								// для данного варианта рёбра
								rightEdgesMatrix[firstCaseEdgeOne.GetFirstPoint()][firstCaseEdgeOne.GetSecondPoint()] = true;
								rightEdgesMatrix[firstCaseEdgeOne.GetSecondPoint()][firstCaseEdgeOne.GetFirstPoint()] = true;
								rightEdgesMatrix[firstCaseEdgeTwo.GetFirstPoint()][firstCaseEdgeTwo.GetSecondPoint()] = true;
								rightEdgesMatrix[firstCaseEdgeTwo.GetSecondPoint()][firstCaseEdgeTwo.GetFirstPoint()] = true;
								minWay[oneE] = newEdge;
								minWay[oneDeleteEdgeN] = firstCaseEdgeOne;
								minWay[twoDeleteEdgeN] = firstCaseEdgeTwo;
								minWayWeight = minWayWeight - oldWeight + newWeight;
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
							newWeight += secondCaseEdgeWeight;
							if (oldWeight > newWeight) {
								std::cout << "Method - 5.2.2" << std::endl;
								std::cout << "Right Edge | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << std::endl;
								std::cout << "Choose edges | " << minWay[twoE].GetFirstPoint() << " - " << minWay[twoE].GetSecondPoint() << " | " << oneDeleteEdge.GetFirstPoint() << " - " << oneDeleteEdge.GetSecondPoint() << " | " << twoDeleteEdge.GetFirstPoint() << " - " << twoDeleteEdge.GetSecondPoint() << std::endl;
								std::cout << "Change edges | " << newEdge.GetFirstPoint() << " - " << newEdge.GetSecondPoint() << " | " << secondCaseEdgeOne.GetFirstPoint() << " - " << secondCaseEdgeOne.GetSecondPoint() << " | " << secondCaseEdgeTwo.GetFirstPoint() << " - " << secondCaseEdgeTwo.GetSecondPoint() << std::endl;
								// теперь удалим рёбра в матрице правильных рёбер
								rightEdgesMatrix[minWay[oneE].GetFirstPoint()][minWay[oneE].GetSecondPoint()] = false;
								rightEdgesMatrix[minWay[oneE].GetSecondPoint()][minWay[oneE].GetFirstPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetFirstPoint()][oneDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[oneDeleteEdge.GetSecondPoint()][oneDeleteEdge.GetFirstPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetFirstPoint()][twoDeleteEdge.GetSecondPoint()] = false;
								rightEdgesMatrix[twoDeleteEdge.GetSecondPoint()][twoDeleteEdge.GetFirstPoint()] = false;
								// добавляем правильные рёбра
								rightEdgesMatrix[oneDeleteEdgeV][twoDeleteEdgeV] = true;
								rightEdgesMatrix[twoDeleteEdgeV][oneDeleteEdgeV] = true;
								// для данного варианта рёбра
								rightEdgesMatrix[secondCaseEdgeOne.GetFirstPoint()][secondCaseEdgeOne.GetSecondPoint()] = true;
								rightEdgesMatrix[secondCaseEdgeOne.GetSecondPoint()][secondCaseEdgeOne.GetFirstPoint()] = true;
								rightEdgesMatrix[secondCaseEdgeTwo.GetFirstPoint()][secondCaseEdgeTwo.GetSecondPoint()] = true;
								rightEdgesMatrix[secondCaseEdgeTwo.GetSecondPoint()][secondCaseEdgeTwo.GetFirstPoint()] = true;
								minWay[oneE] = newEdge;
								minWay[oneDeleteEdgeN] = secondCaseEdgeOne;
								minWay[twoDeleteEdgeN] = secondCaseEdgeTwo;
								minWayWeight = minWayWeight - oldWeight + newWeight;
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
