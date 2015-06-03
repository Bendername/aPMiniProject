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
#include <thread>
#include <atomic>
#include <future>
#include <mutex>
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
	std::string GetFormula() const;
	void ScalePolynomial(auto);
	void AddRoot(double);
	void AddMultipleRoots(std::initializer_list<T>);
	Polynomial CalculateDerivative();
	double ValuateAtPoint(double);
	T ComputeIntegral(T, T);

	//Polynomial<T>& operator=(const Polynomial& rhs);

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

	std::map<int, T> GetCachedIntegral() const;
	std::map<int, T> CalculateIntegral();
	mutable std::atomic<bool> cachedIntegralIsValid{false};
	mutable std::atomic<bool> cachedFormulaIsValid{false};
	mutable std::mutex integralLock;
	mutable std::mutex formulaLock;
	void CleanUp();
};



#endif