#pragma once

#include <iostream>

template <typename T>
class Deque {
	struct Node {
		T value; // значение элемента
		Node *next; // указатель на следующий элемент
		Node *prev; // указатель на предыдущий элемент
	};

	Node *head; // указатель на начало дека
	Node *tail; // указатель на конец дека

public:
	Deque(); // конструктор по умолчанию
	Deque(const Deque& Deque); // конструктор копирования

	Deque& operator=(const Deque& Deque); // оператор присваивания

	void EnqueueFront(const T& value); // добавление элемента в начало дека
	void EnqueueBack(const T& value); // добавление элемента в конец дека
	
	T DequeueFront(); // извлечение элемента из начала дека
	T DequeueBack(); // извлечение элемента из конца дека

	T& Front(); // элемент в начале дека
	T& Back(); // элемент в конце дека

	const T& Front() const; // элемент в начале дека
	const T& Back() const; // элемент в конце дека

	bool IsEmpty() const; // проверка дека на пустоту
	int GetSize() const; // получение размера дека

	~Deque(); // деструктор, освобождение памяти
};

// конструктор по умолчанию
template <typename T>
Deque<T>::Deque() {
	head = nullptr; // дек пуст, поэтому указатели
	tail = nullptr; // на начало и на конец пусты
}

// конструктор копирования
template <typename T>
Deque<T>::Deque(const Deque& deque) {
	head = nullptr;
	tail = nullptr;

	if (deque.head == nullptr)
		return;
	
	for (Node *orig = deque.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;
		node->prev = tail;

		// если дек пуст
		if (tail == nullptr) {
			head = node; // то этот элемент является началом дека
		}
		else { // иначе вставляем в конец
			tail->next = node;
		}

		tail = node;
	}
}

// оператор присваивания
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& deque) {
	if (this == &deque)
		return *this; // нет смысла присваивать самому себе

	// очищаем дек
	while (head) {
		Node *tmp = head; //сохраняем указатель на текущий элемент
		head = head->next; // переходим на следующий
		delete tmp; // удаляем старый элемент
	}

	tail = nullptr; // обнуляем указатель на конец дека

	// если присваивается пустой дек
	if (deque.head == nullptr)
		return *this; // возвращаем пустой дек
	
	// копируем элементы дека
	for (Node *orig = deque.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;
		node->prev = tail;

		// если дек пуст
		if (tail == nullptr) {
			head = node; // то этот элемент является началом дека
		}
		else { // иначе вставляем в конец
			tail->next = node;
		}

		tail = node;
	}

	return *this;
}

// добавление элемента в начало дека
template <typename T>
void Deque<T>::EnqueueFront(const T& value) {
	Node *node = new Node; // создаём элемент

	node->value = value; // сохраняем значение
	node->prev = nullptr;
	node->next = head;

	// если дек пуст
	if (head == nullptr) {
		tail = node; // то конец дека является этим элементом
	}
	else {		
		head->prev = node; // иначе вставляем в начало
	}

	head = node; // обновляем начало дека
}

// добавление элемента в конец дека
template <typename T>
void Deque<T>::EnqueueBack(const T& value) {
	Node *node = new Node; // создаём новый элемент

	node->value = value; // сохраняем значение
	node->prev = tail; // перед этим элементом последний элемент дека
	node->next = nullptr; // за ним ничего

	// если дек пуста
	if (tail == nullptr) {
		head = node; // то начало дека является этим элементом
	}
	else { // иначе вставляем в конец		
		tail->next = node;
	}

	tail = node; // обновляем конец дека
}

// извлечение элемента из начала дека
template <typename T>
T Deque<T>::DequeueFront() {
	// если дек пуст
	if (head == nullptr)
		throw std::string("Deque::DequeueFront - Deque is empty"); // бросаем исключение

	T value = head->value; // запоминаем значение в начале дека

	Node *tmp = head; // сохраняем значение текущего начала
	head = head->next; // переходим к следующему элементу
	delete tmp; // удаляем старое начало

	// если опустело начало дека
	if (head == nullptr) {
		tail = nullptr; // то и конец должен быть пустым
	}
	else {
		head->prev = nullptr; // иначе обновляем указатель на предыдущий элемент
	}

	return value; // возвращаем значение
}


// извлечение элемента из конца дека
template <typename T>
T Deque<T>::DequeueBack() {
	// если дек пуст
	if (head == nullptr)
		throw std::string("Deque::DequeuBack - Deque is empty"); // бросаем исключение

	T value = tail->value; // запоминаем значение в начале дека

	Node *tmp = tail; // сохраняем значение текущего конца
	tail = tail->prev; // переходим к предыдущему элементу
	delete tmp; // удаляем старый конец

	// если конец пуст
	if (tail == nullptr) {
		head = nullptr; // то и начало пусто
	}
	else {
		tail->next = nullptr; // иначе обновляем указатель на следующий элемент
	}

	return value; // возвращаем значение
}

// элемент в начале дека
template <typename T>
T& Deque<T>::Front() {
	// если дек пуст, то невозможно получить элемент
	if (head == nullptr)
		throw std::string("Deque::Front - deque is empty"); // бросаем исключение

	return head->value;
}

// элемент в конце дека
template <typename T>
T& Deque<T>::Back() {
	// если дек пуст, то невозможно получить элемент
	if (tail == nullptr)
		throw std::string("Deque::Back - deque is empty"); // бросаем исключение

	return tail->value;
}

// элемент в начале дека
template <typename T>
const T& Deque<T>::Front() const {
	// если дек пуст, то невозможно получить элемент
	if (head == nullptr)
		throw std::string("Deque::Front - deque is empty"); // бросаем исключение

	return head->value;
}

// элемент в конце дека
template <typename T>
const T& Deque<T>::Back() const {
	// если дек пуст, то невозможно получить элемент
	if (tail == nullptr)
		throw std::string("Deque::Back - deque is empty"); // бросаем исключение

	return tail->value;
}

// проверка дека на пустоту
template <typename T>
bool Deque<T>::IsEmpty() const {
	return head == nullptr;
}

// получение размера дека
template <typename T>
int Deque<T>::GetSize() const {
	int size = 0;
	Node *node = head;

	// пока не пройдём все элементы дека
	while (node) {
		size++; // увеличиваем счётчик числа элементов
		node = node->next; // переходим к следующему элементу
	}

	return size; // возвращаем размер
}

// деструктор, освобождение памяти
template <typename T>
Deque<T>::~Deque() {
	while (head) {
		Node *tmp = head; //сохраняем указатель на текущий элемент
		head = head->next; // переходим на следующий
		delete tmp; // удаляем старый элемент
	}

	tail = nullptr; // обнуляем указатель на конец дека
}