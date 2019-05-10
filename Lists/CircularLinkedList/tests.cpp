#include <iostream>
#include <cassert>

#include "CircularLinkedList.hpp"

using namespace std;

void AddFrontTests() {
	cout << "AddFrontTests: ";

	CircularLinkedList<int> list;

	assert(list.IsEmpty());
	assert(list.Length() == 0);

	list.AddFront(1);

	assert(!list.IsEmpty());
	assert(list.Length() == 1);
	assert(list.GetFirst() == 1);
	assert(list.GetLast() == 1);
	assert(list.Get(0) == 1);

	list.AddFront(2);

	assert(!list.IsEmpty());
	assert(list.Length() == 2);
	assert(list.GetFirst() == 2);
	assert(list.GetLast() == 1);
	assert(list.Get(0) == 2);
	assert(list.Get(1) == 1);

	list.AddFront(3);

	assert(!list.IsEmpty());
	assert(list.Length() == 3);
	assert(list.GetFirst() == 3);
	assert(list.GetLast() == 1);
	assert(list.Get(0) == 3);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 1);

	list.AddFront(4);

	assert(!list.IsEmpty());
	assert(list.Length() == 4);
	assert(list.GetFirst() == 4);
	assert(list.GetLast() == 1);
	assert(list.Get(0) == 4);
	assert(list.Get(1) == 3);
	assert(list.Get(2) == 2);
	assert(list.Get(3) == 1);

	cout << "OK" << endl;
}

void AddBackTests() {
	cout << "AddBackTests: ";

	CircularLinkedList<int> list;

	assert(list.IsEmpty());

	list.AddBack(1);

	assert(!list.IsEmpty());
	assert(list.Length() == 1);
	assert(list.GetFirst() == 1);
	assert(list.GetLast() == 1);
	assert(list.Get(0) == 1);

	list.AddBack(2);

	assert(!list.IsEmpty());
	assert(list.Length() == 2);
	assert(list.GetFirst() == 1);
	assert(list.GetLast() == 2);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);

	list.AddBack(3);

	assert(!list.IsEmpty());
	assert(list.Length() == 3);
	assert(list.GetFirst() == 1);
	assert(list.GetLast() == 3);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 3);

	list.AddBack(4);

	assert(!list.IsEmpty());
	assert(list.Length() == 4);
	assert(list.GetFirst() == 1);
	assert(list.GetLast() == 4);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 3);
	assert(list.Get(3) == 4);

	cout << "OK" << endl;
}

void InsertAtTests() {
	cout << "InsertAtTests: ";

	CircularLinkedList<int> list;

	list.AddBack(1); // 1
	list.AddBack(2); // 1 2

	list.InsertAt(0, 0); // 0 1 2

	assert(!list.IsEmpty());
	assert(list.Length() == 3);
	assert(list.GetFirst() == 0);
	assert(list.GetLast() == 2);
	assert(list.Get(0) == 0);
	assert(list.Get(1) == 1);
	assert(list.Get(2) == 2);

	list.InsertAt(2, 4); // 0 1 4 2

	assert(!list.IsEmpty());
	assert(list.Length() == 4);
	assert(list.GetFirst() == 0);
	assert(list.GetLast() == 2);
	assert(list.Get(0) == 0);
	assert(list.Get(1) == 1);
	assert(list.Get(2) == 4);
	assert(list.Get(3) == 2);

	list.InsertAt(0, 5); // 5 0 1 4 2

	assert(!list.IsEmpty());
	assert(list.Length() == 5);
	assert(list.GetFirst() == 5);
	assert(list.GetLast() == 2);
	assert(list.Get(0) == 5);
	assert(list.Get(1) == 0);
	assert(list.Get(2) == 1);
	assert(list.Get(3) == 4);
	assert(list.Get(4) == 2);

	cout << "OK" << endl;
}

void RemoveFrontTests() {
	cout << "RemoveFrontTests: ";

	CircularLinkedList<int> list;

	list.AddBack(1);
	list.AddBack(2);
	list.AddBack(3);
	list.AddBack(4);
	list.AddBack(5);

	list.RemoveFront();

	assert(!list.IsEmpty());
	assert(list.Length() == 4);
	assert(list.Get(0) == 2);
	assert(list.Get(1) == 3);
	assert(list.Get(2) == 4);
	assert(list.Get(3) == 5);

	list.RemoveFront();

	assert(!list.IsEmpty());
	assert(list.Length() == 3);
	assert(list.Get(0) == 3);
	assert(list.Get(1) == 4);
	assert(list.Get(2) == 5);

	list.RemoveFront();

	assert(!list.IsEmpty());
	assert(list.Length() == 2);
	assert(list.Get(0) == 4);
	assert(list.Get(1) == 5);

	list.RemoveFront();

	assert(!list.IsEmpty());
	assert(list.Length() == 1);
	assert(list.Get(0) == 5);

	list.RemoveFront();

	assert(list.IsEmpty());
	assert(list.Length() == 0);

	cout << "OK" << endl;
}

void RemoveBackTests() {
	cout << "RemoveBackTests: ";

	CircularLinkedList<int> list;

	list.AddBack(1);
	list.AddBack(2);
	list.AddBack(3);
	list.AddBack(4);
	list.AddBack(5);

	list.RemoveBack();

	assert(!list.IsEmpty());
	assert(list.Length() == 4);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 3);
	assert(list.Get(3) == 4);

	list.RemoveBack();

	assert(!list.IsEmpty());
	assert(list.Length() == 3);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 3);

	list.RemoveBack();

	assert(!list.IsEmpty());
	assert(list.Length() == 2);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);

	list.RemoveBack();

	assert(!list.IsEmpty());
	assert(list.Length() == 1);
	assert(list.Get(0) == 1);

	list.RemoveBack();

	assert(list.IsEmpty());
	assert(list.Length() == 0);

	cout << "OK" << endl;
}

void RemoveAtTests() {
	cout << "RemoveAtTests: ";

	CircularLinkedList<int> list;

	list.AddBack(1);
	list.AddBack(2);
	list.AddBack(3);
	list.AddBack(4);
	list.AddBack(5);

	list.RemoveAt(2);

	assert(!list.IsEmpty());
	assert(list.Length() == 4);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 4);
	assert(list.Get(3) == 5);

	list.RemoveAt(1);

	assert(!list.IsEmpty());
	assert(list.Length() == 3);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 4);
	assert(list.Get(2) == 5);

	list.RemoveAt(2);

	assert(!list.IsEmpty());
	assert(list.Length() == 2);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 4);

	list.RemoveAt(0);

	assert(!list.IsEmpty());
	assert(list.Length() == 1);
	assert(list.Get(0) == 4);

	list.RemoveAt(0);

	assert(list.IsEmpty());
	assert(list.Length() == 0);

	cout << "OK" << endl;	
}

void RemoveTests() {
	cout << "RemoveTests: ";

	CircularLinkedList<int> list;

	list.AddBack(1);
	list.AddBack(2);
	list.AddBack(1);

	list.Remove(0);

	assert(!list.IsEmpty());
	assert(list.Length() == 3);
	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 1);

	list.Remove(1);

	assert(!list.IsEmpty());
	assert(list.Length() == 1);
	assert(list.Get(0) == 2);
	
	list.Remove(2);

	assert(list.IsEmpty());
	assert(list.Length() == 0);

	list.AddBack(1);
	list.AddBack(1);
	list.AddBack(1);
	list.AddBack(1);
	list.AddBack(1);
	list.AddBack(1);

	assert(!list.IsEmpty());
	assert(list.Length() == 6);

	list.Remove(1);

	assert(list.IsEmpty());
	assert(list.Length() == 0);

	list.AddBack(1);
	list.AddBack(1);
	list.AddBack(2);
	list.AddBack(3);
	list.AddBack(1);
	list.AddBack(1);
	list.AddBack(4);
	list.AddBack(1);
	list.AddBack(5);
	list.AddBack(1);
	list.AddBack(1);
	list.AddBack(1);

	assert(!list.IsEmpty());
	assert(list.Length() == 12);

	list.Remove(1);

	assert(!list.IsEmpty());
	assert(list.Length() == 4);
	assert(list.Get(0) == 2);
	assert(list.Get(1) == 3);
	assert(list.Get(2) == 4);
	assert(list.Get(3) == 5);

	cout << "OK" << endl;	
}

void CopyTests() {
	cout << "Copy tests: ";

	CircularLinkedList<int> l1;

	l1.AddBack(1);
	l1.AddBack(2);
	l1.AddBack(3);
	l1.AddFront(4);
	l1.AddFront(5);
	l1.AddFront(6);

	CircularLinkedList<int> l2(l1);

	assert(l2.Length() == 6);
	assert(l1.Get(0) == 6);
	assert(l1.Get(1) == 5);
	assert(l1.Get(2) == 4);
	assert(l1.Get(3) == 1);
	assert(l1.Get(4) == 2);
	assert(l1.Get(5) == 3);

	cout << "OK" << endl;
}

void IsSortedTests() {
	cout << "IsSortedTests: ";
	CircularLinkedList<int> list;

	assert(!list.IsSorted());

	list.AddBack(1);

	assert(list.IsSorted());

	list.AddBack(2);

	assert(list.IsSorted());

	list.AddBack(2);
	list.AddBack(3);

	assert(list.IsSorted());

	list.AddBack(1);

	assert(!list.IsSorted());

	cout << "OK" << endl;
}

void ReverseTests() {
	cout << "ReverseTests: ";

	CircularLinkedList<int> list;

	list.AddBack(1);

	assert(list.Get(0) == 1);

	list.Reverse();

	assert(list.Get(0) == 1);

	list.AddBack(2);

	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);

	list.Reverse();

	assert(list.Get(0) == 2);
	assert(list.Get(1) == 1);

	list.AddFront(3);
	list.AddFront(4);
	list.AddFront(5);

	assert(list.Get(0) == 5);
	assert(list.Get(1) == 4);
	assert(list.Get(2) == 3);
	assert(list.Get(3) == 2);
	assert(list.Get(4) == 1);

	list.Reverse();

	assert(list.Get(0) == 1);
	assert(list.Get(1) == 2);
	assert(list.Get(2) == 3);
	assert(list.Get(3) == 4);
	assert(list.Get(4) == 5);

	cout << "OK" << endl;
}

int main() {
	AddFrontTests();
	AddBackTests();
	InsertAtTests();

	RemoveFrontTests();
	RemoveBackTests();
	RemoveAtTests();
	RemoveTests();

	CopyTests();
	IsSortedTests();
	ReverseTests();
}