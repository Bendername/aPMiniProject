#include "D1.h"

D1::D1(int ab) : AB(ab)
{
	Couter<D1>().CoutType();
}

void D1::Incrementer()
{
	a++;
}

/*void D1::Incrementer(string aString)
{
	a++;
}*/


D1::~D1()
{
}
