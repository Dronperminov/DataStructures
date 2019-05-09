#pragma once

#include <iostream>

template <typename T>
class Tree {
    struct Node {
    	T value; // значение элемента

    	Node *left; // указатель на левое поддерево
    	Node *right; // указатель на правое поддерево
    };

    Node *root; // корень дерева

	Node* Insert(Node *node, const T& value); // вставка в дерево
    Node* Remove(Node *node, const T& value); // удаление из дерева

    void Copy(Node *node, Node* &newNode); // копирование дерева
    void Clear(Node* &node); // очистка дерева (освобождение памяти)

    int GetSize(Node *node) const; // количество элементов в дереве
    int GetHeight(Node *node) const; // высота дерева

    void Print(std::ostream &os, Node *node, int level) const; // вывод дерева в виде повёрнутого дерева в поток

public:
    Tree(); // конструктор по умолчанию
    Tree(const Tree& tree); // конструктор копирования

    Tree& operator=(const Tree& tree); // оператор присваивания

    void Insert(const T& value); // вставка элемента в дерево
    bool Remove(const T& value); // удаление элемента из дерева
    void Clear(); // удаление всех элементов из дерева

    bool Find(const T& value) const; // поиск элемента в дереве

    int GetSize() const; // количество элементов в дереве
    int GetHeight() const; // высота дерева

    ~Tree(); // деструктор (освобождение памяти)

    template <typename T1>
    friend std::ostream& operator<<(std::ostream &os, const Tree<T1>& tree); // оператор вывода в поток
};

// вставка в дерево
template <typename T>
typename Tree<T>::Node* Tree<T>::Insert(Node *node, const T& value) {
	if (node == nullptr) {
		node = new Node; // создаём новый элемент

		node->value = value; // сохраняем значение
		node->left = nullptr;
		node->right = nullptr;

		return node; // возвращаем его
	}

	// если значение меньше значения узла
	if (value < node->value) {
		node->left = Insert(node->left, value); // вставляем в левое поддерево
	}
	else {
		node->right = Insert(node->right, value); // иначе вставляем в правое поддерево
	}

	return node; // возвращаем неизменённый указатель
}

// удаление из дерева
template <typename T>
typename Tree<T>::Node* Tree<T>::Remove(Node *node, const T& value) {
	if (node == nullptr)
		return nullptr;

	if (value < node->value) {
		node->left = Remove(node->left, value); // если значение меньше узла, удаляем из левого поддерева
	}
	else if (value > node->value) {
		node->right = Remove(node->right, value); // если значение больше узла, удаляем из правого поддерева
	}
	else {
		// если один ребёнок или ни одного
		if (node->left == nullptr || node->right == nullptr) {
			Node *tmp = node->left ? node->left : node->right;
			delete node;

			return tmp;
		}

		Node *parent = node->right;
		Node *tmp = node->right;

		while (tmp->left) {
			parent = tmp;
			tmp = tmp->left;
		}

		if (parent != tmp) {
			parent->left = tmp->right;
		}
		else {
			node->right = tmp->right;
		}
		
		node->value = tmp->value;
		
		delete tmp;
	}

	return node;
}

// копирование дерева
template <typename T>
void Tree<T>::Copy(Node *node, Node* &newNode) {
	if (node == nullptr)
		return;

	newNode = new Node;

	newNode->value = node->value;
	newNode->left = nullptr;
	newNode->right = nullptr;

	Copy(node->left, newNode->left); // копируем левое поддерево
	Copy(node->right, newNode->right); // копируем правое поддерево
}

// удаление элементов из дерева и освобождение памяти
template <typename T>
void Tree<T>::Clear(Node* &node) {
	if (node == nullptr)
		return;

	Clear(node->left); // удаляем левое поддерево
	Clear(node->right); // удаляем правое поддерево

	delete node; // удаляем элемент
	node = nullptr; // обнуляем значение элемента
}

// количество элементов в дереве
template <typename T>
int Tree<T>::GetSize(Node *node) const {
	if (node == nullptr)
		return 0; // лист не считается за элемент

	int leftSize = GetSize(node->left); // находим число элементов в левом поддереве
	int rightSize = GetSize(node->right); // находим число элементов в правом поддереве

	return 1 + leftSize + rightSize; // итоговое число элементов - сумма числа элементов в поддеревьях + 1
}

// высота дерева
template <typename T>
int Tree<T>::GetHeight(Node *node) const {
	if (node == nullptr)
		return 0; // высота листа равна 0

	int leftHeight = GetHeight(node->left); // получаем высоту левого поддеревп
	int rightHeight = GetHeight(node->right); //  получаем высоту правого поддерева

	return 1 + std::max(leftHeight, rightHeight); // высота узла на 1 больше, чем максимальная из высот поддеревьев
}

// вывод дерева в виде повёрнутого дерева в поток
template <typename T>
void Tree<T>::Print(std::ostream &os, Node *node, int level) const {
	if (node == nullptr)
		return;

	Print(os, node->right, level + 1);

	for (int i = 0; i < level; i++)
		os << "    ";

	os << node->value << std::endl;

	Print(os, node->left, level + 1);
}

// конструктор по умолчанию
template <typename T>
Tree<T>::Tree() {
	root = nullptr; // изначально дерева нет
}

// конструктор копирования
template <typename T>
Tree<T>::Tree(const Tree& tree) {
	Copy(tree.root, root);
}

// оператор присваивания
template <typename T>
Tree<T>& Tree<T>::operator=(const Tree& tree) {
    if (this == &tree)
        return *this;

    Clear(root); // очищаем текущее дерево
    Copy(tree.root, root); // копируем второе дерево

    return *this;
}

template <typename T>
void Tree<T>::Insert(const T& value) {
	root = Insert(root, value);
}

template <typename T>
bool Tree<T>::Remove(const T& value) {
	if (!Find(value))
		return false;

	root = Remove(root, value);

	return true;
}

// удаление всех элементов из дерева
template <typename T>
void Tree<T>::Clear() {
	Clear(root); // вызываем рекурсивную функцию очистки от дерева
}

// поиск элемента в дереве
template <typename T>
bool Tree<T>::Find(const T& value) const {
	Node *node = root;

	while (node) {
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
int Tree<T>::GetSize() const {
	return GetSize(root); // вызываем рекурсивную версию получения размера
}

// высота дерева
template <typename T>
int Tree<T>::GetHeight() const {
	return GetHeight(root); // вызываем рекурсивную версию получения высоты
}

// деструктор (освобождения памяти)
template <typename T>
Tree<T>::~Tree() {
	Clear(root);
}

// оператор вывода в поток
template <typename T>
std::ostream& operator<<(std::ostream &os, const Tree<T>& tree) {
    tree.Print(os, tree.root, 0);

    return os;
}