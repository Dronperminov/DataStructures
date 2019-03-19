#include <iostream>

#include "Complex.hpp"

using namespace std;

int main() {
	Complex a, b;
	double x;

	cout << "Enter a: ";
	cin >> a;

	cout << "Enter b: ";
	cin >> b;

	cout << "Enter scalar: ";
	cin >> x;

	cout << endl;
	cout << "a: " << a << endl;
	cout << "Re(a): " << a.Re() << endl;
	cout << "Im(a): " << a.Im() << endl;
	cout << "abs(a): " << a.Abs() << endl;
	cout << "arg(a): " << a.Arg() << endl;
	cout << "conj(a): " << a.Conjunct() << endl << endl;

	cout << "b: " << b << endl;
	cout << "Re(b): " << b.Re() << endl;
	cout << "Im(b): " << b.Im() << endl;
	cout << "abs(b): " << b.Abs() << endl;
	cout << "arg(b): " << b.Arg() << endl;
	cout << "conj(b): " << b.Conjunct() << endl << endl;

	cout << "a + b = " << (a + b) << endl;
	cout << "a - b = " << (a - b) << endl;
	cout << "a * b = " << (a * b) << endl;
	cout << "a / b = " << (a / b) << endl << endl;

	cout << "a * " << x << " = " << (a * x) << endl;
	cout << "a / " << x << " = " << (a / x) << endl;
}