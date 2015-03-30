#pragma once
#include "A.h"
class B :
	public A
{
public:
	int a, b;
	B();
	B(B&& b, A&& a);
	~B();
};

