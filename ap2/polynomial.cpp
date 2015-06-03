
#include "polynomial.h"

template<typename T>
struct Polynomial<T>::Impl
{
public:
	std::map<int, T> coefficients;
	std::string cachedFormula;
	std::map<int, T> cachedIntegral;
};

template <template <typename...> class Container>
struct is_root_container : std::false_type {};

template <> struct is_root_container<std::map>    			: std::true_type {};
template <> struct is_root_container<std::vector>   		: std::true_type {};
template <> struct is_root_container<std::initializer_list> : std::true_type {};

template<typename T> 
Polynomial<T>::Polynomial():_impl(std::make_unique<Impl>())
{
	static_assert(std::is_floating_point<T>::value, "Has to be floating point type");
	 _impl->coefficients[0] = 0;
	//RecalculateFormula();
}

template<typename T> 
Polynomial<T>::Polynomial(std::map<int, T> degreesTermsCoefficients):_impl(std::make_unique<Impl>())
{
	static_assert(std::is_floating_point<T>::value, "Has to be floating point type");
	
	if(degreesTermsCoefficients.empty())
	{
		_impl->coefficients[0] = 0;
		return;
	}
	//for(auto term: degreesTermsCoefficients)
	//{
	 _impl->coefficients = degreesTermsCoefficients;
	//	_impl->coefficients.insert(std::pair<int, T>(term.first, term.second));
	//}
	CleanUp();
}


/*template<typename T> 
Polynomial<T>::~Polynomial()
{
}*/

/*template<typename T>
double Polynomial<T>::ComputeIntegral(double firstPoint, double secondPoint)
{
	double result = 0;
	std::pair<string, double> firstPointIntegral(cachedIntegral.GetFormula(), firstPoint);
	std::pair<string, double> secondPointIntegral(cachedIntegral.GetFormula(), secondPoint);

	auto first_search_result = integralResults.find(firstPointIntegral);
	auto second_search_result = integralResults.find(secondPointIntegral);
	if(first_search_result != integralResults.end())
	{

	}
	else
	{

	}


	if(second_search_result != integralResults.end())
	{

	}
	else
	{

	}

}
*/

template<typename T>
Polynomial<T> Polynomial<T>::CalculateIntegral()
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

	return Polynomial(integral);
}

template<typename T>
Polynomial<T> Polynomial<T>::CalculateDerivative()
{
	std::map<int, T> derivative;

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


template<typename T> 
void Polynomial<T>::ScalePolynomial(const auto scale)
{			
	for(auto &degree: _impl->coefficients)
	{
		degree.second = degree.second * scale;
	}
	CleanUp();
}

template<typename T> 
void Polynomial<T>::AddRoot(double root)
{
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

template<typename T> 
double Polynomial<T>::ValuateAtPoint(const double point)
{
	double returnValue = 0;
	for(auto const &degree: _impl->coefficients)
	{
		returnValue += pow(point, degree.first) * degree.second;
	}

	return returnValue;
}

template<typename T> 
void Polynomial<T>::AddMultipleRoots(std::initializer_list<T> roots)
{
	for(auto const &root: roots)
	{
		AddRoot(root);
	}
}


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

	//cachedIntegral = CalculateIntegral();
	RecalculateFormula();
}

template<typename T> 
void Polynomial<T>::RecalculateFormula()
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
}

template<typename T> 
std::string Polynomial<T>::GetFormula()
{
	return _impl->cachedFormula;
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial &input) : _impl(std::make_unique<Impl>(*input._impl))
{
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial& rhs)
{
	*_impl = *rhs._impl;
	return *this;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial& right)
{
	std::vector<std::future<std::map<int, T>>> productResults;

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



template<typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial& right)
{
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