#pragma once

#include <iostream>
#include <string>

template <typename T>
class Queue {
	struct Node {
		T value; // значение элемента
		Node *next; // указатель на следующий элемент
		Node *prev; // указатель на предыдущий элемент
	};

	Node *head; // указатель на начало очереди
	Node *tail; // указатель на конец очереди

public:
	Queue(); // конструктор по умолчанию
	Queue(const Queue& queue); // конструктор копирования

	Queue& operator=(const Queue& queue); // оператор присваивания

	void Enqueue(const T& value); // добавление элемента в очередь
	T Dequeue(); // извлечение элемента из очереди

	T& Front(); // элемент в начале очереди
	T& Back(); // элемент в конце очереди

	const T& Front() const; // элемент в начале очереди
	const T& Back() const; // элемент в конце очереди

	bool IsEmpty() const; // проверка очереди на пустоту
	int GetSize() const; // получение размера очереди

	~Queue(); // деструктор, освобождение памяти
};

// конструктор по умолчанию
template <typename T>
Queue<T>::Queue() {
	head = nullptr; // очередь пуста, поэтому указатели
	tail = nullptr; // на начало и на конец пусты
}

// конструктор копирования
template <typename T>
Queue<T>::Queue(const Queue& queue) {
	head = nullptr;
	tail = nullptr;

	if (queue.head == nullptr)
		return;
	
	for (Node *orig = queue.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;
		node->prev = tail;

		// если очередь пуста
		if (tail == nullptr) {
			head = node; // то этот элемент является началом очереди
		}
		else { // иначе вставляем в конец
			tail->next = node;
		}

		tail = node;
	}
}

// оператор присваивания
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& queue) {
	if (this == &queue)
		return *this; // нет смысла присваивать самому себе

	// очищаем очередь
	while (head) {
		Node *tmp = head; //сохраняем указатель на текущий элемент
		head = head->next; // переходим на следующий
		delete tmp; // удаляем старый элемент
	}

	tail = nullptr; // обнуляем указатель на конец очереди

	// если присваивается пустая очередь
	if (queue.head == nullptr)
		return *this; // возвращаем пустую очредь
	
	// копируем элементы очереди
	for (Node *orig = queue.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;
		node->prev = tail;

		// если очередь пуста
		if (tail == nullptr) {
			head = node; // то этот элемент является началом очереди
		}
		else { // иначе вставляем в конец
			tail->next = node;
		}

		tail = node;
	}

	return *this;
}

// добавление элемента в очередь
template <typename T>
void Queue<T>::Enqueue(const T& value) {
	Node *node = new Node; // создаём новый элемент

	node->value = value; // сохраняем значение
	node->prev = tail; // перед этим элементом последний элемент очереди
	node->next = nullptr; // за ним ничего

	// если очередь пуста
	if (tail == nullptr) {
		head = node; // то начало очереди является этим элементом
	}
	else { // иначе вставляем в конец		
		tail->next = node;
	}

	tail = node; // обновляем конец очереди
}

// извлечение элемента из очереди
template <typename T>
T Queue<T>::Dequeue() {
	// если очередь пуста
	if (head == nullptr)
		throw std::string("Queue::Dequeue - queue is empty"); // бросаем исключение

	T value = head->value; // запоминаем значение в начале очереди

	Node *tmp = head; // сохраняем значение текущего начала
	head = head->next; // переходим к следующему элементу
	delete tmp; // удаляем старое начало

	// если опустело начало очереди
	if (head == nullptr) {
		tail = nullptr; // то и конец должен быть пустым
	}
	else {
		head->prev = nullptr; // иначе обновляем указатель на предыдущий элемент
	}

	return value; // возвращаем значение
}

// элемент в начале очереди
template <typename T>
T& Queue<T>::Front() {
	// если очередь пуста, то невозможно получить элемент
	if (head == nullptr)
		throw std::string("Queue::Front - queue is empty"); // бросаем исключение

	return head->value;
}

// элемент в конце очереди
template <typename T>
T& Queue<T>::Back() {
	// если очередь пуста, то невозможно получить элемент
	if (tail == nullptr)
		throw std::string("Queue::Back - queue is empty"); // бросаем исключение

	return tail->value;
}

// элемент в начале очереди
template <typename T>
const T& Queue<T>::Front() const {
	// если очередь пуста, то невозможно получить элемент
	if (head == nullptr)
		throw std::string("Queue::Front - queue is empty"); // бросаем исключение

	return head->value;
}

// элемент в конце очереди
template <typename T>
const T& Queue<T>::Back() const {
	// если очередь пуста, то невозможно получить элемент
	if (tail == nullptr)
		throw std::string("Queue::Back - queue is empty"); // бросаем исключение

	return tail->value;
}

// проверка очереди на пустоту
template <typename T>
bool Queue<T>::IsEmpty() const {
	return head == nullptr;
}

// получение размера очереди
template <typename T>
int Queue<T>::GetSize() const {
	int size = 0;
	Node *node = head;

	// пока не пройдём все элементы очереди
	while (node) {
		size++; // увеличиваем счётчик числа элементов
		node = node->next; // переходим к следующему элементу
	}

	return size; // возвращаем размер
}

// деструктор, освобождение памяти
template <typename T>
Queue<T>::~Queue() {
	while (head) {
		Node *tmp = head; //сохраняем указатель на текущий элемент
		head = head->next; // переходим на следующий
		delete tmp; // удаляем старый элемент
	}

	tail = nullptr; // обнуляем указатель на конец очереди
}