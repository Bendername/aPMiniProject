#pragma once
#include "AB.h"

using namespace std;

class D1 : public AB
{

public:
	D1(int ab);
	
	//You can both make a normal make the normal override
	virtual void Incrementer() override;
	//Or you can do the dirty "hiding" the incrementer both make the instantiable
	//void Incrementer();
	//This did not work because the Incrementer() is not hiding the pure virtual function anymore
	//void Incrementer(string);

	~D1();

};

