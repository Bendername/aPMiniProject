#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm> 
#include <type_traits>
#include <initializer_list>
#include <memory>
#include <cmath>
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
	T ValuateAtPoint(T);
	T ComputeIntegral(T, T);

	//Polynomial<T>& operator=(const Polynomial& rhs);

private:

	//Used to satisfy requirement 7
	struct Impl;
	std::unique_ptr<Impl> _impl;

	std::map<int, T> GetCachedIntegral() const;
	mutable std::atomic<bool> cachedIntegralIsValid{false};
	mutable std::atomic<bool> cachedFormulaIsValid{false};
	mutable std::mutex integralLock;
	mutable std::mutex formulaLock;
	void CleanUp();
};



#endif