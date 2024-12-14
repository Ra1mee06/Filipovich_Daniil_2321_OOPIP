#include <iostream>
#include <cmath>
#include <exception>
#include <string>

using namespace std;

class CustomException : public exception {
private:
    string message;
    double value;
    int errorCode;

public:
    CustomException(const string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const {
        return value;
    }

    int getCode() const {
        return errorCode;
    }
};

double calculateZ1(double& a) {
    if (a == 0 || 2 * a + pow(a, 2) == 0 || 2 * a - pow(a, 2) == 0) {
        throw CustomException("Ошибка: деление на ноль в Z1", a, 2);
    }

    double part1 = (1 + a + pow(a, 2)) / (2 * a + pow(a, 2)) + 2;
    double part2 = (1 - a + pow(a, 2)) / (2 * a - pow(a, 2));
    return pow(part1 - part2, -1) * (5 - 2 * pow(a, 2));
}

double calculateZ2(double& x) {
    return (4 - pow(x, 2)) / 2;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a, x;

    cout << "Введите значение a: ";
    cin >> a;
    cout << "Введите значение x: ";
    cin >> x;

    try {
        double z1 = calculateZ1(a);
        double z2 = calculateZ2(x);

        cout << "Z1 = " << z1 << endl;
        cout << "Z2 = " << z2 << endl;

        if (abs(z1 - z2) < 1e-6) {
            cout << "Z1 и Z2 примерно равны.\n";
        }
        else {
            cout << "Z1 и Z2 не равны.\n";
        }
    }
    catch (const CustomException& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
        cerr << "Значение: " << e.getValue() << endl;
        cerr << "Код ошибки: " << e.getCode() << endl;
    }

    return 0;
}
