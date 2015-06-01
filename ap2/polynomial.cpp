
#include "polynomial.h"


template <template <typename...> class Container>
struct is_root_container : std::false_type {};

template <> struct is_root_container<std::map>    			: std::true_type {};
template <> struct is_root_container<std::vector>   		: std::true_type {};
template <> struct is_root_container<std::initializer_list> : std::true_type {};

template<class T>
double Polynomial<T>::ComputeIntegral(double firstPoint, double secondPoint)
{
	/*double result = 0;
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

	}*/

}


template<class T>
Polynomial<T> Polynomial<T>::CalculateIntegral()
{
	std::map<int, T> integral;

	std::for_each(coefficients.rbegin(), coefficients.rend(),
			[&](auto coefficient)
			{ 
					int key = (&coefficient)->first + 1;
					T value = (&coefficient)->second / ((&coefficient)->first + 1);
					integral[key] = value;
			}
		);

	return Polynomial(integral);
}

template<class T>
Polynomial<T> Polynomial<T>::CalculateDerivative()
{
	std::map<int, T> derivative;

	for(auto const &coefficient: coefficients)
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

template<class T> 
Polynomial<T>::Polynomial()
{
	static_assert(std::is_floating_point<T>::value, "Has to be floating point type");
	coefficients[0] = 0;
	RecalculateFormula();
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
	//for(auto term: degreesTermsCoefficients)
	//{
		coefficients = degreesTermsCoefficients;
		//coefficients.insert(std::pair<int, T>(term.first, term.second));
	//}
	CleanUp();
}

template<class T> 
Polynomial<T>::~Polynomial()
{
}

template<class T> 
void Polynomial<T>::ScalePolynomial(const auto scale)
{			
	for(auto &degree: coefficients)
	{
		degree.second = degree.second * scale;
	}
	CleanUp();
}

template<class T> 
void Polynomial<T>::AddRoot(const auto root)
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
	CleanUp();
}

template<class T> 
double Polynomial<T>::ValuateAtPoint(const double point)
{
	double returnValue = 0;
	for(auto const &degree: coefficients)
	{
		returnValue += pow(point, degree.first) * degree.second;
	}

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
	RecalculateFormula();
}

template<class T>
void Polynomial<T>::CleanUp()
{		
	for(auto const &degree: coefficients)
	{
		if(degree.second == 0 && coefficients.size() > 1)
		{
			coefficients.erase(degree.first);
		}
		else if(degree.first != 0 &&degree.second == 0 && coefficients.size() == 1)
		{
			coefficients.erase(degree.first);
			coefficients[0] = 0;
		}
	}

	cachedIntegral = CalculateIntegral();
	RecalculateFormula();
}

template<class T> 
void Polynomial<T>::RecalculateFormula()
{
	std::stringstream  returnValue;
	returnValue << "f(x) = ";

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

	cachedFormula = returnValue.str();
}

template<class T> 
std::string Polynomial<T>::GetFormula()
{
	return cachedFormula;
}
