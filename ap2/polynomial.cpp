
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm> 
#include <typeinfo>
#include <type_traits>
#include <initializer_list>
#include <math.h>
using namespace std;


template <template <typename...> class Container>
struct is_root_container : std::false_type {};

template <> struct is_root_container<std::map>    			: std::true_type {};
template <> struct is_root_container<std::vector>   		: std::true_type {};
template <> struct is_root_container<std::initializer_list> : std::true_type {};

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

private:
	
	Polynomial CalculateIntegral();
	std::map<int, T> coefficients;
};

template<class T>
Polynomial<T> Polynomial<T>::CalculateIntegral()
{
	std::map<int, T> derivative;

	std::for_each(coefficients.begin(), coefficients.end(),
			[&](auto coefficient)
			{ 
				if((&coefficient)->first > 0)
				{
					int key = (&coefficient)->first - 1;
					T value = (&coefficient)->first * (&coefficient)->second;
					derivative.insert(std::pair<int,T>(key , value));
				}
			}
		);

	return Polynomial(derivative);
}

template<class T>
Polynomial<T> Polynomial<T>::CalculateDerivative()
{
	std::map<int, T> derivative;

	std::for_each(coefficients.begin(), coefficients.end(),
			[&](auto coefficient)
			{ 
				if((&coefficient)->first > 0)
				{
					int key = (&coefficient)->first - 1;
					T value = (&coefficient)->first * (&coefficient)->second;
					derivative.insert(std::pair<int,T>(key , value));
				}
			}
		);

	return Polynomial(derivative);
}

template<class T> 
Polynomial<T>::Polynomial()
{
	static_assert(std::is_floating_point<T>::value, "Has to be floating point type");
	coefficients[0] = 0;
}

template<class T> 
Polynomial<T>::Polynomial(std::map<int, T> degreesTermsCoefficients)
{
	static_assert(std::is_floating_point<T>::value, "Has to be floating point type");
	
	if(degreesTermsCoefficients.empty())
	{
		coefficients[0] = 0;
		return;
	}
	//Requirement
	std::for_each(degreesTermsCoefficients.begin(), degreesTermsCoefficients.end(),
			[&](auto coefficient)
			{ 
				coefficients.insert(std::pair<int, T>((&coefficient)->first, (&coefficient)->second));
			}
		);
}

template<class T> 
Polynomial<T>::~Polynomial()
{
}

template<class T> 
void Polynomial<T>::ScalePolynomial(auto scale)
{		
	std::for_each(coefficients.begin(), coefficients.end(),
			[&](auto coefficient)
			{ 
				coefficients[(&coefficient)->first] = (&coefficient)->second * scale;
			}
		);
}

template<class T> 
void Polynomial<T>::AddRoot(auto root)
{
	for(auto ite = coefficients.rbegin(); ite != coefficients.rend(); ite++)
	{
		int key = ite->first;
		T value = ite->second;

		if(coefficients.count(key+1) > 0)
		{
			coefficients[key+1] = coefficients[key+1] + value;
		}
		else
		{
			coefficients[key+1] =  value;
			ite++;
		}
		
		coefficients[key] = value * (-root);
	}
}

template<class T> 
double Polynomial<T>::ValuateAtPoint(double point)
{
	double returnValue = 0;
	std::for_each(coefficients.begin(), coefficients.end(),
		[&](auto coefficient)
		{ 

			returnValue += pow(point, (&coefficient)->first) * (&coefficient)->second;
		}
	);

	return returnValue;
}

template<class T> 
void Polynomial<T>::AddMultipleRoots(std::initializer_list<T> roots)
{
	std::for_each(roots.begin(), roots.end(),
			[&](T root)
			{ 
				AddRoot(root);
			}
		);
}

template<class T> 
std::string Polynomial<T>::GetFormula()
{
	std::stringstream  returnValue;
	returnValue << "f(x) = ";
	int i = 0;

//use of auto: requirement 4
	for(auto ite = coefficients.begin(); 
		ite != coefficients.end(); 
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

		if(++ite != coefficients.end())
		{
			returnValue << " + ";
		}
		ite--;
	}

	
	return returnValue.str();
}
