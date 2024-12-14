#include <iostream>
#include <memory> 

using namespace std;

template <typename T>
class ShPtr {
private:
    T* ptr;
    size_t* ref_count;

    void addRef() {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

public:
    ShPtr() : ptr(nullptr), ref_count(new size_t(0)) {}

    ShPtr(T* p) : ptr(p), ref_count(new size_t(1)) {}

    ShPtr(const ShPtr<T>& other) : ptr(other.ptr), ref_count(other.ref_count) {
        addRef();
    }

    ShPtr<T>& operator=(const ShPtr<T>& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            addRef();
        }
        return *this;
    }

    ~ShPtr() {
        release();
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    size_t useCount() const {
        return *ref_count;
    }

    bool unique() const {
        return *ref_count == 1;
    }
};

int main() {
    setlocale(0, "ru");

    int value1, value2;

    cout << "Введите значение для первого smart-указателя: ";
    cin >> value1;
    ShPtr<int> sp1(new int(value1));
    cout << "Значение через sp1: " << *sp1 << endl;
    cout << "Счетчик ссылок: " << sp1.useCount() << endl;

    {
        cout << "Введите значение для второго smart-указателя: ";
        cin >> value2;
        ShPtr<int> sp2(new int(value2));
        cout << "Значение через sp2: " << *sp2 << endl;
        cout << "Счетчик ссылок sp2: " << sp2.useCount() << endl;

        cout << "Копируем sp1 в sp2..." << endl;
        sp2 = sp1;
        cout << "Значение через sp2 после копирования: " << *sp2 << endl;
        cout << "Счетчик ссылок sp1: " << sp1.useCount() << endl;
        cout << "Счетчик ссылок sp2: " << sp2.useCount() << endl;
    }

    cout << "Счетчик ссылок sp1 после выхода из области видимости sp2: " << sp1.useCount() << endl;

    return 0;
}
