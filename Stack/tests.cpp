#include <iostream>
#include <cassert>

#include "Stack.hpp"

using namespace std;

int main() {
	cout << "Tests: ";
	Stack<int> stack;

	assert(stack.IsEmpty());
	assert(stack.GetSize() == 0);

	stack.Push(1);

	assert(!stack.IsEmpty());
	assert(stack.GetSize() == 1);
	assert(stack.Top() == 1);

	stack.Push(2);
	stack.Push(3);

	assert(!stack.IsEmpty());
	assert(stack.GetSize() == 3);
	assert(stack.Top() == 3);

	Stack<int> copy = stack;

	assert(!copy.IsEmpty());
	assert(copy.GetSize() == 3);
	assert(copy.Top() == 3);

	assert(stack.Pop() == 3);
	assert(!stack.IsEmpty());
	assert(stack.GetSize() == 2);
	assert(stack.Top() == 2);

	assert(stack.Pop() == 2);
	assert(!stack.IsEmpty());
	assert(stack.GetSize() == 1);
	assert(stack.Top() == 1);

	assert(!copy.IsEmpty());
	assert(copy.GetSize() == 3);
	assert(copy.Top() == 3);

	copy = stack;

	assert(!copy.IsEmpty());
	assert(copy.GetSize() == 1);
	assert(copy.Top() == 1);

	assert(stack.Pop() == 1);
	assert(stack.IsEmpty());
	assert(stack.GetSize() == 0);

	bool excepted = false;

	try {
		stack.Top();
	}
	catch (std::string) {
		excepted = true;
	}

	assert(excepted);

	excepted = false;

	try {
		stack.Pop();
	}
	catch (std::string) {
		excepted = true;
	}

	assert(excepted);

	cout << "OK" << endl;
}