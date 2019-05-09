#pragma once

#include <iostream>

template <typename T>
class Treap {
	struct Node {
		T value; // значение элемента
		int priority; // приоритет

		Node *left; // указатель на левое поддерево
		Node *right; // указатель на правое поддерево
	};

	Node* RotateLeft(Node *node); // левый поворот
	Node* RotateRight(Node *node); // правый поворот

	Node* Remove(Node *node, const T& value); // удаление
	Node* Insert(Node* node, const T& value); // вставка

	void Copy(Node *node, Node* &newNode); // копирование дерева
	void Clear(Node* &node); // очистка дерева (освобождение памяти)

	int GetSize(Node *node) const; // количество элементов в дереве
	int GetHeight(Node *node) const; // высота дерева

	void Print(std::ostream &os, Node *node, int level) const; // вывод дерева в виде повёрнутого дерева в поток
	
	void PreOrder(std::ostream &os, Node *node) const; // прямой порядок вывода
	void InOrder(std::ostream &os, Node *node) const; // центрированный порядок вывода
	void PostOrder(std::ostream &os, Node *node) const; // обратный порядок вывода

	Node *root; // корень дерева

public:
	Treap(); // конструктор по умолчанию
	Treap(const Treap& treap); // конструктор копирования

	Treap& operator=(const Treap& tree); // оператор присваивания

	void Insert(const T& value); // вставка элемента в дерево
	bool Remove(const T& value); // удаление элемента из дерева
	void Clear(); // удаление всех элементов из дерева

	bool Find(const T& value) const; // поиск элемента в дереве

	int GetSize() const; // количество элементов в дереве
	int GetHeight() const; // высота дерева

	void PreOrder(std::ostream &os) const; // прямой порядок вывода
	void InOrder(std::ostream &os) const; // симметричный порядок вывода
	void PostOrder(std::ostream &os) const; // обратный порядок вывода

	~Treap(); // деструктор (освобождение памяти)

	template <typename T1>
	friend std::ostream& operator<<(std::ostream &os, const Treap<T1>& tree); // оператор вывода в поток
};

// левый поворот
template <typename T>
typename Treap<T>::Node* Treap<T>::RotateLeft(Node *node) {
	Node *right = node->right;
	Node *T2 = right->left;

	right->left = node;
	node->right = T2;

	return right;
}

// правый поворот
template <typename T>
typename Treap<T>::Node* Treap<T>::RotateRight(Node *node) {
	Node *left = node->left;
	Node *T2 = left->right;
	left->right = node;
	node->left = T2;

	return left;
}

// вставка
template <typename T>
typename Treap<T>::Node* Treap<T>::Insert(Node* node, const T& value) {
	if (node == nullptr) {
		node = new Node;
		node->value = value;
		node->priority = rand();
		node->left = nullptr;
		node->right = nullptr;

		return node;
	}

	if (value <= node->value) {
		node->left = Insert(node->left, value);

		if (node->left->priority > node->priority)
			node = RotateRight(node);
	}
	else {
		node->right = Insert(node->right, value);

		if (node->right->priority > node->priority)
			node = RotateLeft(node);
	}

	return node;
}

// удаление
template <typename T>
typename Treap<T>::Node* Treap<T>::Remove(Node *node, const T& value) {
	if (node == nullptr)
		return nullptr;

	if (value < node->value) {
		node->left = Remove(node->left, value);
	}
	else if (value > node->value) {
		node->right = Remove(node->right, value);
	}
	else if (node->left == nullptr) {
		Node *tmp = node->right;
		delete node;
		node = tmp;
	}
	else if (node->right == nullptr) {
		Node *tmp = node->left;
		delete node;
		node = tmp;
	}
	else if (node->left->priority < node->right->priority) {
		node = RotateLeft(node);
		node->left = Remove(node->left, value);
	}
	else {
		node = RotateRight(node);
		node->right = Remove(node->right, value);
	}

	return node;
}

// копирование дерева
template <typename T>
void Treap<T>::Copy(Node *node, Node* &newNode) {
	if (node == nullptr)
		return;

	newNode = new Node;
	
	newNode->value = node->value;
	newNode->priority = node->priority;
	newNode->left = nullptr;
	newNode->right = nullptr;

	Copy(node->left, newNode->left); // копируем левое поддерево
	Copy(node->right, newNode->right); // копируем правое поддерево
}

// удаление элементов из дерева и освобождение памяти
template <typename T>
void Treap<T>::Clear(Node* &node) {
	if (node == nullptr)
		return;

	Clear(node->left); // удаляем левое поддерево
	Clear(node->right); // удаляем правоеп поддерево

	delete node; // удаляем элемент
	node = nullptr; // обнуляем значение элемента
}

// количество элементов в дереве
template <typename T>
int Treap<T>::GetSize(Node *node) const {
	if (node == nullptr)
		return 0; // лист не считается за элемент

	int left = GetSize(node->left); // находим число элементов в левом поддереве
	int right = GetSize(node->right); // находим число элементов в правом поддереве

	return 1 + left + right; // итоговое число элементов - сумма числа элементов в поддеревьях + 1
}

// высота дерева
template <typename T> 
int Treap<T>::GetHeight(Node *node) const {
	if (node == nullptr)
		return 0; // высота листа равна 0

	int left = GetHeight(node->left); // получаем высоту левого поддеревп
	int right = GetHeight(node->right); //  получаем высоту правого поддерева

	return 1 + (left > right ? left : right); // высота узла на 1 больше, чем максимальная из высот поддеревьев
}

// вывод дерева в виде повёрнутого дерева в поток
template <typename T>
void Treap<T>::Print(std::ostream &os, Node *node, int level) const {
	if (node == nullptr)
		return;

	Print(os, node->right, level + 1);

	for (int i = 0; i < level; i++)
		os << "	";

	os << node->value << std::endl;

	Print(os, node->left, level + 1);
}

// прямой порядок вывода
template <typename T>
void Treap<T>::PreOrder(std::ostream &os, Node *node) const {
	if (node == nullptr)
		return;

	os << node->value << " ";
	PreOrder(os, node->left);
	PreOrder(os, node->right);
}

// центрированный порядок вывода
template <typename T>
void Treap<T>::InOrder(std::ostream &os, Node *node) const {
	if (node == nullptr)
		return;

	InOrder(os, node->left);
	os << node->value << " ";
	InOrder(os, node->right);
}

// обратный порядок вывода
template <typename T>
void Treap<T>::PostOrder(std::ostream &os, Node *node) const {
	if (node == nullptr)
		return;

	PostOrder(os, node->left);
	PostOrder(os, node->right);
	os << node->value << " ";
}

// конструктор по умолчанию
template <typename T>
Treap<T>::Treap() {
	root = nullptr; // изначально дерева нет
}

// конструктор копирования
template <typename T>
Treap<T>::Treap(const Treap& tree) {
	Copy(tree.root, root);
}

// оператор присваивания
template <typename T>
Treap<T>& Treap<T>::operator=(const Treap& tree) {
	if (this == &tree)
		return *this;

	Clear(root); // очищаем текущее дерево
	Copy(tree.root, root); // копируем второе дерево

	return *this;
}

// вставка элемента в дерево
template <typename T>
void Treap<T>::Insert(const T& value) {
	root = Insert(root, value);
}

// удаление элемента из дерева
template <typename T>
bool Treap<T>::Remove(const T& value) {
	if (!Find(value))
		return false;

	root = Remove(root, value);

	return true;
}

// удаление всех элементов из дерева
template <typename T>
void Treap<T>::Clear() {
	Clear(root); // вызываем рекурсивную функцию очистки от дерева
}

// поиск элемента в дереве
template <typename T>
bool Treap<T>::Find(const T& value) const {
	Node *node = root;

	while (node != nullptr) {
		if (node->value == value)
			return true;

		if (value < node->value) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	return false;
}

// количество элементов в дереве
template <typename T>
int Treap<T>::GetSize() const {
	return GetSize(root); // вызываем рекурсивную версию получения размера
}

// высота дерева
template <typename T> 
int Treap<T>::GetHeight() const {
	return GetHeight(root); // вызываем рекурсивную версию получения высоты
}

// прямой порядок вывода
template <typename T>
void Treap<T>::PreOrder(std::ostream &os) const {
	PreOrder(os, root);
}

// симметричный порядок вывода
template <typename T>
void Treap<T>::InOrder(std::ostream &os) const {
	InOrder(os, root);
}

// обратный порядок вывода
template <typename T>
void Treap<T>::PostOrder(std::ostream &os) const {
	PostOrder(os, root);
}

// деструктор (освобождения памяти)
template <typename T>
Treap<T>::~Treap() {
	Clear(root);
}

// оператор вывода в поток
template <typename T>
std::ostream& operator<<(std::ostream &os, const Treap<T>& tree) {
	tree.Print(os, tree.root, 0);

	return os;
}