/*
//Student	: Anders Bender
//Study no	: 20112715
//Username	: abende11
//Email		: abende11@student.aau.dk
*/


#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm> 
#include <type_traits>
#include <initializer_list>
#include <memory>
#include <iterator>
#include <cmath>
#include <thread>
#include <atomic>
#include <future>
#include <mutex>
using namespace std;



//Implementation of Requirement: 2
template<typename T> 
class Polynomial
{
public:

	//Constructors
	Polynomial();
	Polynomial(std::map<int, T>);
	Polynomial(const Polynomial&);   
	Polynomial(Polynomial&&);
	
	//Desstructor
	~Polynomial() = default;

	//Operations
	Polynomial& operator=(const Polynomial& rhs);
	Polynomial  operator+(const Polynomial& right);
	Polynomial  operator*(const Polynomial& right);

	//Additional functions
	std::string GetFormula() const;
	void ScalePolynomial(const T&);
	void AddRoot(const T&);
	Polynomial CalculateDerivative();
	T ValuateAtPoint(const T&);
	T ComputeIntegral(const T&, const T&);


	//Implementation to Requirement: 5 (initializer_list)
	void AddMultipleRootsInitList(std::initializer_list<T>);

	//Implementation to Requirement: 5 (Works on all sequence containers except arrays)
	template <template <typename, typename> class ContainerType,
          typename Type,
          typename Alloc>
	void AddMultipleRootsContainer(const ContainerType<Type, Alloc>& container)
	{
  		for (const auto& root : container) 
  		{
  			AddRoot(root);
  		}
  	}

	//Implementation to Requirement: 5 (Works for all sequence containers with use of iterators)
	template <typename Iterator> 
	void AddMultipleRootsIterators(typename Iterator::const_iterator start, typename Iterator::const_iterator finish)
	{
  		for (auto root = start; root != finish; root++) 


  		{
  			AddRoot(*root);
  		}
  	}

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