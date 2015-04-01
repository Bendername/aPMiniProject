#include "D2.h"


D2::D2(int abInput) : VB(defaultString),AB(abInput)
{
	Couter<D2>().CoutType();
}

void D2::Incrementer()
{
	++ ++a;
}

//Adds Integer to each in a specific row
void D2::modifyRow(int rowNumber)
{
	for (int i = 0; i < 10; i++)
	{
		matrix[rowNumber - 1][i] += 1;
	}
}

//override getCominedStrings
string D2::getCombinedStrings()
{
	return defaultString;
}


D2::~D2()
{
}
