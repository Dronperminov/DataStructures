#pragma once

#include <iostream>
#include <iomanip>

class Matrix {
	double **values; // значения
	int n; // число строк
	int m; // число столбцов

public:
	Matrix(int n); // конструктор квадратной матрицы
	Matrix(int n, int m); // конструктор произвольной матрицы
	Matrix(const Matrix& matrix); // конструктор копирования

	Matrix& operator=(const Matrix& matrix); // оператор присваивания

	int Rows() const; // получение числа строк
	int Columns() const; // получение числа столбцов

	double& operator()(int i, int j); // получение элемента по индексам
	const double& operator()(int i, int j) const; // получение элемента по индексам

	bool operator==(const Matrix& matrix) const; // проверка матриц на равенство
	bool operator!=(const Matrix& matrix) const; // проверка матриц на неравенство

	Matrix operator+(const Matrix& matrix) const; // сложение матриц
	Matrix operator-(const Matrix& matrix) const; // разность матриц
	Matrix operator*(const Matrix& matrix) const; // умножение матриц

	Matrix operator*(double scalar) const; // умножение матрицы на скаляр
	Matrix operator/(double scalar) const; // деление матрицы на скаляр

	static Matrix Identity(int n); // получение единичной матрицы размера n

	Matrix Transpose() const; // транспонирование матрицы
	Matrix Inverse() const; // получение обратной матрицы

	void SwapRows(int i1, int i2); // перестановка строк
	void SwapColumns(int j1, int j2); // перестановка столбцов

	double Det() const; // определитель матрицы
	double Track() const; // след матрицы
	int Rank() const; // ранг матрицы

	~Matrix(); // деструктор, освобождение памяти

	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix); // вывод матрицы в поток
};

// конструктор квадратной матрицы
Matrix::Matrix(int n) {
	this->n = n; // сохраняем число строк
	this->m = n; // число столбцов совпадает с числом строк

	// выделяем память под элементы матрицы и обнуляем их
	values = new double*[n];

	for (int i = 0; i < n; i++) {
		values[i] = new double[n];

		for (int j = 0; j < n; j++)
			values[i][j] = 0;
	}
}

// конструктор произвольной матрицы
Matrix::Matrix(int n, int m) {
	this->n = n; // сохраняем число строк
	this->m = m; // сохраняем число столбцов

	// выделяем память под элементы матрицы и обнуляем их
	values = new double*[n];

	for (int i = 0; i < n; i++) {
		values[i] = new double[m];

		for (int j = 0; j < m; j++)
			values[i][j] = 0;
	}
}

// конструктор копирования
Matrix::Matrix(const Matrix& matrix) {
	n = matrix.n;
	m = matrix.m;

	// выделяем память под элементы матрицы и копируем значения из матрицы
	values = new double*[n];

	for (int i = 0; i < n; i++) {
		values[i] = new double[m];

		for (int j = 0; j < m; j++)
			values[i][j] = matrix.values[i][j];
	}
}

// оператор присваивания
Matrix& Matrix::operator=(const Matrix& matrix) {
	if (this == &matrix)
		return *this; // нет смысла в присваивании самому себе

	// освобождаем память от текущей матрицы
	for (int i = 0; i < n; i++)
		delete[] values[i];

	delete[] values; // освобождаем память из-под строк

	n = matrix.n; // сохраняем число строк
	m = matrix.m; // сохраняем число столбцов

	// выделяем память под элементы матрицы и копируем значения из матрицы
	values = new double*[n];

	for (int i = 0; i < n; i++) {
		values[i] = new double[m];

		for (int j = 0; j < m; j++)
			values[i][j] = matrix.values[i][j];
	}

	return *this;
}

// получение числа строк
int Matrix::Rows() const {
	return n;
}

// получение числа столбцов
int Matrix::Columns() const {
	return m;
}

// получение элемента по индексам
double& Matrix::operator()(int i, int j) {
	return values[i][j];
}

// получение элемента по индексам
const double& Matrix::operator()(int i, int j) const {
	return values[i][j];
}

// проверка матриц на равенство
bool Matrix::operator==(const Matrix& matrix) const {
	if (n != matrix.n || m != matrix.m)
		return false; // матрицы не равны, если не равны их размеры

	// если хотя бы один элемент не совпадает, матрицы не равны
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (values[i][j] != matrix.values[i][j])
				return false;

	return true; // если дошли, то матрицы равны
}

// проверка матриц на неравенство
bool Matrix::operator!=(const Matrix& matrix) const {
	if (n != matrix.n || m != matrix.m)
		return true; // матрицы не равны, если не равны их размеры

	// если хотя бы один элемент не совпадает, матрицы не равны
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (values[i][j] != matrix.values[i][j])
				return true;

	return false; // если дошли, то матрицы равны
}

// сложение матриц
Matrix Matrix::operator+(const Matrix& matrix) const {
	if (n != matrix.n || m != matrix.m)
		throw std::string("Matrix::operator+: invalid sizes"); // бросаем исключение, если нельзя найти сумму матриц

	Matrix result(n, m); // создаём матрицу для результата

	// считаем сумму значений элементов
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			result.values[i][j] = values[i][j] + matrix.values[i][j];

	return result; // возвращаем полученную матрицу
}

// разность матриц
Matrix Matrix::operator-(const Matrix& matrix) const {
	if (n != matrix.n || m != matrix.m)
		throw std::string("Matrix::operator-: invalid sizes"); // бросаем исключение, если нельзя найти разность матриц

	Matrix result(n, m); // создаём матрицу для результата

	// считаем разность значений элементов
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			result.values[i][j] = values[i][j] - matrix.values[i][j];

	return result; // возвращаем полученную матрицу
}

// умножение матриц
Matrix Matrix::operator*(const Matrix& matrix) const {
	if (m != matrix.n)
		throw std::string("Matrix::operator*: invalid sizes"); // бросаем исключение, если нельзя найти произведение матриц

	Matrix result(n, matrix.m); // создаём матрицу для результата

	// вычисляем произведение матриц
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < matrix.m; j++) {
			double sum = 0;

			for (int k = 0; k < m; k++)
				sum += values[i][k] * matrix.values[k][j];

			result.values[i][j] = sum;
		}
	}

	return result; // возвращаем полученную матрицу
}

// умножение матрицы на скаляр
Matrix Matrix::operator*(double scalar) const {
	Matrix result(n, m); // создаём матрицу для результата

	// умножаем каждый элемент матрицы на скаляр и записываем его в результирующую матрицу
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			result.values[i][j] = values[i][j] * scalar;

	return result; // возвращаем полученную матрицу
}

// деление матрицы на скаляр
Matrix Matrix::operator/(double scalar) const {
	Matrix result(n, m); // создаём матрицу для результата

	// делим каждый элемент матрицы на скаляр и записываем его в результирующую матрицу
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			result.values[i][j] = values[i][j] / scalar;

	return result; // возвращаем полученную матрицу
}

// получение единичной матрицы размера n
Matrix Matrix::Identity(int n) {
	Matrix I(n); // создаём квадратную матрицу размера n

	// заполняем главную диагональ единицами
	for (int i = 0; i < n; i++)
		I.values[i][i] = 1;

	return I; // возвращаем единичную матрицу
}

// транспонирование матрицы
Matrix Matrix::Transpose() const {
	Matrix result(m, n); // создаём матрицу для результата

	// транспонируем матрицу
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			result.values[i][j] = values[j][i];

	return result; // возвращаем транспонированную матрицу
}

// получение обратной матрицы
Matrix Matrix::Inverse() const {
	if (n != m)
		throw std::string("Matrix::Inverse: matrix is not square");

	Matrix A(*this);
	Matrix I = Matrix::Identity(n);

	// прямой ход метода Гаусса
	for (int i = 0; i < n; i++) {
		if (A.values[i][i] == 0) { // если на диагонали ноль
			int index = 0;

			// ищем строку, в которой в этом столбце не ноль
			while (index < n && A.values[index][i] == 0)
				index++;

			// если вся строка нулевая
			if (index == n)
				throw std::string("Matrix::Inverse: matrix is not invertible"); // обратная матрица не существует

			// меняем местами строки
			for (int j = 0; j < n; j++) {
				double tmp = A.values[i][j];
				A.values[i][j] = A.values[index][j];
				A.values[index][j] = tmp;

				tmp = I.values[i][j];
				I.values[i][j] = I.values[index][j];
				I.values[index][j] = tmp;
			}
		}

		double scale = A.values[i][i];

		for (int j = 0; j < n; j++) {
			A.values[i][j] /= scale;
			I.values[i][j] /= scale;
		}

		for (int j = i + 1; j < n; j++) {
			scale = A.values[j][i];

			for (int k = 0; k < n; k++) {
				A.values[j][k] -= A.values[i][k] * scale;
				I.values[j][k] -= I.values[i][k] * scale;
			}
		}
	}

	// обратный ход метода Гаусса
	for (int i = n - 1; i > 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			double scale = A.values[j][i];

			for (int k = n - 1; k >= 0; k--) {
				A.values[j][k] -= A.values[i][k] * scale;
				I.values[j][k] -= I.values[i][k] * scale;
			}
		}
	}

	return I; // возвращаем обратную матрицу
}

// перестановка строк
void Matrix::SwapRows(int i1, int i2) {
	for (int j = 0; j < m; j++) {
		double tmp = values[i1][j];
		values[i1][j] = values[i2][j];
		values[i2][j] = tmp;
	}
}

// перестановка столбцов
void Matrix::SwapColumns(int j1, int j2) {
	for (int i = 0; i < n; i++) {
		double tmp = values[i][j1];
		values[i][j1] = values[i][j2];
		values[i][j2] = tmp;
	}
}

// определитель матрицы
double Matrix::Det() const {
	if (n != m)
		throw std::string("Matrix::Det: matrix is not square");

	Matrix A(*this);
	double det = 1;

	for (int i = 0; i < n; i++) {
		if (A.values[i][i] == 0) {
			int index = 0;

			// ищем строку, в которой в этом столбце не ноль
			while (index < n && A.values[index][i] == 0)
				index++;

			// если вся строка нулевая
			if (index == n)
				return 0; // то определитель равен нулю	

			// меняем местами строки
			for (int j = 0; j < n; j++) {
				double tmp = A.values[i][j];
				A.values[i][j] = A.values[index][j];
				A.values[index][j] = tmp;
			}

			det = -det; // меняем знак определителя
		}

		det *= A.values[i][i];

		for (int j = i + 1; j < n; j++) {
			double scale = A.values[j][i] / A.values[i][i];

			for (int k = 0; k < n; k++)
				A.values[j][k] -= A.values[i][k] * scale;
		}
	}

	return det;
}

// след матрицы
double Matrix::Track() const {
	if (n != m)
		throw std::string("Matrix::Track: matrix is not square");

	double tr = 0;

	// считаем сумму элементов главной диагонали
	for (int i = 0; i < n; i++)
		tr += values[i][i];

	return tr; // возвращаем след
}

// ранг матрицы
int Matrix::Rank() const {
	int size = n > m ? n : m;

	Matrix A(*this); // копируем матрицу, чтобы не изменять исходную

	// приводим матрицу к треугольному виду
	for (int i = 0; i < size; i++) {
		int index = i;

		while (index < n && A.values[index][i] == 0)
			index++;

		if (index == n)
			continue;

		for (int j = 0; j < m; j++) {
			double tmp = A.values[i][j];
			A.values[i][j] = A.values[index][j];
			A.values[index][j] = tmp;
		}

		for (int j = i + 1; j < n; j++) {
			double scale = A.values[j][i] / A.values[i][i];

			for (int k = 0; k < m; k++)
				A.values[j][k] -= A.values[i][k] * scale;
		}
	}

	int rank = 0;

	// считаем количество ненулевых строк
	for (int i = 0; i < n; i++) {
		int j = 0;

		while (j < m && A.values[i][j] == 0)
			j++;

		if (j < m)
			rank++;
	}

	return rank; // возвращаем ранг
}

// деструктор, освобождение памяти
Matrix::~Matrix() {
	// освобождаем память из под столбцов
	for (int i = 0; i < n; i++)
		delete[] values[i];

	delete[] values; // освобождаем память из-под строк
}

// вывод матрицы в поток
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
	for (int i = 0; i < matrix.n; i++) {
		for (int j = 0; j < matrix.m; j++)
			os << std::setw(8) << matrix.values[i][j] << " ";

		os << std::endl;
	}

	return os;
}