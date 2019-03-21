#pragma once

#include <iostream>

class Fraqtion {
    int n; // числитель
    int m; // знаменатель

    int GCD(int a, int b) const; // получение НОД двух чисел
    void Reduce(); // сокращение дроби

public:
    Fraqtion(int n = 1, int m = 1); // конструктор из отношения двух чисел
    Fraqtion(const Fraqtion& fraqtion); // конструктор копирования

    Fraqtion& operator=(const Fraqtion& fraqtion); // оператор присваивания

    int GetN() const; // получение числителя
    int GetM() const; // получение знаменателя

    void SetN(int n); // изменение числителя
    void SetM(int m); // изменение знаменателя

    Fraqtion operator+(const Fraqtion& fraqtion) const; // оператор сложения
    Fraqtion operator-(const Fraqtion& fraqtion) const; // оператор вычитания
    Fraqtion operator*(const Fraqtion& fraqtion) const; // оператор умножения
    Fraqtion operator/(const Fraqtion& fraqtion) const; // оператор деления

    Fraqtion& operator+=(const Fraqtion& fraqtion); // оператор сложения с присваиванием
    Fraqtion& operator-=(const Fraqtion& fraqtion); // оператор вычитания с присваиванием
    Fraqtion& operator*=(const Fraqtion& fraqtion); // оператор умножения с присваиванием
    Fraqtion& operator/=(const Fraqtion& fraqtion); // оператор деления с присваиванием

    bool operator==(const Fraqtion& fraqtion) const; // проверка на равенство
    bool operator!=(const Fraqtion& fraqtion) const; // проверка на неравенство

    bool operator<(const Fraqtion& fraqtion) const; // проверка на меньше
    bool operator>(const Fraqtion& fraqtion) const; // проверка на больше
    bool operator<=(const Fraqtion& fraqtion) const; // проверка на меньше или равно
    bool operator>=(const Fraqtion& fraqtion) const; // проверка на больше или равно

    friend std::ostream& operator<<(std::ostream &os, const Fraqtion& fraqtion); // оператор вывода в поток
};

// получение НОД двух чисел
int Fraqtion::GCD(int a, int b) const {
	if (a < 0)
		a = -a; // если первое число отрицательное, то меняем у него знак

	if (b < 0)
		b = -b; // если второе число отрицательное, то меняем у него знак

	// находим НОД чисел по алгоритму Евклида
	while (b != 0) {
		a %= b;

		int tmp = a;
		a = b;
		b = tmp;
	}

	return a;
}

// сокращение дроби
void Fraqtion::Reduce() {
	int gcd = GCD(n, m); // находим НОД числителя и знаменателя
	
	// делим числитель и знаменатель на их НОД
	n /= gcd;
	m /= gcd;

	// если знаменатель стал отрицательным
	if (m < 0) {
		m *= -1; // меняем его знак
		n *= -1; // и знак числителя
	}
}

// конструктор из отношения двух чисел
Fraqtion::Fraqtion(int n, int m) {
	this->n = n;
	this->m = m;

	Reduce(); // сокращаем
}

// конструктор копирования
Fraqtion::Fraqtion(const Fraqtion& fraqtion) {
	n = fraqtion.n;
	m = fraqtion.m;
}

// оператор присваивания
Fraqtion& Fraqtion::operator=(const Fraqtion& fraqtion) {
    n = fraqtion.n;
	m = fraqtion.m;

    return *this;
}

// получение числителя
int Fraqtion::GetN() const {
	return n;
}

// получение знаменателя
int Fraqtion::GetM() const {
	return m;
}

// изменение числителя
void Fraqtion::SetN(int n) {
	this->n = n;

	Reduce();
}

// изменение знаменателя
void Fraqtion::SetM(int m) {
	this->m = m;

	Reduce();
}

// оператор сложения
Fraqtion Fraqtion::operator+(const Fraqtion& fraqtion) const {
	return Fraqtion(n * fraqtion.m + fraqtion.n * m, m * fraqtion.m); // возвращаем сумму дробей
}

// оператор вычитания
Fraqtion Fraqtion::operator-(const Fraqtion& fraqtion) const {
	return Fraqtion(n * fraqtion.m - fraqtion.n * m, m * fraqtion.m); // возвращаем разность дробей
}

// оператор умножения
Fraqtion Fraqtion::operator*(const Fraqtion& fraqtion) const {
	return Fraqtion(n * fraqtion.n, m * fraqtion.m); // возвращаем произведение дробей
}

// оператор деления
Fraqtion Fraqtion::operator/(const Fraqtion& fraqtion) const {
	return Fraqtion(n * fraqtion.m, m * fraqtion.n); // возвращаем отношение дробей
}

// оператор сложения с присваиванием
Fraqtion& Fraqtion::operator+=(const Fraqtion& fraqtion) {
	n = n * fraqtion.m + fraqtion.n * m;
	m = m * fraqtion.m;

	Reduce();

	return *this;
}

// оператор вычитания с присваиванием
Fraqtion& Fraqtion::operator-=(const Fraqtion& fraqtion) {
	n = n * fraqtion.m - fraqtion.n * m;
	m = m * fraqtion.m;

	Reduce();

	return *this;
}

// оператор умножения с присваиванием
Fraqtion& Fraqtion::operator*=(const Fraqtion& fraqtion) {
	n *= fraqtion.n;
	m *= fraqtion.m;

	Reduce();

	return *this;
}

// оператор деления с присваиванием
Fraqtion& Fraqtion::operator/=(const Fraqtion& fraqtion) {
	n *= fraqtion.m;
	m *= fraqtion.n;

	Reduce();

	return *this;
}

// проверка на равентво
bool Fraqtion::operator==(const Fraqtion& fraqtion) const {
	return n * fraqtion.m == m * fraqtion.n;
}

// проверка на не равентво
bool Fraqtion::operator!=(const Fraqtion& fraqtion) const {
	return n * fraqtion.m != m * fraqtion.n;
}

// проверка на меньше
bool Fraqtion::operator<(const Fraqtion& fraqtion) const {
	int n1 = n * fraqtion.m;
	int n2 = fraqtion.n * m;

	return n1 < n2;
}

// проверка на больше
bool Fraqtion::operator>(const Fraqtion& fraqtion) const {
	int n1 = n * fraqtion.m;
	int n2 = fraqtion.n * m;

	return n1 > n2;
}

// проверка на меньше или равно
bool Fraqtion::operator<=(const Fraqtion& fraqtion) const {
	int n1 = n * fraqtion.m;
	int n2 = fraqtion.n * m;

	return n1 <= n2;
}

// проверка на больше или равно
bool Fraqtion::operator>=(const Fraqtion& fraqtion) const {
	int n1 = n * fraqtion.m;
	int n2 = fraqtion.n * m;

	return n1 >= n2;
}

// оператор вывода в поток
std::ostream& operator<<(std::ostream &os, const Fraqtion& fraqtion) {
    // если знаменатель равен 1
	if (fraqtion.m == 1) {
		os << fraqtion.n; // выводим только числитель
	}
	else {
		os << fraqtion.n << " / " << fraqtion.m; // выводим числитель, знак дроби и знаменатель
	}

    return os;
}
