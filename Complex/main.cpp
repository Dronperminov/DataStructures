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

	cout << "e^a = " << Complex::Exp(a) << endl;
	cout << "Ln(a) = " << Complex::Ln(a) << endl;
	cout << "sh(a) = " << Complex::Sh(a) << endl;
	cout << "ch(a) = " << Complex::Ch(a) << endl;
	cout << "th(a) = " << Complex::Th(a) << endl;
	cout << "cth(a) = " << Complex::Cth(a) << endl;
	cout << "arsh(a) = " << Complex::Arsh(a) << endl;
	cout << "arch(a) = " << Complex::Arch(a) << endl;
	cout << "arth(a) = " << Complex::Arth(a) << endl;
	cout << "arcth(a) = " << Complex::Arcth(a) << endl;
}