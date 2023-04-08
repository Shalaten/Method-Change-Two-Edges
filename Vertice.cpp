#include "Vertice.h"

Vertice::Vertice()
{
	this->verticeNumber = 0;
	this->verticeOne = 0;
	this->verticeTwo = 0;
}

int Vertice::GetVerticeNumber()
{
	return verticeNumber;
}

int Vertice::GetVerticeOne()
{
	return verticeOne;
}

int Vertice::GetVerticeTwo()
{
	return verticeTwo;
}

void Vertice::SetVerticeNumber(int verticeNumber)
{
	this->verticeNumber = verticeNumber;
}

void Vertice::SetVerticeOne(int verticeOne)
{
	this->verticeOne = verticeOne;
}

void Vertice::SetVerticeTwo(int verticeTwo)
{
	this->verticeTwo = verticeTwo;
}
