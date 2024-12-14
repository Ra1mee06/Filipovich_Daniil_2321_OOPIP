#include "pch.h"
#include "List.h"
#include "ExceptionHandler.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

template <typename T>
void visualizeForwardIteration(const List<T>& list) {
    auto iterator = list.createForwardIterator();
    while (iterator->hasNext()) {
        cout << iterator->next() << " ";
        this_thread::sleep_for(chrono::milliseconds(500)); 
    }
    cout << endl;
}

template <typename T>
void visualizeReverseIteration(const List<T>& list) {
    auto iterator = list.createReverseIterator();
    while (iterator->hasNext()) {
        cout << iterator->next() << " ";
        this_thread::sleep_for(chrono::milliseconds(500)); 
    }
    cout << endl;
}

int main() {
    try {

        List<int> intList = { 1, 2, 3, 4, 5 };
        cout << "Forward iteration of intList: ";
        visualizeForwardIteration(intList);

        cout << "Reverse iteration of intList: ";
        visualizeReverseIteration(intList);

        List<double> doubleList = { 1.1, 2.2, 3.3, 4.4 };
        cout << "Forward iteration of doubleList: ";
        visualizeForwardIteration(doubleList);

        cout << "Reverse iteration of doubleList: ";
        visualizeReverseIteration(doubleList);

        List<string> stringList = { "one", "two", "three" };
        cout << "Forward iteration of stringList: ";
        visualizeForwardIteration(stringList);

        cout << "Reverse iteration of stringList: ";
        visualizeReverseIteration(stringList);

        List<int> emptyList;
        try {
            emptyList.pop_back();
        }
        catch (const exception& e) {
            ExceptionHandler::handle(e);
        }

    }
    catch (const exception& e) {
        ExceptionHandler::handle(e);
    }

    return 0;
}
