#pragma once
#include "Couter.h"
using namespace std;

//This will be the Virtual Base Class!
class VB
{
private:
	string firstString;
	string secondString = "VB2";

	void WorkAround();

public:

	//This gives compile error in VS, problem with VS 13 and C++11
	//int matrix[10][10] = { {0} };

	//Sometimes give some funny results, depending on what is in memory
	//have to make a work around in constuctor
	int matrix[10][10];

	void printMatrix();

	virtual string getCombinedStrings();

	VB(string);
	VB();

	virtual ~VB();
};

