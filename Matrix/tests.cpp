#include <iostream>
#include <cassert>
#include <cmath>

#include "Matrix.hpp"

using namespace std;

void TestSizes() {
	cout << "Tests sizes: ";

	Matrix m(1);

	assert(m.Rows() == 1);
	assert(m.Columns() == 1);
	assert(m(0, 0) == 0);

	Matrix m2(2, 4);

	assert(m2.Rows() == 2);
	assert(m2.Columns() == 4);

	assert(m2(0, 0) == 0);
	assert(m2(0, 1) == 0);
	assert(m2(1, 0) == 0);
	assert(m2(1, 1) == 0);

	cout << "OK" << endl;
}

void TestAssign() {
	cout << "Tests assign: ";

	Matrix A(2, 3);

	A(0, 0) = 1;
	A(0, 1) = 2;
	A(0, 2) = 3;

	A(1, 0) = 4;
	A(1, 1) = 5;
	A(1, 2) = 6;

	assert(A(0, 0) == 1);
	assert(A(0, 1) == 2);
	assert(A(0, 2) == 3);
	assert(A(1, 0) == 4);
	assert(A(1, 1) == 5);
	assert(A(1, 2) == 6);

	Matrix B(3, 4);

	B(1, 1) = -10;
	B(2, 2) = 100;

	assert(B.Rows() == 3);
	assert(B.Columns() == 4);
	assert(B(1, 1) == -10);
	assert(B(2, 2) == 100);

	Matrix C(B);

	B = A;

	assert(B.Rows() == 2);
	assert(B.Columns() == 3);

	assert(B(0, 0) == 1);
	assert(B(0, 1) == 2);
	assert(B(0, 2) == 3);
	assert(B(1, 0) == 4);
	assert(B(1, 1) == 5);
	assert(B(1, 2) == 6);

	assert(C.Rows() == 3);
	assert(C.Columns() == 4);
	assert(C(1, 1) == -10);
	assert(C(2, 2) == 100);

	cout << "OK" << endl;
}

void TestOperations() {
	cout << "Tests operators: ";

	Matrix A(2, 3);
	Matrix B(2, 3);
	Matrix C(3, 1);

	A(0, 0) = 1;
	A(0, 1) = 2;
	A(0, 2) = 3;
	A(1, 0) = 4;
	A(1, 1) = 5;
	A(1, 2) = 6;

	B(0, 0) = -1;
	B(0, 1) = -2;
	B(0, 2) = -3;
	B(1, 0) = 12;
	B(1, 1) = 15;
	B(1, 2) = 18;

	C(0, 0) = 5;
	C(1, 0) = -2;
	C(2, 0) = 3;

	Matrix sum = A + B;

	assert(sum.Rows() == 2);
	assert(sum.Columns() == 3);
	assert(sum(0, 0) == 0);
	assert(sum(0, 1) == 0);
	assert(sum(0, 2) == 0);
	assert(sum(1, 0) == 16);
	assert(sum(1, 1) == 20);
	assert(sum(1, 2) == 24);

	Matrix sub = A - B;

	assert(sub.Rows() == 2);
	assert(sub.Columns() == 3);
	assert(sub(0, 0) == 2);
	assert(sub(0, 1) == 4);
	assert(sub(0, 2) == 6);
	assert(sub(1, 0) == -8);
	assert(sub(1, 1) == -10);
	assert(sub(1, 2) == -12);

	Matrix mult = A * C;

	assert(mult.Rows() == 2);
	assert(mult.Columns() == 1);
	assert(mult(0, 0) == 10); 
	assert(mult(1, 0) == 28);

	Matrix A5 = A * 5;
	Matrix A_2 = A / 2;

	assert(A5.Rows() == 2);
	assert(A5.Columns() == 3);
	assert(A5(0, 0) == 5);
	assert(A5(0, 1) == 10);
	assert(A5(0, 2) == 15);
	assert(A5(1, 0) == 20);
	assert(A5(1, 1) == 25);
	assert(A5(1, 2) == 30);

	assert(A_2.Rows() == 2);
	assert(A_2.Columns() == 3);
	assert(A_2(0, 0) == 0.5);
	assert(A_2(0, 1) == 1);
	assert(A_2(0, 2) == 1.5);
	assert(A_2(1, 0) == 2);
	assert(A_2(1, 1) == 2.5);
	assert(A_2(1, 2) == 3);

	Matrix T = mult.Transpose();

	assert(T.Rows() == 1);
	assert(T.Columns() == 2);
	assert(T(0, 0) == 10);
	assert(T(0, 1) == 28);

	T = C.Transpose();

	assert(T.Rows() == 1);
	assert(T.Columns() == 3);
	assert(T(0, 0) == 5);
	assert(T(0, 1) == -2);
	assert(T(0, 2) == 3);

	A.SwapRows(0, 1);

	assert(A.Rows() == 2);
	assert(A.Columns() == 3);
	assert(A(0, 0) == 4);
	assert(A(0, 1) == 5);
	assert(A(0, 2) == 6);
	assert(A(1, 0) == 1);
	assert(A(1, 1) == 2);
	assert(A(1, 2) == 3);

	A.SwapColumns(0, 2);

	assert(A.Rows() == 2);
	assert(A.Columns() == 3);
	assert(A(0, 0) == 6);
	assert(A(0, 1) == 5);
	assert(A(0, 2) == 4);
	assert(A(1, 0) == 3);
	assert(A(1, 1) == 2);
	assert(A(1, 2) == 1);

	cout << "OK" << endl; 
}

void TestAlgebra() {
	cout << "Tests algebra: ";

	Matrix A(2, 2);

	A(0, 0) = 1;
	A(0, 1) = 2;
	A(1, 0) = 2;
	A(1, 1) = 2;

	assert(A.Det() == -2);
	assert(A.Track() == 3);
	assert(A.Rank() == 2);

	Matrix A1 = A.Inverse();

	assert(A1.Rows() == 2);
	assert(A1.Columns() == 2);
	assert(A1.Det() == -0.5);
	assert(A1(0, 0) == -1);
	assert(A1(0, 1) == 1);
	assert(A1(1, 0) == 1);
	assert(A1(1, 1) == -0.5);

	Matrix B(4, 4);

	B(0, 0) = 2;
	B(0, 1) = -1;

	B(1, 0) = -3;
	B(1, 1) = 2;

	B(2, 0) = 31;
	B(2, 1) = -19;
	B(2, 2) = 3;
	B(2, 3) = -4;

	B(3, 0) = -23;
	B(3, 1) = 14;
	B(3, 2) = -2;
	B(3, 3) = 3;

	assert(B.Track() == 10);
	assert(fabs(B.Det() - 1) < 1e-14);
	assert(B.Rank() == 4);

	Matrix B1 = B.Inverse();	

	assert(fabs(B1.Det() - 1) < 1e-14);
	assert(fabs(B1(0, 0) - 2) < 1e-14);
	assert(fabs(B1(0, 1) - 1) < 1e-14);

	assert(fabs(B1(1, 0) - 3) < 1e-14);
	assert(fabs(B1(1, 1) - 2) < 1e-14);

	assert(fabs(B1(2, 0) - 1) < 1e-14);
	assert(fabs(B1(2, 1) - 1) < 1e-14);
	assert(fabs(B1(2, 2) - 3) < 1e-14);
	assert(fabs(B1(2, 3) - 4) < 1e-14);

	assert(fabs(B1(3, 0) - 2) < 1e-14);
	assert(fabs(B1(3, 1) - -1) < 1e-14);
	assert(fabs(B1(3, 2) - 2) < 1e-14);
	assert(fabs(B1(3, 3) - 3) < 1e-14);

	cout << "OK" << endl;
}

int main() {
	TestSizes();
	TestAssign();
	TestOperations();
	TestAlgebra();
}