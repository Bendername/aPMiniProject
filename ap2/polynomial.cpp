
#include "polynomial.h"

//Struct for pImpl
//Used to satisfy requirement 7
template<typename T>
struct Polynomial<T>::Impl
{
public:
	mutable std::map<int, T> coefficients;
	std::string cachedFormula;
	mutable std::map<int, T> cachedIntegral;
};

/* Constructors */
//Default
template<typename T> 
Polynomial<T>::Polynomial():_impl(std::make_unique<Impl>())
{
	//Requirement 8 in order for the function to comply with requirement 2
	static_assert(std::is_floating_point<T>::value, "Has to be floating point type");
	 _impl->coefficients[0] = 0;
}

//Creation from a map
template<typename T> 
Polynomial<T>::Polynomial(std::map<int, T> degreesTermsCoefficients):_impl(std::make_unique<Impl>())
{
	static_assert(std::is_floating_point<T>::value, "Has to be floating point type");
	
	if(degreesTermsCoefficients.empty())
	{
		_impl->coefficients[0] = 0;
		return;
	}
	 _impl->coefficients = degreesTermsCoefficients;

	CleanUp();
}

//Copy constructor
template<typename T>
Polynomial<T>::Polynomial(const Polynomial &input) : _impl(std::make_unique<Impl>(*input._impl))
{
}

//Move Semantics


//Requirement 6
template<typename T> 
std::map<int, T> Polynomial<T>::GetCachedIntegral() const
{
	std::lock_guard<std::mutex> lock(integralLock);

	//Check if the cached integral data is valid otherwise recalculate new data
	if(cachedIntegralIsValid)
	{
		return _impl->cachedIntegral;
	}
	else
	{
		std::map<int, T> integral;

		std::for_each(_impl->coefficients.rbegin(), _impl->coefficients.rend(),
			[&](auto coefficient)
			{ 
					int key = (&coefficient)->first + 1;
					T value = (&coefficient)->second / ((&coefficient)->first + 1);
					integral[key] = value;
			}
		);
		_impl->cachedIntegral = integral;	
		cachedIntegralIsValid = true;
		return _impl->cachedIntegral;
	}

}

//Implementation of requirement: 1.h
template<typename T>
T Polynomial<T>::ComputeIntegral(T firstPoint, T secondPoint)
{
	std::atomic<T> result{0};
	std::map<int, T> storedIntegral = GetCachedIntegral();

	std::thread first ([&result, &storedIntegral, &firstPoint]()
	{
		for(auto const &degree: storedIntegral)
		{
			T valuate = std::pow(firstPoint, degree.first) * degree.second;
			result =result - valuate;;
		}
	});

	std::thread second ([&result, &storedIntegral, &secondPoint]()
	{
		for(auto const &degree: storedIntegral)
		{
			T valuate = std::pow(secondPoint, degree.first) * degree.second;
			result =result + valuate;;
		}
	});

	first.join();
	second.join();

	return result;

}

//Implementation of requirement: 1.g
template<typename T>
Polynomial<T> Polynomial<T>::CalculateDerivative()
{
	std::map<int, T> derivative;

	//Use of auto and const.
	//Requirement: 4 & 5
	for(auto const &coefficient: _impl->coefficients)
	{
		if(coefficient.first > 0)
		{
			int key = coefficient.first - 1;
			T value = coefficient.first * coefficient.second;
			derivative[key] = value;
		}
	}
	
	return Polynomial(derivative);
}

//Implementation of requirement 1.c
template<typename T> 
void Polynomial<T>::ScalePolynomial(const auto scale)
{			
	for(auto &degree: _impl->coefficients)
	{
		degree.second = degree.second * scale;
	}
	CleanUp();
}

//Implementation of requirement: 1.d
template<typename T> 
void Polynomial<T>::AddRoot(double root)
{
	//Use of the Distributivity law to add a root to the polynomial
	for(auto ite = _impl->coefficients.rbegin(); ite != _impl->coefficients.rend(); ite++)
	{
		int key = ite->first;
		T value = ite->second;

		if(_impl->coefficients.count(key+1) > 0)
		{
			_impl->coefficients[key+1] = _impl->coefficients[key+1] + value;
		}
		else
		{
			_impl->coefficients[key+1] =  value;
			ite++;
		}
		
		_impl->coefficients[key] = value * (-root);
	}
	CleanUp();
}

//Implementation of requirement: 1.e
template<typename T> 
void Polynomial<T>::AddMultipleRoots(std::initializer_list<T> roots)
{
	for(auto const &root: roots)
	{
		AddRoot(root);
	}
}

//Implementation of requirement: 1.f
template<typename T> 
T Polynomial<T>::ValuateAtPoint(const T point)
{
	std::vector<std::thread *> threadContainer;
	std::atomic<T> returnValue{0};

	for(auto const &degree: _impl->coefficients)
	{
		//Cache threads to they can be joined later
		//Requirement 9: use of lambda to create an asynchronus compuation for the value of a point
		threadContainer.push_back(new std::thread([&returnValue, &degree, &point]()
			{
				double valuate = std::pow(point, degree.first) * degree.second;
				returnValue = returnValue + valuate;
			}));
	}

	for(auto &aThread : threadContainer)
	{
		aThread->join();
		delete aThread;
	}

	return returnValue;
}

//Used to print the result
template<typename T> 
std::string Polynomial<T>::GetFormula() const
{
	std::lock_guard<std::mutex> lock(formulaLock);

	if(cachedFormulaIsValid)
	{
		return _impl->cachedFormula;
	}
	else
	{
		std::stringstream  returnValue;
		returnValue << "f(x) = ";
		for(auto ite = _impl->coefficients.begin(); 
			ite != _impl->coefficients.end(); 
			ite++)
		{
			if(ite->first == 0)
			{
				returnValue << ite->second;
			}
			else
			{
				returnValue << ite->second << "x^" << ite->first;
			}

			if(++ite != _impl->coefficients.end())
			{
				returnValue << " + ";
			}
			ite--;
		}

		_impl->cachedFormula = returnValue.str();
		cachedFormulaIsValid = true;
		return _impl->cachedFormula;
	}
}

/* Operator */

template<typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial& rhs)
{
	*_impl = *rhs._impl;
	return *this;
}


//Implementaion of requirement: 1.i
template<typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial& right)
{
	//Simply adds the two polynomial together
	std::map<int, T> newPolynomiel = this->_impl->coefficients;

	for(auto const &degree : right._impl->coefficients)
	{
		if(newPolynomiel.count(degree.first) > 0)
		{
			newPolynomiel[degree.first] += degree.second;
		}	
		else
		{
			newPolynomiel.insert(std::pair<int, T>(degree.first, degree.second));
		}
	}
	return Polynomial<T>(newPolynomiel);
}

//Implementaion of requirement: 1.j
template<typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial& right)
{
	std::vector<std::future<std::map<int, T>>> productResults;

	//Requirement 10
	//productResult = f(x)*g(x)
	//Takes each degree concurrently from the leftmost polynomial (f(x)) 
	//	and multiply with each degree from the rightmost polynomial(g(X))
	for(auto degree : this->_impl->coefficients)
	{
    	productResults.push_back(std::async(std::launch::async, [&right](int power, T coefficient)
    		{	
    			std::map<int, T> productResult;

				std::for_each(right._impl->coefficients.rbegin(), right._impl->coefficients.rend(),
				[&coefficient, &productResult, &power](auto const & right_coefficient)
				{ 
					int key = right_coefficient.first + power;
					T value = right_coefficient.second * coefficient;
					if(productResult.count(key) > 0)
					{
						productResult[key] += value;
					}
					else
					{
						productResult[key] = value;
					}
				});

    			return productResult; 
    		}, 
    		degree.first, degree.second
    		));
	}
	std::mutex result_mutex;
	std::map<int, T> fullResult{};

	//These results from the above standing calculations are then added together to get the final result.
	std::for_each(productResults.begin(), productResults.end(),[&fullResult, &result_mutex](auto &asyncResult)
	{
		auto result = asyncResult.get();
		std::lock_guard<std::mutex> lock(result_mutex);
		for(auto const & pair : result)
		{
				if(fullResult.count(pair.first) > 0)
				{
					fullResult[pair.first] += pair.second;
				}
				else
				{
					fullResult[pair.first] += pair.second;
				}
		}
	});

	return Polynomial<T>(fullResult);
}


/* Helper Functions */

//CleanUp -> should be called everytime the polynomial is changed
//Removed "dead" degrees & sets cached data as invalid
template<typename T>
void Polynomial<T>::CleanUp()
{		
	for(auto ite = _impl->coefficients.begin(); 
		ite != _impl->coefficients.end(); 
		ite++)
	{
		if(ite->second == 0 && _impl->coefficients.size() > 1)
		{
			_impl->coefficients.erase(ite++);
		}
		else if(ite->first != 0 &&ite->second == 0 && _impl->coefficients.size() == 1)
		{
			_impl->coefficients.clear();
			_impl->coefficients[0] = 0;
		}
	}

	cachedIntegralIsValid = false;
	cachedFormulaIsValid = false;
}
