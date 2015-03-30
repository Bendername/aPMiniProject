#pragma once
#include "Base.h"
class SomeClass :
	public Base
{
public:
	void Increment() override;
	SomeClass();
	~SomeClass();
	//~Base() override;
};

