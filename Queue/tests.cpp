#include <iostream>
#include <cassert>

#include "Queue.hpp"

using namespace std;

void EmptyQueueTests() {
	cout << "Empty tests: ";
	Queue<int> q;

	assert(q.IsEmpty());
	assert(q.GetSize() == 0);

	bool excepted = false;

	try {
		q.Dequeue();
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

void QueueTests() {
	cout << "Queue tests: ";

	Queue<int> q;

	q.Enqueue(1);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 1);
	assert(q.Front() == 1);
	assert(q.Back() == 1);

	q.Enqueue(2);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 2);
	assert(q.Front() == 1);
	assert(q.Back() == 2);

	q.Enqueue(3);
	q.Enqueue(4);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 4);
	assert(q.Front() == 1);
	assert(q.Back() == 4);

	assert(q.Dequeue() == 1);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 3);
	assert(q.Front() == 2);
	assert(q.Back() == 4);

	assert(q.Dequeue() == 2);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 2);
	assert(q.Front() == 3);
	assert(q.Back() == 4);

	assert(q.Dequeue() == 3);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 1);
	assert(q.Front() == 4);
	assert(q.Back() == 4);

	assert(q.Dequeue() == 4);

	assert(q.IsEmpty());
	assert(q.GetSize() == 0);

	cout << "OK" << endl;
}

void QueueCopyTests() {
	cout << "Copy tests: ";

	Queue<int> q;

	q.Enqueue(1);
	q.Enqueue(2);
	q.Enqueue(3);
	q.Enqueue(4);
	q.Enqueue(5);

	Queue<int> copy(q);

	assert(!copy.IsEmpty());
	assert(copy.GetSize() == 5);
	assert(copy.Front() == 1);
	assert(copy.Back() == 5);

	copy.Enqueue(6);

	assert(!copy.IsEmpty());
	assert(copy.GetSize() == 6);
	assert(copy.Front() == 1);
	assert(copy.Back() == 6);

	assert(!q.IsEmpty());
	assert(q.GetSize() == 5);
	assert(q.Front() == 1);
	assert(q.Back() == 5);

	cout << "OK" << endl;
}

void QueueAssignTests() {
	cout << "Assign tests: ";
	
	Queue<int> q;

	q.Enqueue(1);
	q.Enqueue(2);
	q.Enqueue(3);
	q.Enqueue(4);
	q.Enqueue(5);

	Queue<int> q2;

	q2.Enqueue(4);
	q2.Enqueue(3);
	q2.Enqueue(2);
	q2.Enqueue(1);

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
	EmptyQueueTests();
	QueueTests();
	QueueCopyTests();
	QueueAssignTests();
}