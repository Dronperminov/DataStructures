#pragma once

#include <iostream>

// Стек
template <typename T>
class Stack {
	struct Node {
		T value; // значение элемента
		Node *next; // указатель на следующий элемент
	};

	Node *top; // указатель на начало стека

public:
	Stack(); // конструктор по умолчанию
	Stack(const Stack& stack); // конструктор копирования
	
	Stack& operator=(const Stack& stack); // оператор присваивания

	void Push(const T& value); // добавление элемента в стек
	T Pop(); // получение и удаление элемента из стека
	
	T& Top(); // получение элемента на вершине стека
	const T& Top() const; // получение элемента на вершине стека

	bool IsEmpty() const; // проверка на пустоту
	int GetSize() const; // получение размера стека

	~Stack(); // деструктор
};

template <typename T>
Stack<T>::Stack() {
	top = nullptr; // указатель на начало пуст
}

// конструктор копирования
template <typename T>
Stack<T>::Stack(const Stack& stack) {
	top = nullptr;

	Node *prev = nullptr; // предыдущий элемент
	
	// проходимся по всем элементам стека
	for (Node *orig = stack.top; orig != nullptr; orig = orig->next) {
		Node *node = new Node; // выделяем память под новый элемент

		node->value = orig->value; // копируем значение
		node->next = nullptr; // впереди потенциально нет элементов

		if (prev == nullptr) {
			top = node; // задаём указатель вершины стека
		}
		else {
			prev->next = node; // пробрасываем связь элементов
		}

		prev = node; // обновляем значение предыдущего элемента
	}
}

// оператор присваивания
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& stack) {
	if (this == &stack)
		return *this;

	// очищаем память от текущих элементов
	while (top) {
		Node *node = top;
		top = top->next;
		delete node;
	}

	Node *prev = nullptr; // предыдущий элемент
	
	// проходимся по всем элементам стека
	for (Node *orig = stack.top; orig != nullptr; orig = orig->next) {
		Node *node = new Node; // выделяем память под новый элемент

		node->value = orig->value; // копируем значение
		node->next = nullptr; // впереди потенциально нет элементов

		if (prev == nullptr) {
			top = node; // задаём указатель вершины стека
		}
		else {
			prev->next = node; // пробрасываем связь элементов
		}

		prev = node; // обновляем значение предыдущего элемента
	}

	return *this;
}

// добавление элемента в стек
template <typename T>
void Stack<T>::Push(const T& value) {
	Node *node = new Node; // выделяем память под новый элемент

	node->value = value; // сохраняем значение
	node->next = top; // следующий элемент - текущий первый

	top = node; // обновляем указатель на начало стека
}

// получение и удаление элемента из стека
template <typename T>
T Stack<T>::Pop() {
	// если стек пуст, то невозможно удалить элемент
	if (top == nullptr)
		throw std::string("Stack::Pop - stack is empty"); // бросаем исключение

	T value = top->value; // запоминаем значение

	Node *tmp = top; // запоминаем текущий первый элемент
	top = top->next; // смещаем указатель
	delete tmp; // удаляем элемент

	return value; // возвращаем значение
}

// получение элемента на вершине стека
template <typename T>
T& Stack<T>::Top() {
	// если стек пуст, то невозможно получить элемент
	if (top == nullptr)
		throw std::string("Stack::Top - stack is empty"); // бросаем исключение

	return top->value;
}

// получение элемента на вершине стека
template <typename T>
const T& Stack<T>::Top() const {
	// если стек пуст, то невозможно получить элемент
	if (top == nullptr)
		throw std::string("Stack::Top - stack is empty"); // бросаем исключение

	return top->value;
}

// проверка на пустоту
template <typename T>
bool Stack<T>::IsEmpty() const {
	return top == nullptr; // стек пуст, если нет элементов
}

// получение размера стека
template <typename T>
int Stack<T>::GetSize() const {
	int size = 0; // счётчик для размера
	Node *node = top;

	// пока не пройдём все элементы стека
	while (node) {
		size++; // увеличиваем размер
		node = node->next; // переходим к следующему элементу
	}

	return size; // возвращаем размер
}

// деструктор
template <typename T>
Stack<T>::~Stack() {
	// очищаем память от элементов
	while (top) {
		Node *node = top;
		top = top->next;
		delete node;
	}
}