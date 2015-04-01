#include "AB.h"

AB::AB(int a) : a(a)
{
	cout << "Integer - ";
	Couter<AB>().CoutType();
}

AB::AB() : a(0)
{
	cout << "Default - ";
	Couter<AB>().CoutType();
}

void AB::Decrementer()
{
	a--;
}

AB::~AB()
{
}
