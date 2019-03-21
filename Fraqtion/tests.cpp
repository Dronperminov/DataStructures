#include <iostream>
#include <cassert>

#include "Fraqtion.hpp"

using namespace std;

int main() {
	cout << "Tests: ";

	Fraqtion f1; // 0

	assert(f1.GetN() == 1);
	assert(f1.GetM() == 1);

	Fraqtion f2(5); // 5

	assert(f2.GetN() == 5);
	assert(f2.GetM() == 1);

	Fraqtion f3(1, 3); // 1/3

	assert(f3.GetN() == 1);
	assert(f3.GetM() == 3);

	Fraqtion f4(1, -5); // -1/5

	assert(f4.GetN() == -1);
	assert(f4.GetM() == 5);

	Fraqtion f5(544, 2048); // 17/64

	assert(f5.GetN() == 17);
	assert(f5.GetM() == 64);

	Fraqtion f6 = f1 + f2; // 6

	assert(f6.GetN() == 6);
	assert(f6.GetM() == 1);

	Fraqtion f7 = f1 - f2; // -4

	assert(f7.GetN() == -4);
	assert(f7.GetM() == 1);

	Fraqtion f8 = f2 * f3; // 5/3

	assert(f8.GetN() == 5);
	assert(f8.GetM() == 3);

	Fraqtion f9 = f2 / f3; // 15

	assert(f9.GetN() == 15);
	assert(f9.GetM() == 1);

	Fraqtion f10 = f3 / f2; // 1/15

	assert(f10.GetN() == 1);
	assert(f10.GetM() == 15);

	assert(f10 < f5);
	assert(f10 <= f5);
	assert(f5 > f10);
	assert(f5 >= f10);
	
	assert(f5 != f10);
	assert(f5 == f5);

	assert(f1 * f2 == f2 * f1);

	f10.SetN(5);

	assert(f10.GetN() == 1);
	assert(f10.GetM() == 3);

	f8.SetM(5);

	assert(f8.GetN() == 1);
	assert(f8.GetM() == 1);

	cout << "OK" << endl;
}