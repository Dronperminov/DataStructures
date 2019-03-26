#pragma once

#include <iostream>

template <typename T>
class CircularLinkedList {
	struct Node {
		T value; // значение элемента
		Node *next; // указатель на следующий элемент
	};

	Node *head; // указатель на начало списка
	int length; // количество элементов списка

public:
	CircularLinkedList(); // конструктор по умолчанию
	CircularLinkedList(const CircularLinkedList& list); // конструктор копирования
	
	int Length() const; // получение длины списка
	bool IsEmpty() const; // проверка списка на пустоту
	bool IsSorted() const; // проверка на упорядоченность (по неубыванию)

	T& GetFirst(); // получение первого элемента списка
	T& GetLast(); // получение последнего элемента списка
	T& Get(int index); // получение элемента по индексу

	void AddFront(const T& value); // добавление в начало списка
	void AddBack(const T& value); // добавление в конец списка
	void InsertAt(int index, const T& value); // добавление в произвольное место списка

	void RemoveFront(); // удаление из начала списка
	void RemoveBack(); // удаление с конца списка
	void RemoveAt(int index); // удаление по индексу
	void Remove(const T& value); // удаление элементов равных value

	void Reverse(); // разворот списка
	
	void Print() const; // печать списка

	~CircularLinkedList(); // деструктор, освобождение памяти
};

// конструктор по умолчанию
template <typename T>
CircularLinkedList<T>::CircularLinkedList() {
	head = nullptr;
	length = 0;
}

// конструктор копирования
template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList& list) {
	head = nullptr; // обнуляем указатель
	length = list.length; // копируем длину

	// если нечего копировать, то не копируем
	if (list.head == nullptr)
		return;

	Node *orig = list.head;
	Node *last = nullptr;

	do {
		Node *node = new Node; // выделяем память под элемент

		node->value = orig->value; // сохраняем значение

		if (head == nullptr) {
			head = node; // новый элемент становится первым
			last = node;
		}
		else {
			last->next = node;
		}

		node->next = head; // закольцовываем на начало
		last = node;

		orig = orig->next;
	} while (orig != list.head);
}

// получение длины списка
template <typename T>
int CircularLinkedList<T>::Length() const {
	return length;
}

// проверка списка на пустоту
template <typename T>
bool CircularLinkedList<T>::IsEmpty() const {
	return head == nullptr;
}

// проверка на упорядоченность (по неубыванию)
template <typename T>
bool CircularLinkedList<T>::IsSorted() const {
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
T& CircularLinkedList<T>::GetFirst() {
	// если нет элементов, бросаем исключение
	if (head == nullptr)
		throw "CircularLinkedList::GetFirst(): list is empty";

	return head->value; // возвращаем первый элемент
}

// получение последнего элемента списка
template <typename T>
T& CircularLinkedList<T>::GetLast() {
	// если нет элементов, бросаем исключение
	if (head == nullptr)
		throw "CircularLinkedList::GetLast(): list is empty";

	// идём до последнего элемента списка
	Node *last = head;

	while (last->next != head)
		last = last->next;

	return last->value; // и возвращаем последнее значение
}

// получение элемента по индексу
template <typename T>
T& CircularLinkedList<T>::Get(int index) {
	// если индекс вне границ
	if (index < 0 || index >= length)
		throw "CircularLinkedList::Get(index): index out of bounds"; // бросаем исключение

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
void CircularLinkedList<T>::AddFront(const T& value) {
	Node *node = new Node; // выделяем память под элемент

	node->value = value; // сохраняем значение

	// если список пуст
	if (head == nullptr) {
		node->next = node; // закольцовываем на себя
	}
	else {
		Node *last = head;

		// ищем послежний элемент списка
		while (last->next != head)
			last = last->next;

		last->next = node; // обновляем указатель на следующий элемент
		node->next = head; // следующий за текущим будет начальный
	}

	head = node; // обновляем начальный элемент

	length++; // увеличиваем длину
}

// добавление в конец списка
template <typename T>
void CircularLinkedList<T>::AddBack(const T& value) {
	Node *node = new Node; // выделяем память под элемент

	node->value = value; // сохраняем значение

	if (head == nullptr) {
		head = node; // новый элемент становится первым
	}
	else {
		Node *last = head;

		while (last->next != head)
			last = last->next;

		last->next = node;
	}

	node->next = head; // закольцовываем на начало

	length++; // увеличиваем длину
}

template <typename T>
void CircularLinkedList<T>::InsertAt(int index, const T& value) {
	if (index < 0 || index >= length)
		throw "CircularLinkedList::InsertAt(index): index out of bounds";

	length++; // увеличиваем длину

	Node *node = new Node; // выделяем память под элемент
	node->value = value; // сохраняем значение

	if (index == 0) {
		// если список пуст
		if (head == nullptr) {
			node->next = node; // закольцовываем на себя
		}
		else {
			Node *last = head;

			// ищем послежний элемент списка
			while (last->next != head)
				last = last->next;

			last->next = node; // обновляем указатель на следующий элемент
			node->next = head; // следующий за текущим будет начальный
		}

		head = node; // обновляем начальный элемент
	}
	else {
		// доходим до элемента с индексом index - 1
		Node *prev = head;

		while (index - 1) {
			index--;
			prev = prev->next;
		}

		node->next = prev->next;
		prev->next = node;
	}
}

// удаление из начала списка
template <typename T>
void CircularLinkedList<T>::RemoveFront() {
	if (head == nullptr)
		throw "CircularLinkedList::RemoveFront: list is empty";

	if (head->next == head) { // если элемент всего один
		delete head; // удаляем элемент
		head = nullptr; // обнуляем указатель
	}
	else {
		Node *tmp = head; // запоминаем удаляемый элемент
		Node *last = head; // последний элемент списка

		// ищем последний элемент списка
		while (last->next != head)
			last = last->next;

		last->next = head->next; // обновляем указатель на начало
		head = head->next; // сдвигаем указатель на начало списка

		delete tmp; // удаляем старый элемент
	}

	length--; // уменьшаем длину
}

// удаление с конца списка
template <typename T>
void CircularLinkedList<T>::RemoveBack() {
	if (head == nullptr)
		throw "CircularLinkedList::RemoveBack: list is empty";

	if (head->next == head) { // если элемент всего один
		delete head; // удаляем элемент
		head = nullptr; // обнуляем указатель
	}
	else {
		Node *last = head;

		// ищем предпоследний элемент
		while (last->next->next != head)
			last = last->next;

		Node *tmp = last->next; // запоминаем последний элемент
		last->next = head; // перекидываем указатель на начало списка

		delete tmp; // удаляем элемент
	}

	length--; // уменьшаем длину
}

// удаление по индексу
template <typename T>
void CircularLinkedList<T>::RemoveAt(int index) {
	// если индекс находится вне границ
	if (index < 0 || index >= length)
		throw "CircularLinkedList::RemoveAt(index): index out of bounds"; // бросаем исключение

	length--; // уменьшаем длину

	if (head->next == head) { // если элемент всего один
		delete head; // удаляем элемент
		head = nullptr; // обнуляем указатель
		return; // выходим
	}

	Node *tmp; // элемент для удаления

	if (index == 0) {
		tmp = head; // запоминаем удаляемый элемент
		Node *last = head; // последний элемент списка

		// ищем последний элемент списка
		while (last->next != head)
			last = last->next;

		last->next = head->next; // обновляем указатель на начало
		head = head->next; // сдвигаем указатель на начало списка
	}
	else {
		Node *prev = nullptr;
		Node *node = head;

		while (index) {
			index--;
			prev = node;
			node = node->next;
		}

		tmp = node; // запоминаем адрес нужного элемента
		prev->next = node->next; // подменяем указатели
	}

	delete tmp; // удаляем ненужный элемент
}

// удаление элементов равных value
template <typename T>
void CircularLinkedList<T>::Remove(const T& value) {
	// пока значение вначале, удаляем из начала
	while (head && head->value == value) 
		RemoveFront();
	
	// если список стал пуст, то выходим
	if (head == nullptr)
		return;

	Node *prev = head;
	Node *node = head->next;

	// пока не просмотрим все оставшиеся элементы
	while (node != head) {
		if (node->value == value) { // если встретили элемент с нужным значением
			length--; // уменьшаем длину

			Node *tmp = node;

			prev->next = node->next;
			node = node->next;

			delete tmp;
		}
		else {
			prev = node;
			node = node->next; // иначе переходим на следующий элемент
		}
	}
}

// разворот списка
template <typename T>
void CircularLinkedList<T>::Reverse() {
	if (head == nullptr || head->next == head)
		return; // выходим, если список пустой или состоит из одного элемента

	Node *prev = nullptr;
	Node *curr = head;

	do {
		Node *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	} while (curr != head);

	head->next = prev;
	head = prev;
}

// печать списка
template <typename T>
void CircularLinkedList<T>::Print() const {
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

// деструктор, освобождение памяти
template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
	if (head == nullptr)
		return; // если список пуст, то очищать нечего

	Node *node = head; // запоминаем указатель на начало списка

	do {
		Node *tmp = head; // сохраняем указатель на текущий элемент
		head = head->next; // переходим к следующему элементу
		delete tmp; // освобождаем память
	} while (head != node); // повторяем, пока не вернёмся в начало списка
}