#pragma once

#include <iostream>
#include <cmath>

class Complex {
	double re; // действительная часть числа
	double im; // мнимая часть числа

public:
	Complex(double re = 0.0, double im = 0.0); // конструкторы (по умолчанию, с одним и двумя параметрами)
	Complex(const Complex &c); // конструктор копирования

	Complex& operator=(const Complex &c); // оператор присваивания

	bool operator==(const Complex &c) const; // проверка на равенство двух чисел
	bool operator!=(const Complex &c) const; // проверка на неравенство двух чисел
	
	Complex operator+(const Complex &c) const; // сумма двух чисел
	Complex operator-(const Complex &c) const; // разность двух чисел
	Complex operator*(const Complex &c) const; // произведение двух чисел
	Complex operator/(const Complex &c) const; // деление двух чисел

	Complex& operator+=(const Complex &c); // короткая запись суммы
	Complex& operator-=(const Complex &c); // короткая запись разности
	Complex& operator*=(const Complex &c); // короктая запись произведения
	Complex& operator/=(const Complex &c); // короткая запись деления

	Complex operator+(double lambda) const; // прибавление скаляря
	Complex operator-(double lambda) const; // вычитание скаляря
	Complex operator*(double lambda) const; // умножение на скаляр
	Complex operator/(double lambda) const; // деление на скаляр

	Complex& operator*=(double lambda); // короткое умножение на скаляр
	Complex& operator/=(double lambda); // короткое деление на скаляр

	Complex operator-() const; // унарный минус

	double Re() const; // получение действительной части
	double Im() const; // получение мнимой части

	double Abs() const; // получение модуля числа
	double Arg() const; // получение аргумента числа
	Complex Conjunct() const; // получение сопряжённого к числу

	static Complex Exp(const Complex& c); // экспонента от числа
	static Complex Ln(const Complex& c); // логарифм от числа
	static Complex Sh(const Complex& c); // гиперболический синус
	static Complex Ch(const Complex& c); // гиперболический косинус
	static Complex Th(const Complex& c); // гиперболический тангенс
	static Complex Cth(const Complex& c); // гиперболический котангенс

	static Complex Arsh(const Complex& c); // ареасинус
	static Complex Arch(const Complex& c); // ареакосинус
	static Complex Arth(const Complex& c); // ареатангенс
	static Complex Arcth(const Complex& c); // ареакотангенс

	friend std::ostream& operator<<(std::ostream& os, const Complex &c); // вывод в поток
	friend std::istream& operator>>(std::istream& is, Complex &c); // ввод из потока
};

Complex::Complex(double re, double im) {
	this->re = re;
	this->im = im;
}

Complex::Complex(const Complex &c) {
	this->re = c.re;
	this->im = c.im;
}

Complex& Complex::operator=(const Complex &c) {
	if (this != &c) {
		re = c.re;
		im = c.im;
	}

	return *this;
}

bool Complex::operator==(const Complex &c) const {
	return re == c.re && im == c.im;
}

bool Complex::operator!=(const Complex &c) const {
	return re != c.re || im != c.im;
}

Complex Complex::operator+(const Complex &c) const {
	return Complex(re + c.re, im + c.im);
}

Complex Complex::operator-(const Complex &c) const {
	return Complex(re - c.re, im - c.im);
}

Complex Complex::operator*(const Complex &c) const {
	return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
}

Complex Complex::operator/(const Complex &c) const {
	double t = c.re * c.re + c.im * c.im;
	return Complex((re * c.re + im * c.im) / t, (-re * c.im + im * c.re) / t);
}

Complex& Complex::operator+=(const Complex &c) {
	re += c.re;
	im += c.im;

	return *this;
}

Complex& Complex::operator-=(const Complex &c) {
	re -= c.re;
	im -= c.im;

	return *this;
}

Complex& Complex::operator*=(const Complex &c) {
	double real = re * c.re - im * c.im;
	double imaginary = re * c.im + im * c.re;

	re = real;
	im = imaginary;

	return *this;
}

Complex& Complex::operator/=(const Complex &c) {
	double t = c.re * c.re + c.im * c.im;
	double real = (re * c.re + im * c.im) / t;
	double imaginary = (-re * c.im + im * c.re) / t;

	re = real;
	im = imaginary;

	return *this;
}

// прибавление скаляря
Complex Complex::operator+(double lambda) const {
	return Complex(re + lambda, im);
}

// вычитание скаляря
Complex Complex::operator-(double lambda) const {
	return Complex(re - lambda, im);
}

Complex Complex::operator*(double lambda) const {
	return Complex(re * lambda, im * lambda);
}

Complex Complex::operator/(double lambda) const {
	return Complex(re / lambda, im / lambda);
}

Complex& Complex::operator*=(double lambda) {
	re *= lambda;
	im *= lambda;

	return *this;
}

Complex& Complex::operator/=(double lambda) {
	re /= lambda;
	im /= lambda;
	
	return *this;
}

// унарный минус
Complex Complex::operator-() const {
	return Complex(-re, -im);
}

double Complex::Re() const {
	return re;
}

double Complex::Im() const {
	return im;
}

double Complex::Abs() const {
	return sqrt(re * re + im * im);
}

double Complex::Arg() const {
	return atan(im / re) + (im > 0 ? M_PI : -M_PI) * (re < 0);
}

Complex Complex::Conjunct() const {
	return Complex(re, -im);
}

// экспонента от числа
Complex Complex::Exp(const Complex& c) {
	return Complex(exp(c.re) * cos(c.im), exp(c.re) * sin(c.im));
}

// логарифм от числа
Complex Complex::Ln(const Complex& c) {
	return Complex(log(c.Abs()), c.Arg());
}

// гиперболический синус
Complex Complex::Sh(const Complex& c) {
	double re = (exp(c.re) - exp(-c.re)) / 2 * cos(c.im);
	double im = (exp(c.re) + exp(-c.re)) / 2 * sin(c.im);

	return Complex(re, im);
}

// гиперболический косинус
Complex Complex::Ch(const Complex& c) {
	double re = (exp(c.re) + exp(-c.re)) / 2 * cos(c.im);
	double im = (exp(c.re) - exp(-c.re)) / 2 * sin(c.im);

	return Complex(re, im);
}

// гиперболический тангенс
Complex Complex::Th(const Complex& c) {
	double t = exp(4 * c.re) + 2 * exp(2 * c.re) * cos(2 * c.im) + 1;
	double re = (exp(4 * c.re) - 1) / t;
	double im = (2 * exp(2 * c.re) * sin(2 * c.im)) / t;

	return Complex(re, im);
}

// гиперболический котангенс
Complex Complex::Cth(const Complex& c) {
	double t = exp(4 * c.re) - 2 * exp(2 * c.re) * cos(2 * c.im) + 1;
	double re = (exp(4 * c.re) - 1) / t;
	double im = (-2 * exp(2 * c.re) * sin(2 * c.im)) / t;

	return Complex(re, im);
}

// ареасинус
Complex Complex::Arsh(const Complex& c) {
	Complex z = c*c + 1;
	Complex sqrtC;

	sqrtC.im = sqrt((-z.re + z.Abs()) / 2) * (z.im > 0 ? 1 : -1);
	sqrtC.re = z.im / (2 * sqrtC.im);

	return Ln(c + sqrtC);
}

// ареакосинус
Complex Complex::Arch(const Complex& c) {
	Complex z = c*c - 1;
	Complex sqrtC;

	sqrtC.im = sqrt((-z.re + z.Abs()) / 2);
	sqrtC.re = z.im / (2 * sqrtC.im);

	return Ln(c + sqrtC) * (c.im > 0 ? 1 : -1);
}

// ареатангенс
Complex Complex::Arth(const Complex& c) {
	Complex z = -(c + 1) / (c - 1);

	return Complex(log(z.Abs()) / 2, z.Arg() / 2);
}

// ареакотангенс
Complex Complex::Arcth(const Complex& c) {
	Complex z = (c + 1) / (c - 1);

	return Complex(log(z.Abs()) / 2, z.Arg() / 2);
}

std::ostream& operator<<(std::ostream& os, const Complex &c) {
	if (c.re == 0 && c.im == 0)
		return os << 0;

	if (c.re != 0)
		os << c.re;

	if (c.im != 0) {
		if (c.im > 0 && c.re != 0)
			os << "+";

		if (c.im != 1 && c.im != -1)
			os << c.im;

		if (c.im == -1)
			os << "-";

		os << "i";
	}

	return os;
}

std::istream& operator>>(std::istream& is, Complex &c) {
	return is >> c.re >> c.im;
}