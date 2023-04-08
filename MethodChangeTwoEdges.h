#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <list>
#include "Edge.h"
#include "Vertice.h"

class MethodChangeTwoEdges {
public:
	MethodChangeTwoEdges(int verticesAmount);
	void BroodForceMethod();
	void FindWay();
	void PrintEdgeMatrix();
	void PrintBroodForceMethodWay();

	std::vector<int> broodForceWayMassive;
	int broodForceWayWeight;
private:
	int verticesAmount;
	std::vector<std::vector<Edge>> edges;
	void GenerateEdgeMatrix();
	void BroodForceMethodRecursion(std::vector<int> wayM, int counterM, int sumWeightM, int lastPoint, std::vector<bool> checkedPointsM);
	bool IsEquals(int oneNumber, int twoNumber);
	bool IsMore(int oneNumber, int twoNumber);
};