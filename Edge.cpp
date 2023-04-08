#include "Edge.h"

Edge::Edge()
{
	this->firstPoint = 0;
	this->secondPoint = 0;
	this->weight = 0;
}

Edge::Edge(int firstPoint = 0, int secondPoint = 0, int weight = 0) {
	this->firstPoint = firstPoint;
	this->secondPoint = secondPoint;
	this->weight = weight;
}

int Edge::GetFirstPoint()
{
	return firstPoint;
}

int Edge::GetSecondPoint()
{
	return secondPoint;
}

int Edge::GetWeight()
{
	return weight;
}

void Edge::SetFirstPoint(int firstPoint)
{
	this->firstPoint = firstPoint;
}

void Edge::SetSecondPoint(int secondPoint)
{
	this->secondPoint = secondPoint;
}

void Edge::SetWeight(int weight)
{
	this->weight = weight;
}

void Edge::operator=(const Edge& edge)
{
	this->firstPoint = edge.firstPoint;
	this->secondPoint = edge.secondPoint;
	this->weight = edge.weight;
}

bool Edge::operator ==(const Edge& edge)
{
	return (this->firstPoint == edge.firstPoint && this->secondPoint == edge.secondPoint && this->weight == edge.weight)
		|| (this->firstPoint == edge.secondPoint && this->secondPoint == edge.firstPoint && this->weight == edge.weight);
}

bool Edge::operator!=(const Edge& edge)
{
	return !((this->firstPoint == edge.firstPoint && this->secondPoint == edge.secondPoint && this->weight == edge.weight)
		|| (this->firstPoint == edge.secondPoint && this->secondPoint == edge.firstPoint && this->weight == edge.weight));
}