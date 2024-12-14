#include <iostream>
#include <map>

using namespace std;

namespace containers {

    template <typename T>
    class SparseArr {
    public:
        SparseArr(size_t size) : logicalSize(size) {}

        void set(size_t index, const T& value) {
            if (index >= logicalSize) {
                throw out_of_range("Индекс вне диапазона");
            }
            if (value != T{}) {
                data[index] = value;
            }
            else {
                data.erase(index);
            }
        }

        T get(size_t index) const {
            if (index >= logicalSize) {
                throw out_of_range("Индекс вне диапазона");
            }
            auto it = data.find(index);
            return it != data.end() ? it->second : T{};
        }

        size_t size() const {
            return logicalSize;
        }

        size_t nonZeroCount() const {
            return data.size();
        }

    private:
        size_t logicalSize;
        map<size_t, T> data;
    };

    template <typename T>
    class Queue {
    public:
        Queue() : front(nullptr), rear(nullptr), count(0) {}

        ~Queue() {
            while (!isEmpty()) {
                dequeue();
            }
        }

        void enqueue(const T& value) {
            Node* newNode = new Node(value);
            if (rear) {
                rear->next = newNode;
            }
            else {
                front = newNode;
            }
            rear = newNode;
            ++count;
        }

        T dequeue() {
            if (isEmpty()) {
                throw out_of_range("Очередь пуста");
            }
            Node* temp = front;
            T value = temp->data;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
            --count;
            return value;
        }

        bool isEmpty() const {
            return count == 0;
        }

        size_t size() const {
            return count;
        }

    private:
        struct Node {
            T data;
            Node* next;

            Node(const T& value) : data(value), next(nullptr) {}
        };

        Node* front;
        Node* rear;
        size_t count;
    };
}

int main() {
    setlocale(LC_ALL, "Russian");
    using namespace containers;

    Queue<int> queue;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент в очередь\n";
        cout << "2. Извлечь элемент из очереди\n";
        cout << "3. Проверить, пуста ли очередь\n";
        cout << "4. Показать размер очереди\n";
        cout << "5. Выход\n";
        cout << "Выберите опцию: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Введите значение: ";
            cin >> value;
            queue.enqueue(value);
            cout << "Элемент добавлен в очередь.\n";
            break;
        }
        case 2: {
            try {
                int value = queue.dequeue();
                cout << "Извлечённый элемент: " << value << "\n";
            }
            catch (const out_of_range& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            cout << (queue.isEmpty() ? "Очередь пуста" : "Очередь не пуста") << "\n";
            break;
        }
        case 4: {
            cout << "Размер очереди: " << queue.size() << "\n";
            break;
        }
        case 5: {
            cout << "Выход из программы.\n";
            return 0;
        }
        default: {
            cout << "Неверная опция. Попробуйте снова.\n";
            break;
        }
        }
    }

    return 0;
}
