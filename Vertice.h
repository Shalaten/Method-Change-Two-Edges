#pragma once

class Vertice {
public:
	Vertice();
	int GetVerticeNumber();
	int GetVerticeOne();
	int GetVerticeTwo();
	void SetVerticeNumber(int verticeNumber);
	void SetVerticeOne(int verticeOne);
	void SetVerticeTwo(int verticeTwo);
private:
	int verticeNumber;
	int verticeOne;
	int verticeTwo;
};