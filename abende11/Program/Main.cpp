 
#include <iostream>
#include <string>

#include "D4.h"
#include "D5.h"

using namespace std;	

int main() {

	/*Test 1: Abstract instantiate and hiding*/
	//AB ab{}; //Result: Cannot instantiate because abstract
	//D1 d1{1}; //Result: can be seen in D1.h
	//AB ab = d1; //Result: Cannot be upcasted because no instantiation of an abstract class
	

	/*Test 2: Replication and Upcasting*/
	D4 d42{};

	d42.CoutValuesForA(); //Default value = 0 and 0
	d42.Incrementer(); //incrementing d4's replicated a variables in D1's AB with 1 and D2's AB with 2

	d42.CoutValuesForA();// Values D1's a = 1 and D2's a = 2

	d42.Decrementer(); //is hiding D1/AB decrement

	d42.CoutValuesForA(); // Values D1's a = 1 and D2's a = 2

	d42.Incrementer(); //incrementing d4's replicated a variables in D1's AB with 1 and D2's AB with 2

	d42.CoutValuesForA();// Values D1's a = 2 and D2's a = 4

	//AB ab = d4; //Result: Cannot up because of ambiguity

	D1 d11 = d42; //Down casting Expected results: the D1 a value which is 2

	cout << d11.a << "\n";  // Value = 2
	d11.Incrementer(); //use D1 Incrementer function to increment

	cout << d11.a << "\n"; // Value = 3

	d11.Decrementer(); //use D1 Decrementer function to decrement

	cout << d11.a << "\n"; // Value = 2
	
	/*Test 3: Virtual Base*/
	D4 d43{ 1, 1, "d4Input" };


	d43.printMatrix();

	cout << "\n";

	d43.modifyColumn(3); //use function inherited from D3 to modify shared array
	d43.modifyRow(5); //use function inherited from D2 to modify shared array

	d43.ModifyRowAndColumn(5, 3);

	d43.ModifyPoint(10, 10);
	d43.printMatrix();

	
	//cout << "Combined string return from d4: "<< d4.getCombinedStrings() << endl;

	/*Test 4: What if there is only 1 inherit to a virtual base class*/
	D5 d5{}; //Result: Still calls the default constructor implicit
	
	getchar();
}
