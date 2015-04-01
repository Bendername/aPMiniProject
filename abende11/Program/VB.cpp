#include "VB.h"


VB::VB(string firstString) : firstString(firstString)
{
	cout << "String - ";
	Couter<VB>().CoutType();
	//Nasty work around
	WorkAround();
}


VB::VB() : firstString("Default")
{
	cout << "Default - ";
	Couter<VB>().CoutType();

	//Nasty work around
	WorkAround();

}
void VB::WorkAround()
{
	for (int i = 0; i < 10; i++)
	{
		for (int l = 0; l < 10; l++)
		{
			matrix[i][l] = 0;
		}
	}
}

void VB::printMatrix()
{
	for (int i = 0; i < 10; i++)
	{
		for (int l = 0; l < 10; l++)
		{
			cout << matrix[i][l] << " ";
		}
		cout << "\n";
	}
}

string VB::getCombinedStrings()
{
	return firstString + secondString;
}
 
VB::~VB()
{
}

