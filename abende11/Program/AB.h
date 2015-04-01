#pragma once
#

#include "Couter.h"

using namespace std;

//This will be an abstract base class 
class AB 
{
public:

	int a;

	AB(int);
	AB();
	virtual ~AB();

//	virtual void Incrementer();
	virtual void Incrementer() = 0;

	virtual void Decrementer();
};

