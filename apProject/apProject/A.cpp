#include "A.h"
#include <algorithm>  

void coutNumbers(int i) {  // function:
	cout << i << ' ';
}
A::A()
{
	cout << "Normal Constructor call" << endl;
}

A::A(A&& o)
{
	cout << "Move Constructor call" << endl;
}


A& A::operator=(A&& something)
{
	cout << "move assignment" << endl;
	
	return *this;
}

A::~A()
{
}

std::ostream& operator<<(std::ostream& s, const A& a)
{

	return s ;
}
