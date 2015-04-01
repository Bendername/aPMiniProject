#include "D3.h"


D3::D3(string input) : VB(input)
{
	Couter<D3>().CoutType();
}

void D3::modifyColumn(int columnNumber)
{
	for (int i = 0; i < 10; i++)
	{
		matrix[i][columnNumber-1] += 1;
	}
}

string D3::getCombinedStrings()
{
	return string1 +" "+ string2;
}

D3::~D3()
{
}
