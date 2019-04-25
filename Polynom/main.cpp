#include <iostream>
#include <cassert>

#include "Polynom.hpp"

using namespace std;

int main() {
    Polynom a, b;
    int item; // выбираемый пункт меню

    do {
        system("cls"); // очищаем экран
        // выводим меню
        cout << "What do you want to do?" << endl;
        cout << "1. Print" << endl;
        cout << "2. Read" << endl;
        cout << "3. Add" << endl;
        cout << "4. Sub" << endl;
        cout << "5. Mult" << endl;
        cout << "6. Div" << endl;
        cout << "7. Mod" << endl;
        cout << "8. Gcd" << endl;
        cout << "9. Quit" << endl;
        cout << ">";
        cin >> item; // считываем пункт меню

        // обрабатываем некорректный ввод
        while(item < 1 || item > 9) {
            cout << "Incorrect item. Try again: ";
            cin >> item; // считываем пункт меню заново
        }

        // в зависимости от выбранного пункта выполняем действие
        switch (item) {
            case 1:
                cout << "a: " << a << endl;
                cout << "b: " << b << endl;
                break;

            case 2:
                cout << "Enter a: ";
                cin >> a;
                cout << "Enter b: ";
                cin >> b;
                break;

            case 3:
                cout << "  a: " << a << endl;
                cout << "  b: " << b << endl;
                cout << "a+b: " << (a + b) << endl;
                break;

            case 4:
                cout << "  a: " << a << endl;
                cout << "  b: " << b << endl;
                cout << "a-b: " << (a - b) << endl;
                break;

            case 5:
                cout << "  a: " << a << endl;
                cout << "  b: " << b << endl;
                cout << "a*b: " << (a * b) << endl;
                break;

            case 6:
                cout << "  a: " << a << endl;
                cout << "  b: " << b << endl;
                cout << "a/b: " << (a / b) << endl;
                break;

            case 7:
                cout << "  a: " << a << endl;
                cout << "  b: " << b << endl;
                cout << "a%b: " << (a % b) << endl;
                break;

            case 8:
                cout << "  a: " << a << endl;
                cout << "  b: " << b << endl;
                cout << "gcd: " << a.GCD(b) << endl;
                break;
        }

        if (item != 9) {
            system("pause"); // задерживаем экран
        }
    } while (item != 9); // повторяем, пока не решим выйти

    return 0;
}