#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Polynomial
{
public:
	Polynomial();
	~Polynomial();


	void test();

	std::string GetFormula();

private:
	vector<float> coefficients;
};
