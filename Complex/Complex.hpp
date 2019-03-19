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

	Complex operator*(double lambda) const; // умножение на скаляр
	Complex operator/(double lambda) const; // деление на скаляр

	Complex& operator*=(double lambda); // короткое умножение на скаляр
	Complex& operator/=(double lambda); // короткое деление на скаляр

	double Re() const; // получение действительной части
	double Im() const; // получение мнимой части

	double Abs() const; // получение модуля числа
	double Arg() const; // получение аргумента числа
	Complex Conjunct() const; // получение сопряжённого к числу

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