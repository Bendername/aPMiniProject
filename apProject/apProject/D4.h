#pragma once
#include "D1.h"
#include "D3.h"
#include "D2.h"

class D4 :
	public D1, public D2, public D3
{
	int d4interger{ 0 };
public:
	D4(int, int, string);
	D4();

	void ModifyRowAndColumn(int row, int column);

	void ModifyPoint(int row, int column);

	//If this function is not here, the two functions from D2 and D3 would be ambiguous
	string getCombinedStrings() override;

	void Incrementer() override;

	void CoutValuesForA();

	//Hiding
	void Decrementer();

	~D4();
};

