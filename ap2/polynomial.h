#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm> 
#include <typeinfo>
#include <type_traits>
#include <initializer_list>
#include <memory>
#include <math.h>
using namespace std;

template<typename T> 
class Polynomial
{
public:
	
	//Constructors
	Polynomial();
	Polynomial(std::map<int, T>);
	Polynomial(const Polynomial& input);
	
	//Desstructor
	~Polynomial() = default;

	//Operations
	Polynomial& operator=(const Polynomial& rhs);
	Polynomial  operator+(const Polynomial& right);
	Polynomial  operator*(const Polynomial& right);

	//Additional functions
	std::string GetFormula();
	void ScalePolynomial(auto);
	void AddRoot(double);
	void AddMultipleRoots(std::initializer_list<T>);
	Polynomial CalculateDerivative();
	double ValuateAtPoint(double);
	double ComputeIntegral(double, double);

	//Polynomial<T>& operator=(const Polynomial& rhs);

	Polynomial CalculateIntegral();
private:
	//Polynomial<T> cachedIntegral;
		struct Impl;
	std::unique_ptr<Impl> _impl;
	void RecalculateFormula();
	void CleanUp();
};



#endif