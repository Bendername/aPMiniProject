#pragma once

#include <iostream> 
#include <vector>
#include <string>
#include <memory>
#include "B.h"
using namespace std;

class A
{
public:
	int i{ 0 };
	string s{ "" };
	float f{ 0.0f };
	bool b{ false };
	char c{ ' ' };
	double d{ 0.0 };
	std::unique_ptr<B> p{ new B{} };
	std::vector<int> a{ 10 };

	A();

	A(A&& o); 

	A& operator=(A&&);

	~A();

	friend std::ostream& operator<<(std::ostream&, const A&);
};
