#include <iostream>
#include <iomanip>
#include <cmath>

class Polynom {
	const double EPS = 1e-15;
	
	double *coef; // коэффициенты полинома
	int n; // степень полинома

public:
	Polynom(); // конструктро по умолчанию - полином нулевой степени с нулевым коэффициентом
	Polynom(int n); // конструктор из степени - нулевой полином
	Polynom(int n, double *coef); // конструктор с двумя параметрами (степень и массив коэффициентов)
	Polynom(const Polynom& polynom); // конструктор копирования

	Polynom& operator=(const Polynom& polynom); // оператор присваивания

	double& operator[](int power); // оператор [] доступа к коэффициенту при данной степени
	int GetN(); // получение степени

	Polynom operator+(const Polynom& polynom) const; // сумма
	Polynom operator-(const Polynom& polynom) const; // разность
	Polynom operator*(const Polynom& polynom) const; // произведение
	Polynom operator/(const Polynom& polynom) const; // деление
	Polynom operator%(const Polynom& polynom) const; // остаток

	Polynom GCD(const Polynom& polynom) const; // НОД полиномов

	friend std::ostream& operator<<(std::ostream& os, const Polynom& polynom); // вывод в поток
	friend std::istream& operator>>(std::istream& is, Polynom& polynom); // ввод из потока

	~Polynom(); // деструктор
};

// конструктро по умолчанию - полином нулевой степени с нулевым коэффициентом
Polynom::Polynom() {
	n = 0;
	coef = new double[1];
	coef[0] = 0;
}

// конструктор из степени - нулевой полином
Polynom::Polynom(int n) {
	this->n = n;
	coef = new double[n + 1];

	for (int i = 0; i <= n; i++)
		coef[i] = 0;
}

// конструктор с двумя параметрами (степень и массив коэффициентов)
Polynom::Polynom(int n, double *coef) {
	this->n = n;
	this->coef = new double[n + 1];

	for (int i = 0; i <= n; i++)
		this->coef[i] = coef[i];
}

// конструктор копирования
Polynom::Polynom(const Polynom& polynom) {
	n = polynom.n;
	coef = new double[n + 1];

	for (int i = 0; i <= n; i++)
		coef[i] = polynom.coef[i];
}

// оператор присваивания
Polynom& Polynom::operator=(const Polynom& polynom) {
	if (this == &polynom)
		return *this;

	delete[] coef;

	n = polynom.n;
	coef = new double[n + 1];

	for (int i = 0; i <= n; i++)
		coef[i] = polynom.coef[i];

	return *this;
}

// оператор [] доступа к коэффициенту при данной степени
double& Polynom::operator[](int power) {
	return coef[power];
}

// получение степени
int Polynom::GetN() {
	return n;
}

// сумма
Polynom Polynom::operator+(const Polynom& polynom) const {
	Polynom p(n > polynom.n ? n : polynom.n);

	for (int i = 0; i <= n; i++)
		p.coef[i] += coef[i];

	for (int i = 0; i <= polynom.n; i++)
		p.coef[i] += polynom.coef[i];

	while (fabs(p.coef[p.n]) < EPS && p.n > 0)
		p.n--;

	return p;
}

// разность
Polynom Polynom::operator-(const Polynom& polynom) const {
	Polynom p(n > polynom.n ? n : polynom.n);

	for (int i = 0; i <= n; i++)
		p.coef[i] += coef[i];

	for (int i = 0; i <= polynom.n; i++)
		p.coef[i] -= polynom.coef[i];

	while (fabs(p.coef[p.n]) < EPS && p.n > 0)
		p.n--;

	return p;
}

// произведение
Polynom Polynom::operator*(const Polynom& polynom) const {
	Polynom p(n + polynom.n);

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= polynom.n; j++)
			p.coef[i + j] += coef[i] * polynom.coef[j];

	while (fabs(p.coef[p.n]) < EPS && p.n > 0)
		p.n--;

	return p;
}

// деление
Polynom Polynom::operator/(const Polynom& polynom) const {
	if (n < polynom.n)
		return Polynom(); // нулевой полином 0 степени

	Polynom div(n - polynom.n);
	Polynom mod(*this);

	while (mod.n > 0 && mod.n >= polynom.n) {
		double a = mod.coef[mod.n] / polynom.coef[polynom.n];

		div.coef[mod.n - polynom.n] = a;

		Polynom tmp(mod.n);

		for (int j = 0; j <= polynom.n; j++)
			tmp.coef[mod.n - polynom.n + j] = a * polynom.coef[j];
	
		mod = mod - tmp;
	}

	return div;
}

// остаток
Polynom Polynom::operator%(const Polynom& polynom) const {
	if (n < polynom.n)
		return *this; // нулевой полином 0 степени

	Polynom div(n - polynom.n);
	Polynom mod(*this);

	while (mod.n > 0 && mod.n >= polynom.n) {
		double a = mod.coef[mod.n] / polynom.coef[polynom.n];

		div.coef[mod.n - polynom.n] = a;

		Polynom tmp(mod.n);

		for (int j = 0; j <= polynom.n; j++)
			tmp.coef[mod.n - polynom.n + j] = a * polynom.coef[j];
	
		mod = mod - tmp;
	}

	return mod;
}

// НОД полиномов
Polynom Polynom::GCD(const Polynom& polynom) const {
	Polynom a(*this);
	Polynom b(polynom);
	
	Polynom c = a % polynom;

	if (c.n == 0 && fabs(c[0]) > EPS)
		return c;
	
	while (b.n) {
		a = a % b;
		Polynom tmp = a;
		a = b;
		b = tmp;
	}

	return a;
}

// вывод в поток
std::ostream& operator<<(std::ostream& os, const Polynom& polynom) {
	os << polynom.n;

	for (int i = polynom.n; i >= 0; i--)
		os << " " << polynom.coef[i];

	return os;
}

// ввод из потока
std::istream& operator>>(std::istream& is, Polynom& polynom) {
	is >> polynom.n;

	delete[] polynom.coef;

	polynom.coef = new double[polynom.n + 1];

	for (int i = polynom.n; i >= 0; i--)
		is >> polynom.coef[i];

	return is;
}

// деструктор
Polynom::~Polynom() {
	delete[] coef;
}