#include "D5.h"


D5::D5() : D3("From D5")
{
	Couter<D5>().CoutType();
}

//Better Constructor In my oppinion, with an explicit invoking of VB
/*
D5::D5() : D3("Used for nothing"), VB()
{
	Couter<D5>().CoutType();
}
*/

D5::~D5()
{
}
