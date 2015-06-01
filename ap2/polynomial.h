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

template<class T> 
class Polynomial
{
public:
	
	//Constructors
	Polynomial();
	Polynomial(std::map<int, T>);
	
	//Desstructor
	~Polynomial();

	//Additional functions
	std::string GetFormula();
	void ScalePolynomial(auto);
	void AddRoot(auto);
	void AddMultipleRoots(std::initializer_list<T>);
	Polynomial CalculateDerivative();
	double ValuateAtPoint(double);
	double ComputeIntegral(double, double);

	Polynomial CalculateIntegral();
private:
	std::string cachedFormula;
	Polynomial<T> cachedIntegral;
	void RecalculateFormula();

	static std::map<std::pair<string, double>, double> integralResults;
	void CleanUp();
	std::map<int, T> coefficients;
};

#endif