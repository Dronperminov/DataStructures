#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename T>
class LinkedList {
	struct Node {
		T value; // значение элемента списка
		Node *next; // указатель на следующий элемент списка
	};

	Node *head; // начало списка
	int length; // количество элементов списка

	Node* GetTail(Node *node) const; // получение последнего элемента списка
	Node* Partition(Node *head, Node *tail, Node* &newHead, Node* &newTail);

	Node* QuickSort(Node *head, Node *end); // рекурсивный метод быстрой сортировкм

public:
	LinkedList(); // конструктор по умолчанию
	LinkedList(const LinkedList &list); // конструктор копирования

	LinkedList& operator=(const LinkedList &list); // оператор присваивания

int Length() const; // получение длины списка
	bool IsEmpty() const; // проверка списка на пустоту
	bool IsSorted() const; // проверка на упорядоченность (по неубыванию)

	T& GetFirst(); // получение первого элемента списка: O(1)
	T& GetLast(); // получение последнего элемента списка: O(N)
	T& Get(int index); // получение элемента по индексу: O(N)

	T GetMin() const; // получение минимума
	T GetMax() const; // получение максимума

	void AddFront(const T& value); // добавление в начало списка: O(1)
	void AddBack(const T& value); // добавление в конец списка: O(N)
	void InsertAt(int index, const T& value); // добавление в произвольное место списка: O(N)

	void RemoveFront(); // удаление с начала списка: O(1)
	void RemoveBack(); // удаление с конца списка: O(N)
	void RemoveAt(int index); // удаление по индексу: O(N)
	void Remove(const T& value); // удаление элементов равных value: O(N)

	void BubleSort(); // сортировка пузырьком
	void SelectionSort(); // сортировка выбором (минимума)
	void InsertionSort(); // сортировка вставками
	void MergeSort(); // сортировка слияниями
	void QuickSort(); // быстрая сортировка

	void Reverse(); // перестановка списка в обратном порядке

	void Print() const; // печать списка

	~LinkedList();
};

// получение последнего элемента списка
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetTail(Node *node) const {
	while (node && node->next)
		node = node->next;

	return node;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Partition(Node *head, Node *end, Node* &newHead, Node* &newEnd) {
	Node *pivot = end;
	Node *prev = nullptr;
	Node *cur = head;
	Node *tail = pivot;

	while (cur != pivot) {
		if (cur->value < pivot->value) {
			if (newHead == nullptr)
				newHead = cur;

			prev = cur;
			cur = cur->next;
		}
		else {
			if (prev)
				prev->next = cur->next;

			Node *tmp = cur->next;
			cur->next = nullptr;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}

	if (newHead == nullptr)
		newHead = pivot;

	newEnd = tail;

	return pivot;
}

// екурсивный метод быстрой сортировки
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::QuickSort(Node *head, Node *end) {
	if (head == nullptr || head == end)
		return head;

	Node *newHead = nullptr;
	Node *newEnd = nullptr;

	Node *pivot = Partition(head, end, newHead, newEnd);

	if (newHead != pivot) {
		Node *tmp = newHead;

		while (tmp->next != pivot)
			tmp = tmp->next;

		tmp->next = nullptr;

		newHead = QuickSort(newHead, tmp);

		tmp = GetTail(newHead);
		tmp->next =  pivot;
	}

	pivot->next = QuickSort(pivot->next, newEnd);

	return newHead;
}

template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	length = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList &list) {
	head = nullptr;
	length = list.length;

	Node *prev = nullptr;

	for (Node *orig = list.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;

		if (prev == nullptr) {
			head = node;
		}
		else {
			prev->next = node;
		}

		prev = node;
	}
}

// оператор присваивания
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &list) {
	if (this == &list)
		return *this;

	while (head) {
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}

	length = list.length;

	Node *prev = nullptr;

	for (Node *orig = list.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;

		if (prev == nullptr) {
			head = node;
		}
		else {
			prev->next = node;
		}

		prev = node;
	}

	return *this;
}

template <typename T>
int LinkedList<T>::Length() const {
	return length;
}

template <typename T>
bool LinkedList<T>::IsEmpty() const {
	return length == 0;
}

template <typename T>
bool LinkedList<T>::IsSorted() const {
	if (IsEmpty())
		return false; // пустой список не является упорядоченным

	Node *node = head;

	while (node->next && node->value <= node->next->value)
		node = node->next;

	return node->next == nullptr;
}

template <typename T>
T& LinkedList<T>::GetFirst() {
	// если нет элементов, бросаем исключение
	if (IsEmpty())
		throw "LinkedList::GetFirst(): list is empty";

	return head->value; // возвращаем первый элемент
}

template <typename T>
T& LinkedList<T>::GetLast() {
	// если нет элементов, бросаем исключение
	if (IsEmpty())
		throw "LinkedList::GetLast(): list is empty";

	Node *node = head;

	// идём до последнего элемента
	while (node->next)
		node = node->next;

	return node->value; // возврашаем его знчение
}

template <typename T>
T& LinkedList<T>::Get(int index) {
	// если индекс вне границ
	if (index < 0 || index >= length)
		throw "LinkedList::Get(index): index out of bounds"; // бросаем исключение

	Node *node = head;

	// доходим до элемента с нужным индексом
	while (node != nullptr && index) {
		index--;
		node = node->next;
	}

	return node->value; // возвращаем его значение
}

template <typename T>
T LinkedList<T>::GetMin() const {
	if (IsEmpty())
		throw "LinkedList::GetMin(): list is empty";

	T min = head->value;

	Node *node = head->next;

	while (node) {
		if (node->value < min)
			min = node->value;

		node = node->next;
	}

	return min;
}

template <typename T>
T LinkedList<T>::GetMax() const {
	if (IsEmpty())
		throw "LinkedList::GetMax(): list is empty";

	T max = head->value;

	Node *node = head->next;

	while (node) {
		if (node->value > max)
			max = node->value;

		node = node->next;
	}

	return max;
}

template <typename T>
void LinkedList<T>::AddFront(const T& value) {
	Node *node = new Node; // создаём элемент

	node->value = value; // сохраняем значение
	node->next = head;

	head = node; // обновляем начало списка

	length++; // увеличиваем длину
}

template <typename T>
void LinkedList<T>::AddBack(const T& value) {
	Node *node = new Node; // создаём элемент

	node->value = value; // сохраняем значение
	node->next = nullptr;

	if (head == nullptr) { // если начала списка нет
		head = node; // то этот элемент и является началом
	}
	else {
		Node *prev = head;

		// иначе идём до последнего элемента
		while (prev->next)
			prev = prev->next;

		prev->next = node; // и обновляем указатель на следующий элемент
	}

	length++; // увеличиваем длину
}

template <typename T>
void LinkedList<T>::InsertAt(int index, const T& value) {
	if (index < 0 || index >= length)
		throw "LinkedList::InsertAt(index): index out of bounds";

	// если вставляем перед нулевым элементом
	if (index == 0) {
		AddFront(value); // то вставляем в начало
		return;
	}

	// доходим до элемента с индексом index - 1
	Node *prev = head;

	while (index - 1) {
		index--;
		prev = prev->next;
	}

	// создаём новый элемент и вставляем его
	Node *node = new Node;

	node->value = value;
	node->next = prev->next;
	prev->next = node;

	length++; // увеличиваем длину
}

template <typename T>
void LinkedList<T>::RemoveFront() {
	// если список пуст
	if (IsEmpty())
		throw "LinkedList::RemoveFront(): list is empty"; // бросаем исключение

	Node *tmp = head; // сохраняем значение текущего начала
	head = head->next; // переходим к следующему элементу
	delete tmp; // удаляем старое начало

	length--; // уменьшаем длину
}

template <typename T>
void LinkedList<T>::RemoveBack() {
	// если список пуст
	if (IsEmpty())
		throw "LinkedList::RemoveBack(): list is empty"; // бросаем исключение

	length--;

	if (head->next == nullptr) {
		delete head;

		head = nullptr;
		return;
	}

	Node *prev = head;

	// доходим до последнего элемента
	while (prev->next->next)
		prev = prev->next;
	
	delete prev->next;

	prev->next = nullptr;
}

template <typename T>
void LinkedList<T>::RemoveAt(int index) {
	// если индекс находится вне границ
	if (index < 0 || index >= length)
		throw "LinkedList::RemoveAt(index): index out of bounds"; // бросаем исключение

	// если удаляем из нулевого индекса
	if (index == 0) {
		RemoveFront(); // то удаляем из начала
		return;
	}

	Node *prev = nullptr;
	Node *node = head;

	while (index) {
		index--;

		prev = node;
		node = node->next;
	}

	prev->next = node->next;
	delete node;

	length--;
}

template <typename T>
void LinkedList<T>::Remove(const T& value) {
	// пока нужный элемент в начале списка
	while (!IsEmpty() && head->value == value)
		RemoveFront(); // удаляем из начала

	// если удалять больше нечего
	if (IsEmpty())
		return; // то выходим

	// запоминаем текущее и предыдущее значения элементов списка
	Node *prev = head;
	Node *node = head->next;

	// доходим до конца списка
	while (node != nullptr) {
		if (node->value == value) { // если нашли элемент для удаления, то удаляем его
			length--; // уменьшаем длину
			
			Node *tmp = node; // сохраняем адрес текущего элемента
			prev->next = node->next; // подменяем указатели

			delete tmp; // удаляем ненужный элемент

			node = prev;
		}

		prev = node;
		node = node->next; // переходим к следующему элементу
	}
}

template <typename T>
void LinkedList<T>::BubleSort() {
	if (length < 2)
		return;

	bool isSorted = false;

	while (!isSorted) {
		isSorted = true;

		Node *prev = nullptr;
		Node *node = head;

		while (node->next) {
			if (node->value > node->next->value) {
				Node *next = node->next;
				node->next = next->next;
				next->next = node;

				if (node == head) {
					head = next;
				}
				else {
					prev->next = next;
					node = next;
				}

				isSorted = false;
			}

			prev = node;
			node = node->next;
		}
	}
}

template <typename T>
void LinkedList<T>::SelectionSort() {
	if (length < 2)
		return;

	Node *prev = nullptr;
	Node *node = head;

	while (node) {
		Node *minPrev = prev;
		Node *min = node;

		Node *tmpPrev = node;
		Node *tmp = node->next;

		while (tmp) {
			if (tmp->value < min->value) {
				minPrev = tmpPrev;
				min = tmp;
			}

			tmpPrev = tmp;
			tmp = tmp->next;
		}

		if (node == min) {
			prev = node;
			node = node->next;
		}
		else {
			if (prev != nullptr) {
				prev->next = min;
			}
			else {
				head = min;
			}

			if (node->next == min) {
				node->next = min->next;
				min->next = node;

				prev = min;
			}
			else {
				Node *next2 = min->next;

				min->next = node->next;
				node->next = next2;

				minPrev->next = node;

				prev = min;
				node = min->next;
			}
		}
	}
}

template <typename T>
void LinkedList<T>::InsertionSort() {
	Node *current = head;
	head = nullptr;

	while (current) {
		Node *next = current->next;

		if (head == nullptr || head->value >= current->value) {
			current->next = head;
			head = current;
		}
		else {
			Node *node = head;

			while (node->next && node->next->value < current->value)
				node = node->next;

			current->next = node->next;
			node->next = current;
		}

		current = next;
	}
}

template <typename T>
void LinkedList<T>::MergeSort() {
	if (length < 2)
		return; // если список пуст или из 1 элемента, то выходим

	// списки для левой и правой половины
	LinkedList<T> left;
	LinkedList<T> right;

	int index = 0;
	Node *tmp = head;

	// записываем левую половину списка в левый список
	while (index < length / 2) {
		left.AddBack(tmp->value);

		index++;
		tmp = tmp->next;
	}

	// записываем правую половину списка в правый список
	while (index < length) {
		right.AddBack(tmp->value);

		index++;
		tmp = tmp->next;
	}

	// рекурсивно выполняем сортировку подсписков
	left.MergeSort();
	right.MergeSort();

	tmp = head;

	// выполняем слияние подсписков в список
	while (!left.IsEmpty() && !right.IsEmpty()) {
		T value1 = left.GetFirst();
		T value2 = right.GetFirst();

		if (value1 < value2) {
			tmp->value = value1;
			left.RemoveFront();
		}
		else {
			tmp->value = value2;
			right.RemoveFront();
		}

		tmp = tmp->next;
	}

	// дозаписываем из левого подсписка
	while (!left.IsEmpty()) {
		tmp->value = left.GetFirst();
		left.RemoveFront();

		tmp = tmp->next;
	}

	// дозаписываем из правого подсписка
	while (!right.IsEmpty()) {
		tmp->value = right.GetFirst();
		right.RemoveFront();

		tmp = tmp->next;
	}
}

template <typename T>
void LinkedList<T>::QuickSort() {
	Node *tail = GetTail(head); // получаем конец списка

	head = QuickSort(head, tail); // вызываем рекурсивный алгоритм
}

template <typename T>
void LinkedList<T>::Reverse() {
	if (head == nullptr || head->next == nullptr)
		return;

	Node *node = head;

	while (node->next) {
		Node *tmp = node->next;
		node->next = tmp->next;
		tmp->next = head;
		head = tmp;
	}
}

template <typename T>
void LinkedList<T>::Print() const {
	if (IsEmpty())
		std::cout << "(empty)";
	
	Node *node = head;

	while (node != nullptr) {
		std::cout << node->value << " ";

		node = node->next;
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	while (head) {
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}
}

#endif