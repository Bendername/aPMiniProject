#pragma once
#include "VB.h"
#include "AB.h"

class D2 :
	public virtual VB, public AB
{
private:
	string defaultString = "defaultString";
public:
	D2(int);

	string getCombinedStrings() override;
	void modifyRow(int);
	void Incrementer() override;

	~D2();
};

