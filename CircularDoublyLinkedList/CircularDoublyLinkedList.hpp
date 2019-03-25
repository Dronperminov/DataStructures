#pragma once

#include <iostream>

template <typename T>
class CircularDoublyLinkedList {
	struct Node {
		T value; // значение элемента
		Node *next; // указатель на следующий элемент
		Node *prev; // указатель на предыдущий элемент
	};

	Node *head; // указатель на начало списка
	int length; // количество элементов списка

public:
	CircularDoublyLinkedList(); // конструктор по умолчанию
	CircularDoublyLinkedList(const CircularDoublyLinkedList& list); // конструктор копирования

	int Length() const; // получение длины списка
	bool IsEmpty() const; // проверка списка на пустоту
	bool IsSorted() const; // проверка на упорядоченность (по неубыванию)

	T& GetFirst(); // получение первого элемента списка
	T& GetLast(); // получение последнего элемента списка
	T& Get(int index); // получение элемента по индексу

	void AddFront(const T& value); // добавление в начало списка
	void AddBack(const T& value); // добавление в конец списка
	void InsertAt(int index, const T& value); // добавление в произвольное место списка

	void RemoveFront(); // удаление с начала списка
	void RemoveBack(); // удаление с конца списка
	void RemoveAt(int index); // удаление по индексу
	void Remove(const T& value); // удаление элементов равных value

	void Reverse(); // разворот списка

	void Print() const; // печать списка с начала
	void PrintBackward() const; // печать списка с конца

	~CircularDoublyLinkedList(); // деструктор, освобождение памяти
};

// конструктор по умолчанию
template <typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList() {
	head = nullptr; // изначально список пуст
	length = 0;
}

// конструктор копирования
template <typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(const CircularDoublyLinkedList& list) {
	std::cout << "COPY!";
	head = nullptr; // обнулея указатель
	length = list.length; // копируем длину

	// если нечего копировать, то не копируем
	if (list.head == nullptr)
		return;

	Node *orig = list.head;

	do {
		Node *node = new Node; // выделяем память под элемент

		node->value = orig->value; // сохраняем значение

		// если список пуст
		if (head == nullptr) {
			head = node; // этот элемент и есть начало списка
			
			head->next = head; // закольцовываем на себя
			head->prev = head; // закольцовываем на себя
		}
		else { // иначе
			node->next = head;
			node->prev = head->prev;

			head->prev->next = node;		
			head->prev = node;
		}

		orig = orig->next;
	} while (orig != list.head);
}

// получение длины списка
template <typename T>
int CircularDoublyLinkedList<T>::Length() const {
	return length;
}

// проверка списка на пустоту
template <typename T>
bool CircularDoublyLinkedList<T>::IsEmpty() const {
	return head == nullptr;
}

// проверка на упорядоченность (по неубыванию)
template <typename T>
bool CircularDoublyLinkedList<T>::IsSorted() const {
	if (head == nullptr)
		return false; // пустой список не является упорядоченным

	Node *node = head;

	while (node->next != head) {
		if (node->value > node->next->value)
			return false;

		node = node->next;
	}

	return true;
}

// получение первого элемента списка
template <typename T>
T& CircularDoublyLinkedList<T>::GetFirst() {
	// если нет элементов, бросаем исключение
	if (head == nullptr)
		throw "CircularDoublyLinkedList::GetFirst(): list is empty";

	return head->value; // возвращаем первый элемент
}

// получение последнего элемента списка
template <typename T>
T& CircularDoublyLinkedList<T>::GetLast() {
	// если нет элементов, бросаем исключение
	if (head == nullptr)
		throw "CircularDoublyLinkedList::GetLast(): list is empty";

	return head->prev->value; // и возвращаем последнее значение
}

// получение элемента по индексу
template <typename T>
T& CircularDoublyLinkedList<T>::Get(int index) {
	// если индекс вне границ
	if (index < 0 || index >= length)
		throw "CircularDoublyLinkedList::Get(index): index out of bounds"; // бросаем исключение

	Node *node = head;

	// доходим до элемента с нужным индексом
	while (index) {
		index--;
		node = node->next;
	}

	return node->value; // возвращаем его значение
}

// добавление в начало списка
template <typename T>
void CircularDoublyLinkedList<T>::AddFront(const T& value) {
	Node *node = new Node; // выделяем память под элемент

	node->value = value; // сохраняем значение

	// если список пуст
	if (head == nullptr) {
		head = node; // этот элемент и есть начало списка
		
		head->next = head; // закольцовываем на себя
		head->prev = head; // закольцовываем на себя
	}
	else { // иначе
		node->next = head;
		node->prev = head->prev;

		head->prev->next = node;
		head->prev = node;

		head = node;
	}

	length++; // увеличиваем длину
}

// добавление в конец списка
template <typename T>
void CircularDoublyLinkedList<T>::AddBack(const T& value) {
	Node *node = new Node; // выделяем память под элемент

	node->value = value; // сохраняем значение

	// если список пуст
	if (head == nullptr) {
		head = node; // этот элемент и есть начало списка
		
		head->next = head; // закольцовываем на себя
		head->prev = head; // закольцовываем на себя
	}
	else { // иначе
		node->next = head;
		node->prev = head->prev;

		head->prev->next = node;
		head->prev = node;
	}

	length++; // увеличиваем длину
}

template <typename T>
void CircularDoublyLinkedList<T>::InsertAt(int index, const T& value) {
	if (index < 0 || index >= length)
		throw "CircularDoublyLinkedList::InsertAt(index): index out of bounds";

	length++; // увеличиваем длину

	Node *node = new Node; // выделяем память под элемент
	node->value = value; // сохраняем значение

	if (index == 0) {
		// если список пуст
		if (head == nullptr) {
			head = node; // этот элемент и есть начало списка
			
			head->next = head; // закольцовываем на себя
			head->prev = head; // закольцовываем на себя
		}
		else { // иначе
			node->next = head;
			node->prev = head->prev;

			head->prev->next = node;
			head->prev = node;

			head = node;
		}
	}
	else {
		// доходим до элемента с индексом index - 1
		Node *prev = head;

		while (index - 1) {
			index--;
			prev = prev->next;
		}

		node->next = prev->next;
		prev->next->prev = node;
		prev->next = node;
		node->prev = prev;
	}
}

// удаление с начала списка
template <typename T>
void CircularDoublyLinkedList<T>::RemoveFront() {
	if (head == nullptr)
		throw "CircularDoublyLinkedList::RemoveFront: list is empty";

	if (head->next == head) { // если элемент всего один
		delete head; // удаляем элемент
		head = nullptr; // обнуляем указатель
	}
	else {
		Node *tail = head->prev;
		Node *tmp = head;

		head = head->next;
		head->prev = tail;
		tail->next = head;

		delete tmp;
	}

	length--; // уменьшаем длину
}

// удаление с конца списка
template <typename T>
void CircularDoublyLinkedList<T>::RemoveBack() {
	if (head == nullptr)
		throw "CircularDoublyLinkedList::RemoveBack: list is empty";

	if (head->next == head) { // если элемент всего один
		delete head; // удаляем элемент
		head = nullptr; // обнуляем указатель
	}
	else {
		Node *tmp = head->prev;
		head->prev = tmp->prev;
		tmp->prev->next = head;

		delete tmp;
	}

	length--; // уменьшаем длину
}

// удаление по индексу
template <typename T>
void CircularDoublyLinkedList<T>::RemoveAt(int index) {
	// если индекс находится вне границ
	if (index < 0 || index >= length)
		throw "CircularDoublyLinkedList::RemoveAt(index): index out of bounds"; // бросаем исключение

	length--; // уменьшаем длину

	if (head->next == head) { // если элемент всего один
		delete head; // удаляем элемент
		head = nullptr; // обнуляем указатель
		return; // выходим
	}

	Node *tmp;

	if (index == 0) {
		Node *tail = head->prev;
		tmp = head;

		head = head->next;
		head->prev = tail;
		tail->next = head;
	}
	else {
		Node *node = head;

		while (index) {
			index--;
			node = node->next;
		}

		Node *prev = node->prev;
		tmp = node; // запоминаем адрес нужного элемента
		prev->next = node->next; // подменяем указатели
		node->next->prev = prev; // минуя текущий элемент
	}

	delete tmp; // удаляем ненужный элемент
}

// удаление элементов равных value
template <typename T>
void CircularDoublyLinkedList<T>::Remove(const T& value) {
	// пока значение вначале, удаляем из начала
	while (head && head->value == value)
		RemoveFront();

	// пока значение вконце, удаляем с конца
	while (head && head->prev->value == value)
		RemoveBack();
	
	// если список стал пуст, то выходим
	if (head == nullptr)
		return;

	Node *node = head->next;

	// пока не просмотрим все оставшиеся элементы
	while (node != head) {
		if (node->value == value) { // если встретили элемент с нужным значением
			length--; // уменьшаем длину

			Node *tmp = node;

			node->prev->next = node->next;
			node->next->prev = node->prev;

			node = node->next;
			delete tmp;
		}
		else {
			node = node->next; // иначе переходим на следующий элемент
		}
	}
}

// разворот списка
template <typename T>
void CircularDoublyLinkedList<T>::Reverse() {
	if (head == nullptr || head->next == head)
		return; // выходим, если список пустой или состоит из одного элемента

	Node *newHead = nullptr;
	Node *curr = head->prev;

	while (curr->prev != head->prev) {
		Node *prev = curr->prev;

		if (newHead == nullptr) {
			curr->next = curr;
			curr->prev = curr;
			newHead = curr;
		}
		else {
			curr->next = newHead;
			curr->prev = newHead->prev;

			newHead->prev->next = curr;
			newHead->prev = curr;
		}
		
		curr = prev;
	}

	curr->next = newHead;
	curr->prev = newHead->prev;

	newHead->prev->next = curr;
	newHead->prev = curr;

	head = newHead;
}

// печать списка с начала
template <typename T>
void CircularDoublyLinkedList<T>::Print() const {
	if (head == nullptr) {
		std::cout << "(empty)";
		return;
	}
	
	// иначе проходимся по всем элементам списка и выводим их
	Node *node = head;

	do {
		std::cout << node->value << " ";
		node = node->next;
	} while (node != head);
}

// печать списка с конца
template <typename T>
void CircularDoublyLinkedList<T>::PrintBackward() const {
	if (head == nullptr) {
		std::cout << "(empty)";
		return;
	}

	// иначе проходимся по всем элементам списка и выводим их
	Node *node = head->prev;

	do {
		std::cout << node->value << " ";
		node = node->prev;
	} while (node != head->prev);
}

// деструктор, освобождение памяти
template <typename T>
CircularDoublyLinkedList<T>::~CircularDoublyLinkedList() {
	if (head == nullptr)
		return; // если список пуст, то очищать нечего

	Node *node = head; // запоминаем указатель на начало списка

	do {
		Node *tmp = head; // сохраняем указатель на текущий элемент
		head = head->next; // переходим к следующему элементу
		delete tmp; // освобождаем память
	} while (head != node); // повторяем, пока не вернёмся в начало списка
}