#include <iostream>
#include <cassert>

#include "Deque.hpp"

using namespace std;

void EmptyDequeTests() {
	cout << "Empty tests: ";
	Deque<int> q;

	assert(q.IsEmpty());
	assert(q.GetSize() == 0);

	bool excepted = false;

	try {
		q.DequeueFront();
	}
	catch (string) {
		excepted = true;
	}

	assert(excepted);

	excepted = false;

	try {
		q.Front();
	}
	catch (string) {
		excepted = true;
	}

	assert(excepted);

	excepted = false;

	try {
		q.Back();
	}
	catch (string) {
		excepted = true;
	}

	assert(excepted);

	cout << "OK" << endl;
}

void DequeTests() {
	cout << "Deque tests: ";

	Deque<int> q;

	q.EnqueueBack(1);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 1);
	assert(q.Front() == 1);
	assert(q.Back() == 1);

	q.EnqueueBack(2);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 2);
	assert(q.Front() == 1);
	assert(q.Back() == 2);

	q.EnqueueBack(3);
	q.EnqueueBack(4);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 4);
	assert(q.Front() == 1);
	assert(q.Back() == 4);

	assert(q.DequeueFront() == 1);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 3);
	assert(q.Front() == 2);
	assert(q.Back() == 4);

	assert(q.DequeueFront() == 2);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 2);
	assert(q.Front() == 3);
	assert(q.Back() == 4);

	assert(q.DequeueFront() == 3);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 1);
	assert(q.Front() == 4);
	assert(q.Back() == 4);

	assert(q.DequeueFront() == 4);

	assert(q.IsEmpty());
	assert(q.GetSize() == 0);


	q.EnqueueFront(1);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 1);
	assert(q.Back() == 1);
	assert(q.Front() == 1);

	q.EnqueueFront(2);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 2);
	assert(q.Back() == 1);
	assert(q.Front() == 2);

	q.EnqueueFront(3);
	q.EnqueueFront(4);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 4);
	assert(q.Back() == 1);
	assert(q.Front() == 4);

	assert(q.DequeueBack() == 1);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 3);
	assert(q.Back() == 2);
	assert(q.Front() == 4);

	assert(q.DequeueBack() == 2);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 2);
	assert(q.Back() == 3);
	assert(q.Front() == 4);

	assert(q.DequeueBack() == 3);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 1);
	assert(q.Back() == 4);
	assert(q.Front() == 4);

	assert(q.DequeueBack() == 4);

	assert(q.IsEmpty());
	assert(q.GetSize() == 0);

	cout << "OK" << endl;
}

void DequeCopyTests() {
	cout << "Copy tests: ";

	Deque<int> q;

	q.EnqueueBack(1);
	q.EnqueueFront(2);
	q.EnqueueBack(3);
	q.EnqueueFront(4);
	q.EnqueueBack(5);

	Deque<int> copy(q);

	assert(!copy.IsEmpty());
	assert(copy.GetSize() == 5);
	assert(copy.Front() == 4);
	assert(copy.Back() == 5);

	copy.EnqueueBack(6);

	assert(!copy.IsEmpty());
	assert(copy.GetSize() == 6);
	assert(copy.Front() == 4);
	assert(copy.Back() == 6);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 5);
	assert(q.Front() == 4);
	assert(q.Back() == 5);

	cout << "OK" << endl;
}

void DequeAssignTests() {
	cout << "Assign tests: ";
	
	Deque<int> q;

	q.EnqueueBack(1);
	q.EnqueueBack(2);
	q.EnqueueBack(3);
	q.EnqueueBack(4);
	q.EnqueueBack(5);

	Deque<int> q2;

	q2.EnqueueBack(4);
	q2.EnqueueBack(3);
	q2.EnqueueBack(2);
	q2.EnqueueBack(1);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 5);

	assert(!q2.IsEmpty());
	assert(q2.GetSize() == 4);

	q2 = q;

	assert(!q.IsEmpty());
	assert(q.GetSize() == 5);

	assert(!q2.IsEmpty());
	assert(q2.GetSize() == 5);
	assert(q2.Front() == 1);
	assert(q2.Back() == 5);

	cout << "OK" << endl;
}

int main() {
	EmptyDequeTests();
	DequeTests();
	DequeCopyTests();
	DequeAssignTests();
}