#include <iostream>
#include <iomanip> 
using namespace std;

class StringManipulator {
private:
    string str;

public:
    friend istream& operator>>(istream& is, StringManipulator& obj) {
        is >> obj.str;
        return is;
    }

    friend ostream& operator<<(ostream& os, const StringManipulator& obj) {
        for (char c : obj.str) {
            os << "Символ: " << c
                << ", Шестнадцатеричный код: " << hex << uppercase << (int)c
                << ", Восьмеричный код: " << oct << (int)c
                << endl;
        }
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    StringManipulator sm;
    cout << "Введите строку: ";
    cin >> sm;

    cout << "Результат:\n" << sm;
    return 0;
}
