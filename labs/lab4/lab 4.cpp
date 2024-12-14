#include <iostream>
#include <string>
#include "Queue.h"
#include "Stack.h"
#include "List.h"
#include "ExceptionHandler.h"

using namespace std;
using namespace containers;

void menu() {
    cout << "Меню:\n";
    cout << "1. Добавить элемент в очередь\n";
    cout << "2. Удалить элемент из очереди\n";
    cout << "3. Проверить, пуста ли очередь\n";
    cout << "4. Получить размер очереди\n";
    cout << "5. Добавить элемент в стек\n";
    cout << "6. Удалить элемент из стека\n";
    cout << "7. Проверить, пуст ли стек\n";
    cout << "8. Получить размер стека\n";
    cout << "9. Добавить элемент в список\n";
    cout << "10. Удалить элемент из списка\n";
    cout << "11. Получить размер списка\n";
    cout << "12. закончить работу\n";
    cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "RUS");
    try {
        Queue<int> queueInt;
        Stack<int> stackInt;
        List<int> listInt;

        Queue<double> queueDouble;
        Stack<double> stackDouble;
        List<double> listDouble;

        Queue<string> queueString;
        Stack<string> stackString;
        List<string> listString;

        int choice;
        int intValue;
        double doubleValue;
        string stringValue;

        while (true) {
            menu();
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "Введите значение (int): ";
                cin >> intValue;
                queueInt.enqueue(intValue);
                cout << "Введите значение (double): ";
                cin >> doubleValue;
                queueDouble.enqueue(doubleValue);
                cout << "Введите значение (string): ";
                cin >> stringValue;
                queueString.enqueue(stringValue);
                break;
            case 2:
                cout << "Удалённое значение (int): " << queueInt.dequeue() << "\n";
                cout << "Удалённое значение (double): " << queueDouble.dequeue() << "\n";
                cout << "Удалённое значение (string): " << queueString.dequeue() << "\n";
                break;
            case 3:
                cout << "Пуста ли очередь (int): " << (queueInt.isEmpty() ? "Да" : "Нет") << "\n";
                cout << "Пуста ли очередь (double): " << (queueDouble.isEmpty() ? "Да" : "Нет") << "\n";
                cout << "Пуста ли очередь (string): " << (queueString.isEmpty() ? "Да" : "Нет") << "\n";
                break;
            case 4:
                cout << "Размер очереди (int): " << queueInt.getSize() << "\n";
                cout << "Размер очереди (double): " << queueDouble.getSize() << "\n";
                cout << "Размер очереди (string): " << queueString.getSize() << "\n";
                break;
            case 5:
                cout << "Введите значение (int): ";
                cin >> intValue;
                stackInt.push(intValue);
                cout << "Введите значение (double): ";
                cin >> doubleValue;
                stackDouble.push(doubleValue);
                cout << "Введите значение (string): ";
                cin >> stringValue;
                stackString.push(stringValue);
                break;
            case 6:
                cout << "Удалённое значение (int): " << stackInt.pop() << "\n";
                cout << "Удалённое значение (double): " << stackDouble.pop() << "\n";
                cout << "Удалённое значение (string): " << stackString.pop() << "\n";
                break;
            case 7:
                cout << "Пуст ли стек (int): " << (stackInt.isEmpty() ? "Да" : "Нет") << "\n";
                cout << "Пуст ли стек (double): " << (stackDouble.isEmpty() ? "Да" : "Нет") << "\n";
                cout << "Пуст ли стек (string): " << (stackString.isEmpty() ? "Да" : "Нет") << "\n";
                break;
            case 8:
                cout << "Размер стека (int): " << stackInt.getSize() << "\n";
                cout << "Размер стека (double): " << stackDouble.getSize() << "\n";
                cout << "Размер стека (string): " << stackString.getSize() << "\n";
                break;
            case 9:
                cout << "Введите значение (int): ";
                cin >> intValue;
                listInt.push_front(intValue);
                cout << "Введите значение (double): ";
                cin >> doubleValue;
                listDouble.push_front(doubleValue);
                cout << "Введите значение (string): ";
                cin >> stringValue;
                listString.push_front(stringValue);
                break;
            case 10:
                cout << "Введите значение для удаления (int): ";
                cin >> intValue;
                listInt.remove(intValue);
                cout << "Введите значение для удаления (double): ";
                cin >> doubleValue;
                listDouble.remove(doubleValue);
                cout << "Введите значение для удаления (string): ";
                cin >> stringValue;
                listString.remove(stringValue);
                break;
            case 11:
                cout << "Размер списка (int): " << listInt.getSize() << "\n";
                cout << "Размер списка (double): " << listDouble.getSize() << "\n";
                cout << "Размер списка (string): " << listString.getSize() << "\n";
                break;
            case 12:
                return 0;
            default:
                cout << "Неверный выбор, попробуйте снова.\n";
            }
        }
    }
    catch (const ExceptionHandler& e) {
        cerr << "Поймано исключение: " << e.what() << endl;
    }

    return 0;
}
