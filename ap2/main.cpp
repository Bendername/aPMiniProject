#include "polynomial.cpp"
#include <map>
#include <initializer_list>

int main()
{


//Default constructor to create a trivial polynomial: 0.
Polynomial<float> pol1{};
//cout << "Printing default constructor result: " << pol1.GetFormula() << "\n";

// Constructor for specific degree term coefficients.
std::map<int, double> coefficients;
coefficients[1] = 4;
//coefficients[1] = 3;
coefficients[0] = 5;
//coefficients[105] = 5;
//coefficients[4] = 9;

//coefficients[20] = 51;
//coefficients[154] = 5;

Polynomial<double> pol2{coefficients};

std::map<int, double> coefficients1;
coefficients1[1] = 1;
//coefficients[1] = 3;
coefficients1[2] = 10;
//coefficients[105] = 5;
//coefficients[4] = 9;

//coefficients[20] = 51;
//coefficients[154] = 5;

Polynomial<double> pol8{coefficients1};
Polynomial<double> pol10 = pol2 * pol8;

cout << "Printing degree term coefficient constructor result: " << pol10.GetFormula() << "\n";
//cout << "Printing degree term coefficient constructor result: " << pol2.GetFormula() << "\n";

// A method to scale the polynomial, i.e. multiply by a scalar value.
//pol2.ScalePolynomial(10);

//pol2.AddRoot(0);
//cout << "Printing degree term coefficient constructor result: " << pol2.GetFormula() << "\n";
//cout << "Printing scale result from second polynomial: " << pol2.GetFormula() << "\n";

// A method to add a root r, i.e. multiply by a term (x-r).
//cout << "Printing the polynomial with the additional: " << pol2.GetFormula() << "\n";

// A method to add several roots at once.

//pol2.AddMultipleRoots({1,0});
//cout << "Printing the polynomial with the additional roots added: " << pol2.GetFormula() << "\n";

// A method to valuate the polynomial at a given point.

//cout << "Printing value for point from the graph: "  << pol2.ValuateAtPoint(1);

// A method to compute a polynomial which is a derivative of the polynomial.

/*Polynomial<double> poli = pol2.CalculateDerivative();

Polynomial<double> pol4{poli};
pol4.ScalePolynomial(4);
pol4.AddRoot(1);*/
//Polynomial<double> pol5 = pol2 * pol4;

//cout << poli.GetFormula() << "\n";
//cout << pol4.GetFormula() << "\n";
//cout << pol5.GetFormula() << "\n";
//cout << poli.GetFormula()<<" Printing degree term coefficient constructor result: " << pol5.GetFormula()  << "\n";

// A method to compute an integral for given interval bounds.


// A plus operator to return a polynomial equal to a sum of two polynomials.


// A star operator to return a polynomial equal to a product of two polynomials.


    return 0;
}
