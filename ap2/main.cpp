/*
//Student	: Anders Bender
//Study no	: 20112715
//Username	: abende11
//Email		: abende11@student.aau.dk
*/

#include "polynomial.cpp"
#include <map>
#include <list>
#include <array>
#include <vector>
#include <initializer_list>
#include <forward_list>
#include <deque>

int main()
{


//1. Default constructor to create a trivial polynomial: 0.
Polynomial<float> pol1{};
cout << "1. Printing default constructor result: " << pol1.GetFormula() << "\n";

//2. Constructor for specific degree term coefficients.
std::map<int, double> coefficients;
coefficients[1] = 4;
coefficients[2] = 1;
coefficients[0] = 5;

Polynomial<double> pol2{coefficients};
cout << "2. Printing degree term coefficient constructor result: " << pol2.GetFormula() << "\n";

//3. A method to scale the polynomial, i.e. multiply by a scalar value.
Polynomial<double> pol3{coefficients};
pol3.ScalePolynomial(1.5);
cout << "3. Printing scaled polynomial: " << pol3.GetFormula() << "\n";

//4. A method to add a root r, i.e. multiply by a term (x-r).
Polynomial<double> pol4{coefficients};
pol4.AddRoot(5);
cout << "4. Printing polynomial with added root in 5: " << pol4.GetFormula() << "\n";
//Result: f(x) = -25 - 15x^1 -x^2 + x^3
// f(x) = -25 - 75 - 25 + 125 = 0


//5. A method to add several roots at once.
Polynomial<double> pol5{coefficients};
pol5.AddMultipleRootsInitList({1,0});
cout << "5. Printing the polynomial with the additional roots added from initializer_list: " << pol5.GetFormula() << "\n";
std::vector<double> v{1,0};
pol5.AddMultipleRootsContainer(v);
cout << " - Printing the polynomial with the additional roots added from vector: " << pol5.GetFormula() << "\n";
std::list<double> l{1,0};
pol5.AddMultipleRootsContainer(l);
cout << " - Printing the polynomial with the additional roots added from list: " << pol5.GetFormula() << "\n";
std::forward_list<double> fl{1,0};
pol5.AddMultipleRootsContainer(fl);
cout << " - Printing the polynomial with the additional roots added from forward_list: " << pol5.GetFormula() << "\n";
std::deque<double> d{1,0};
pol5.AddMultipleRootsContainer(d);
cout << " - Printing the polynomial with the additional roots added from deque: " << pol5.GetFormula() << "\n";
std::array<double,2> a{1,0};
pol5.AddMultipleRootsIterators<std::array<double,2>>(a.cbegin(), a.cend());
cout << " - Printing the polynomial with the additional roots added from array: " << pol5.GetFormula() << "\n";


//6. A method to valuate the polynomial at a given point.
Polynomial<double> pol6{coefficients};
cout << "6. Printing value for point from the graph: "  << pol6.ValuateAtPoint(4.7)<<"\n";
//f(x) = 5 + 4x + x^2
//Expected Result: f(x) = 45.89
//Result: 45.89

//7. A method to compute a polynomial which is a derivative of the polynomial.
std::map<int, double> coefficientsSeven;
coefficientsSeven[8] = 4;
coefficientsSeven[6] = 1;
coefficientsSeven[4] = 5;
Polynomial<double> pol7one{coefficientsSeven};
Polynomial<double> pol7two = pol7one.CalculateDerivative();

cout << "7. Printing pol7one:        "  << pol7one.GetFormula() <<"\n";
cout << " - with derivative pol7two: "  << pol7two.GetFormula() <<"\n";

//8. A method to compute an integral for given interval bounds.
Polynomial<double> pol8{coefficients};

cout << "8. Printing result for the integral between 4 and 10: "  << pol8.ComputeIntegral(4, 10) <<"\n";
//Expected Result: 510
//Result: 510

cout << " - Printing result for the integral between 4 and 10: "  << pol8.ComputeIntegral(5.1, 8.68) <<"\n";
//Expected Result: 290.338
//Result: 290.338


// A plus operator to return a polynomial equal to a sum of two polynomials.



// A star operator to return a polynomial equal to a product of two polynomials.


    return 0;
}
