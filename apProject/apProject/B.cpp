#include "B.h"


B::B()
{
}
A::A(A&& o) : a(std::move(o.a)), aInteger(std::move(o.aInteger))
{
	cout << "Move Constructor called" << endl;

}

B::~B()
{
}
