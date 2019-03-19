#include <iostream>
#include <cassert>

#include "Complex.hpp"

using namespace std;

int main() {
	cout << "Tests: ";
	Complex zero;

	assert(zero.Re() == 0);
	assert(zero.Im() == 0);
	assert(zero.Abs() == 0);

	Complex real(1);

	assert(real.Re() == 1);
	assert(real.Im() == 0);
	assert(real.Abs() == 1);
	assert(real.Arg() == 0);

	Complex c(3, 4); // 3+4i

	assert(c.Re() == 3);
	assert(c.Im() == 4);
	assert(c.Abs() == 5);
	
	Complex d = c;

	assert(d.Re() == 3);
	assert(d.Im() == 4);
	assert(d.Abs() == 5);

	Complex c2(8, -9); // 8-9i

	Complex sum = c + c2;

	assert(sum.Re() == 11);
	assert(sum.Im() == -5);

	Complex sub = c - c2;

	assert(sub.Re() == -5);
	assert(sub.Im() == 13);

	Complex mult = c * c2;

	assert(mult.Re() == 60);
	assert(mult.Im() == 5);

	Complex div = c / c2;

	assert(div.Re() == -12.0 / 145);
	assert(div.Im() == 59.0 / 145);

	Complex conj = c.Conjunct();

	assert(conj.Re() == c.Re());
	assert(conj.Im() == -c.Im());

	Complex cs = c * 25;

	assert(cs.Re() == c.Re() * 25);
	assert(cs.Im() == c.Im() * 25);

	Complex cd = c / 25;

	assert(cd.Re() == c.Re() / 25);
	assert(cd.Im() == c.Im() / 25);

	cout << "OK" << endl;
}