#pragma once

class Edge {
public:
	Edge();
	Edge(int firstPoint, int secondPoint, int weight);
	int GetFirstPoint();
	int GetSecondPoint();
	int GetWeight();
	void SetFirstPoint(int firstPoint);
	void SetSecondPoint(int secondPoint);
	void SetWeight(int weight);

	void operator =(const Edge& edge);
	bool operator == (const Edge& edge);
	bool operator != (const Edge& edge);
private:
	int firstPoint, secondPoint;
	int weight;
};