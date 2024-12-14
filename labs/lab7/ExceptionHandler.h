#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <iostream>
#include <exception>
using namespace std;

class ExceptionHandler {
public:

    static void handle(const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
};

#endif 

