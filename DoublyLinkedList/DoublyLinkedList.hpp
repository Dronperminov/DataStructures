#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

template <typename T>
class DoublyLinkedList {
	struct Node {
		T value; // значение элемента списка
		Node *next; // ссылка на следующий элемент
		Node *prev; // ссылка на предыдущий элемент
	};

	Node *head; // начало списка
	Node *tail; // конец списка

	int length; // количество элементов списка

	void QuickSort(int first, int last, Node* &firstNode, Node* &lastNode);

public:
	DoublyLinkedList(); // конструктор по умолчанию
	DoublyLinkedList(const DoublyLinkedList<T> &list); // конструктор копирования

	int Length() const; // получение длины списка
	bool IsEmpty() const; // проверка списка на пустоту
	bool IsSorted() const; // проверка на упорядоченность (по неубыванию)

	T& GetFirst(); // получение первого элемента списка: O(1)
	T& GetLast(); // получение последнего элемента списка: O(1)
	T& Get(int index); // получение элемента по индексу: O(N)

	T GetMin() const; // получение минимума
	T GetMax() const; // получение максимума

	void AddFront(const T& value); // добавление в начало списка: O(1)
	void AddBack(const T& value); // добавление в конец списка: O(1)
	void InsertAt(int index, const T& value); // добавление в произвольное место списка: O(N)

	void RemoveFront(); // удаление с начала списка: O(1)
	void RemoveBack(); // удаление с конца списка: O(1)
	void RemoveAt(int index); // удаление по индексу: O(N)
	void Remove(const T& value); // удаление элементов равных value: O(N)

	void BubleSort(); // сортировка пузырьком
	void SelectionSort(); // сортировка выбором (минимума)
	void InsertionSort(); // сортировка вставками
	void MergeSort(); // сортировка слияниями
	void QuickSort(); // быстрая сортировка

	void Reverse(); // перестановка списка в обратном порядке
	void Swap(int index1, int index2); // переставить элементы с индексами index1 и index2 местами

	void Print() const; // печать списка с начала
	void PrintBackward() const; // печать списка с конца

	~DoublyLinkedList(); // деструктор
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	head = nullptr;
	tail = nullptr;

	length = 0;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &list) {
	head = nullptr;
	tail = nullptr;

	length = list.length;

	if (list.head == nullptr)
		return;
	
	for (Node *orig = list.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;
		node->prev = tail;

		// если список пуст
		if (tail == nullptr) {
			head = node; // то голова списка и есть этот элемент
		}
		else { // иначе вставляем в конец		
			tail->next = node;
		}

		tail = node;
	}
}

template <typename T>
int DoublyLinkedList<T>::Length() const {
	return length;
}

template <typename T>
bool DoublyLinkedList<T>::IsEmpty() const {
	return length == 0;
}

template <typename T>
bool DoublyLinkedList<T>::IsSorted() const {
	if (IsEmpty())
		return false; // пустой список не является упорядоченным

	Node *node = head;

	while (node->next && node->value <= node->next->value)
		node = node->next;

	return node->next == nullptr;
}

template <typename T>
T& DoublyLinkedList<T>::GetFirst() {
	// если нет элементов, бросаем исключение
	if (IsEmpty())
		throw "DoublyLinkedList::GetFirst(): list is empty";

	return head->value; // возвращаем первый элемент
}

template <typename T>
T& DoublyLinkedList<T>::GetLast() {
	// если нет элементов, бросаем исключение
	if (IsEmpty())
		throw "DoublyLinkedList::GetLast(): list is empty";

	return tail->value; // и возвращаем последнее значение
}

template <typename T>
T& DoublyLinkedList<T>::Get(int index) {
	// если индекс вне границ
	if (index < 0 || index >= length)
		throw "DoublyLinkedList::Get(index): index out of bounds"; // бросаем исключение

	Node *node = head;

	// доходим до элемента с нужным индексом
	while (node != nullptr && index) {
		index--;
		node = node->next;
	}

	return node->value; // возвращаем его значение
}

template <typename T>
T DoublyLinkedList<T>::GetMin() const {
	if (IsEmpty())
		throw "DoublyLinkedList::GetMin(): list is empty";

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
T DoublyLinkedList<T>::GetMax() const {
	if (IsEmpty())
		throw "DoublyLinkedList::GetMax(): list is empty";

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
void DoublyLinkedList<T>::AddFront(const T& value) {
	Node *node = new Node; // создаём элемент

	node->value = value; // сохраняем значение
	node->prev = nullptr;
	node->next = head;

	// если список пуст
	if (head == nullptr) {
		tail = node; // то конец списка является этим элементом
	}
	else {		
		head->prev = node; // иначе вставляем в начало
	}

	head = node; // обновляем начало списка

	length++; // увеличиваем длину
}

template <typename T>
void DoublyLinkedList<T>::AddBack(const T& value) {
	Node *node = new Node;

	node->value = value;
	node->prev = tail;
	node->next = nullptr;

	// если список пуст
	if (tail == nullptr) {
		head = node; // то голова списка является этим элементом
	}
	else { // иначе вставляем в конец		
		tail->next = node;
	}

	tail = node; // обновляем конец списка

	length++; // увеличиваем длину
}

template <typename T>
void DoublyLinkedList<T>::InsertAt(int index, const T& value) {
	if (index < 0 || index >= length)
		throw "DoublyLinkedList::InsertAt(index): index out of bounds";

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

	// обновляем ссылку конца, если нужно
	if (prev->next == tail)
		tail->prev = node;

	node->value = value;
	node->next = prev->next;
	prev->next->prev = node;
	prev->next = node;
	node->prev = prev;

	length++; // увеличиваем длину
}

template <typename T>
void DoublyLinkedList<T>::RemoveFront() {
	// если список пуст
	if (IsEmpty())
		throw "DoublyLinkedList::RemoveFront: list is empty"; // бросаем исключение

	Node *tmp = head; // сохраняем значение текущего начала
	head = head->next; // переходим к следующему элементу
	delete tmp; // удаляем старое начало

	length--; // уменьшаем длину

	// если начало пуста
	if (head == nullptr) {
		tail = nullptr; // то и конец пуст
	}
	else {
		head->prev = nullptr; // иначе обновляем указатель на предыдущий элемент
	}
}

template <typename T>
void DoublyLinkedList<T>::RemoveBack() {
	// если список пуст
	if (IsEmpty())
		throw "DoublyLinkedList::RemoveBack: list is empty"; // бросаем исключение

	Node *tmp = tail; // сохраняем значение текущего конца
	tail = tail->prev; // переходим к предыдущему элементу
	delete tmp; // удаляем старый конец

	length--; // уменьшаем длину

	// если конец пуст
	if (tail == nullptr) {
		head = nullptr; // то и начало пусто
	}
	else {
		tail->next = nullptr; // иначе обновляем указатель на следующий элемент
	}
}

template <typename T>
void DoublyLinkedList<T>::RemoveAt(int index) {
	// если индекс находится вне границ
	if (index < 0 || index >= length)
		throw "DoublyLinkedList::RemoveAt(index): index out of bounds"; // бросаем исключение

	// если удаляем из нулевого индекса
	if (index == 0) {
		RemoveFront(); // то удаляем из начала
		return;
	}

	// если удаляем последний элемент
	if (index == length - 1) {
		RemoveBack(); // то удаляем с конца
		return;
	}

	// иначе доходим до элемента с нужным индексом
	Node *prev = nullptr;
	Node *node = head;

	while (index) {
		index--;

		prev = node;
		node = node->next;
	}

	length--; // уменьшаем длину

	Node *tmp = node; // запоминаем адрес нужного элемента
	prev->next = node->next; // подменяем указатели
	node->next->prev = prev; // минуя текущий элемент

	delete tmp; // удаляем ненужный элемент
}

template <typename T>
void DoublyLinkedList<T>::Remove(const T& value) {
	// пока нужный элемент в начале списка
	while (!IsEmpty() && head->value == value)
		RemoveFront(); // удаляем из начала

	// пока нужный элемент в конце списка
	while (!IsEmpty() && tail->value == value)
		RemoveBack(); // удаляем из конца

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
			node->next->prev = prev; // минуя текущий элемент

			delete tmp; // удаляем ненужный элемент

			node = prev;
		}

		prev = node;
		node = node->next; // переходим к следующему элементу
	}
}

template <typename T>
void DoublyLinkedList<T>::BubleSort() {
	if (length < 2)
		return;

	bool isSorted = false; // флаг отсортированности

	// повторяем, пока не станет отсортирован
	while (!isSorted) {
		isSorted = true; // считаем, что отсортирован

		Node *node = head; // идём от начала списка

		// и до конца списка
		while (node->next) {
			Node *l1 = node;
			Node *l2 = node->next;

			// если элементы стоят в неправильном порядке, то переставляем их
			if (l1->value > l2->value) {
				Node *prev = l1->prev;
				Node *next = l2->next;

				l1->prev = l2;
				l1->next = next;

				l2->prev = prev;
				l2->next = l1;

				if (l1 == head) {
					head = l2;
					next->prev = l1;
				}
				else if (l2 == tail) {
					tail = l1;
					prev->next = l2;
				}
				else {
					prev->next = l2;
					next->prev = l1;
				}

				isSorted = false; // не отсортирован, так как была перестановка
			}
			else
				node = node->next; // переходим к следующему элементу
		}
	}
}

template <typename T>
void DoublyLinkedList<T>::SelectionSort() {
	if (length < 2)
		return;

	Node *node = head;

	while (node->next) {
		Node *min = node;
		Node *tmp = node->next;

		// ищем минимальный элемент списка
		while (tmp) {
			if (tmp->value < min->value) 
				min = tmp;

			tmp = tmp->next;
		}

		// если минимум и так на своём месте
		if (node == min) {
			node = node->next; // то переходим к следующему элементу
		}
		else { // иначе вставляем минимум на нужное место
			if (node == head) {
				head = min;
			}
			else {
				node->prev->next = min;
			}

			if (min == tail) {
				tail = node;
			}
			else {
				min->next->prev = node;
			}

			// если минимум идёт за текущим элементом
			if (node->next == min) {
				Node *prev = node->prev;
				Node *next = min->next;

				min->next = node;
				min->prev = prev;

				node->next = next;
				node->prev = min;
			}
			else { // иначе если текущий элемент и минимум далеко друг от друга
				Node *prev1 = node->prev;
				Node *next1 = node->next;

				Node *prev2 = min->prev;
				Node *next2 = min->next;

				node->next = next2;
				node->prev = prev2;

				min->next = next1;
				min->prev = prev1;

				prev2->next = node;
				next1->prev = min;

				node = next1;
			}
		}
	}
}

template <typename T>
void DoublyLinkedList<T>::InsertionSort() {
	if (length < 2)
		return;
	
	Node *node = head->next;

	while (node) {
		Node *tmp = node;

		Node *prev = node->prev;
		Node *next = node->next;

		prev->next = next;

		if (node != tail) {
			next->prev = prev;
		}
		else {
			tail = prev;
		}

		Node *elem = prev;

		// ищем место для вставки элемента
		while (elem && elem->value > tmp->value)
			elem = elem->prev;

		node->prev = elem;

		// и вставляем
		if (elem == nullptr) { // если дошли до начала, то вставляем в начало
			node->next = head;
			head->prev = node;

			head = node;
		}
		else {
			if (elem == tail) { // если в конце
				tail = node; // то конец указывает на текущий элемент
			}
			else { // иначе вставляем в середину
				node->next = elem->next;
				elem->next->prev = node;
			}

			elem->next = node;
		}

		node = tmp->next; // переходим к следующему элементу
	}
}

template <typename T>
void DoublyLinkedList<T>::MergeSort() {
	if (length < 2)
		return; // если список пуст или из 1 элемента, то выходим

	// списки для левой и правой половины
	DoublyLinkedList<T> left;
	DoublyLinkedList<T> right;

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
void DoublyLinkedList<T>::QuickSort(int first, int last, Node* &firstNode, Node* &lastNode) {
	if (first >= last)
		return;

	int left = first;
	int right = last;

	Node *leftNode = firstNode;
	Node *rightNode = lastNode;

	Node *node1 = firstNode;
	Node *node2 = lastNode;

	// ищем середину подсписка
	while (node1 != node2 && node1->next != node2) {
		node1 = node1->next;
		node2 = node2->prev;
	}

	T middle = node1->value; // запоминаем значение из серидины

	// выполняем разделение
	while (left <= right) {
		while (leftNode->value < middle) {
			left++;
			leftNode = leftNode->next;
		}

		while (rightNode->value > middle) {
			right--;
			rightNode = rightNode->prev;
		}

		if (left <= right) {
			T tmp = leftNode->value;
			leftNode->value = rightNode->value;
			rightNode->value = tmp;

			leftNode = leftNode->next;
			rightNode = rightNode->prev;

			left++;
			right--;
		}
	}

	// запускаем рекурсивно для двух подсписков
	QuickSort(first, right, firstNode, rightNode);
	QuickSort(left, last, leftNode, lastNode);
}

template <typename T>
void DoublyLinkedList<T>::QuickSort() {
	QuickSort(0, length - 1, head, tail);
}

template <typename T>
void DoublyLinkedList<T>::Reverse() {
	Node *node1 = head;
	Node *node2 = tail;

	while (node1 != node2 && node1->next != node2) {
		Node *next1 = node1->next;
		Node *prev1 = node1->prev;

		Node *next2 = node2->next;
		Node *prev2 = node2->prev;

		if (next2) {
			next2->prev = node1;
		}
		else {
			head = node2;
		}

		if (prev1) {
			prev1->next = node2;
		}
		else {
			tail = node1;
		}

		next1->prev = node2;
		prev2->next = node1;

		node1->next = next2;
		node1->prev = prev2;

		node2->next = next1;
		node2->prev = prev1;

		node1 = next1;
		node2 = prev2;
	}
}

template <typename T>
void DoublyLinkedList<T>::Swap(int index1, int index2) {
	if (index1 < 0 || index1 >= length)
		throw "DoublyLinkedList<T>::Swap(int index1, int index2): index1 out of bounds";

	if (index2 < 0 || index2 >= length)
		throw "DoublyLinkedList<T>::Swap(int index1, int index2): index2 out of bounds";

	if (index1 == index2)
		return;

	Node *node1 = head;
	Node *node2 = head;

	if (index2 < index1) {
		int tmp = index1;
		index1 = index2;
		index2 = tmp;
	}

	int index = 0;

	while (index < index1 && index < index2) {
		index++;

		node1 = node1->next;
		node2 = node2->next;
	}

	while (index < index1) {
		index++;
		node1 = node1->next;
	}

	while (index < index2) {
		index++;
		node2 = node2->next;
	}

	if (index1 == index2 - 1) {
		Node *prev = node1->prev;
		Node *next = node2->next;

		node1->next = next;
		node1->prev = node2;

		node2->next = node1;
		node2->prev = prev;

		if (node1 == head) {
			head = node2;
		}
		else {
			prev->next = node2;
		}

		if (node2 == tail) {
			tail = node1;
		}
		else {
			next->prev = node1;
		}
	}
	else {
		Node *prev1 = node1->prev;
		Node *next1 = node1->next;

		Node *prev2 = node2->prev;
		Node *next2 = node2->next;

		node1->next = next2;
		node1->prev = prev2;

		node2->next = next1;
		node2->prev = prev1;

		if (node1 == head) {
			head = node2;
		}
		else {
			prev1->next = node2;
		}

		next1->prev = node2;
		prev2->next = node1;

		if (node2 == tail) {
			tail = node1;
		}
		else {
			next2->prev = node1;
		}
	}
}

template <typename T>
void DoublyLinkedList<T>::Print() const {
	if (IsEmpty())
		std::cout << "(empty)";
	
	Node *node = head;

	while (node != nullptr) {
		std::cout << node->value << " ";

		node = node->next;
	}
}

template <typename T>
void DoublyLinkedList<T>::PrintBackward() const {
	if (IsEmpty())
		std::cout << "(empty)";

	Node *node = tail;

	while (node != nullptr) {
		std::cout << node->value << " ";

		node = node->prev;
	}
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	while (head) {
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}

	tail = nullptr;
}

#endif