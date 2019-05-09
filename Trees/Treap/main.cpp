#include <iostream>
#include <cstdlib>
#include "Treap.hpp"

using namespace std;

void Print(Treap<int> &Treap) {
    if (Treap.GetSize() == 0) {
        cout << "(empty)" << endl;
    }
    else {
        cout << Treap;
        cout << endl << "PreOrder: ";
        Treap.PreOrder(cout);

        cout << endl << "InOrder: ";
        Treap.InOrder(cout);

        cout << endl << "PostOrder: ";
        Treap.PostOrder(cout);
        cout << endl;
    }
}

void Insert(Treap<int> &Treap) {
    int value;

    cout << "Enter value for insert: ";
    cin >> value;

    Treap.Insert(value);
    cout << "Inserted!" << endl;
}

void Find(Treap<int> &Treap) {
    int value;

    cout << "Enter value for search: ";
    cin >> value;

    if (Treap.Find(value)) {
        cout << "Find!" << endl;
    }
    else {
        cout << "No value " << value << " in Treap" << endl;
    }
}

void Remove(Treap<int> &Treap) {
    int value;

    cout << "Enter value for remove: ";
    cin >> value;

    if (Treap.Remove(value)) {
        cout << "Removed!" << endl;
    }
    else {
        cout << "No value " << value << " in Treap" << endl;
    }
}

void GetHeight(Treap<int> &Treap) {
    cout << "Height: " << Treap.GetHeight() << endl;
}

void GetSize(Treap<int> &Treap) {
    cout << "Size: " << Treap.GetSize() << endl;
}

int main() {
    int item; // выбираемый пункт меню
    Treap<int> Treap; // создаём дерево

    do {
        // выводим меню
        cout << "What do you want to do?" << endl;
        cout << "1. Print" << endl;
        cout << "2. Insert" << endl;
        cout << "3. Find" << endl;
        cout << "4. Remove" << endl;
        cout << "5. Get height" << endl;
        cout << "6. Get size" << endl;
        cout << "7. Quit" << endl;
        cout << ">";
        cin >> item; // считываем пункт меню

        // обрабатываем некорректный ввод
        while(item < 1 || item > 7) {
            cout << "Incorrect item. Try again: ";
            cin >> item; // считываем пункт меню заново
        }

        // в зависимости от выбранного пункта выполняем действие
        switch (item) {
            case 1:
                Print(Treap);
                break;

            case 2:
                Insert(Treap);
                break;

            case 3:
                Find(Treap);
                break;

            case 4:
                Remove(Treap);
                break;

            case 5:
                GetHeight(Treap);
                break;

            case 6:
                GetSize(Treap);
                break;
        }
    } while (item != 7); // повторяем, пока не решим выйти

    return 0;
}