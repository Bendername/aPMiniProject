#pragma once
#
#include <typeinfo>
#include <iostream> 
using namespace std;

/*
Created this class to easily print what constructor is whenever a constructor is called.
This is done by Creating  a Couter of the type which should be displayed in the console
and then call the function Couter().
*/

template<typename C>class Couter
{
public:
	Couter();
	
	void CoutType();

	~Couter();
};

template<typename C> Couter<C>::Couter()
{
}

template<typename C> void Couter<C>::CoutType()
{
	cout << "Constructor Called: " << typeid(*this).name() << "\n";
}

template<typename C> Couter<C>::~Couter()
{
}


