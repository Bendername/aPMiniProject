#include "D4.h"

//This constructor works, but gives some strange behaviour
//D3 is never used
D4::D4(int d1, int d2, string d3) : D1(d1), D2(d2), D3(d3 + "ThroughD4"), VB(d3)
{
	cout << "Input - ";
	Couter<D4>().CoutType();
}


// D3 doesn't do anything here because it's only purpose was to initalize  
// VB, but D4 implicit uses initialize through VB's newly created Default constuctor
D4::D4() : D3("throughD4"), D2(0), D1(0)
{
	cout << "Default - ";
	Couter<D4>().CoutType();
}


//Doesn't work if there is no default constructor for VB
/*
D4::D4(int d1, int d2, string d3) : D3(d3 + "ThroughD4"), D1(d1), D2(d2)
{
	Couter<D4>().CoutType();
}*/

void D4::Incrementer()
{

	//++ ++ ++ ++a;  //this is ambigious because it can come from both D1's AB or D2' AB
	++D1::a;
	++ ++D2::a;
}

void D4::CoutValuesForA()
{ 
	cout << "Value from D1's AB a: " << D1::a << " & Value from D2's AB a: " << D2::a << "\n";
}

void D4::ModifyRowAndColumn(int row, int column)
{
	modifyRow(row);
	modifyColumn(column);
}
void D4::ModifyPoint(int row, int column)
{
	matrix[row - 1][column - 1] += 1;
}

//If defined explicit the functions from the derivitive can be call with ease
string D4::getCombinedStrings()
{
	return "\nVB String: " + VB::getCombinedStrings()
		+ "\nD2 String: " + D2::getCombinedStrings() 
		+ "\nD3 String: " + D3::getCombinedStrings();
}

void D4::Decrementer()
{
	++d4interger;
}

D4::~D4()
{
}
