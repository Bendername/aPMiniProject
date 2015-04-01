#pragma once
#include "VB.h"

class D3 :
	public virtual VB
{
private:
	string string1 = "d3";
	string string2 = "D3";
public:
	D3(string);
	
	string getCombinedStrings() override;

	void modifyColumn(int);
	~D3();
};

