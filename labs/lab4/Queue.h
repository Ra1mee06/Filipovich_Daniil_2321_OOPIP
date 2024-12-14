#pragma once
#include <initializer_list>
#include "ExceptionHandler.h"

namespace containers {

    template <typename T>
    class Queue {
    private:
        struct Node {
            T value;
            Node* next;
            Node(const T& val) : value(val), next(nullptr) {}
        };

        Node* head;
        Node* tail;
        size_t size;

    public:
        Queue() : head(nullptr), tail(nullptr), size(0) {}

        Queue(std::initializer_list<T> initList) : head(nullptr), tail(nullptr), size(0) {
            for (const auto& value : initList) {
                enqueue(value);
            }
        }

        Queue(const Queue& other) : head(nullptr), tail(nullptr), size(0) {
            Node* current = other.head;
            while (current) {
                enqueue(current->value);
                current = current->next;
            }
        }

        Queue& operator=(const Queue& other) {
            if (this != &other) {
                clear();
                Node* current = other.head;
                while (current) {
                    enqueue(current->value);
                    current = current->next;
                }
            }
            return *this;
        }

        Queue(Queue&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }

        Queue& operator=(Queue&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                size = other.size;
                other.head = nullptr;
                other.tail = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~Queue() {
            clear();
        }

        void enqueue(const T& value) {
            Node* newNode = new Node(value);
            if (tail) {
                tail->next = newNode;
            }
            else {
                head = newNode;
            }
            tail = newNode;
            ++size;
        }

        T dequeue() {
            if (isEmpty()) {
                throw ExceptionHandler("Очередь пуста");
            }
            Node* temp = head;
            T value = head->value;
            head = head->next;
            if (!head) {
                tail = nullptr;
            }
            delete temp;
            --size;
            return value;
        }

        T& operator[](size_t index) {
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                if (!current) {
                    enqueue(T());
                    current = tail;
                    break;
                }
                current = current->next;
            }
            return current->value;
        }

        bool isEmpty() const {
            return size == 0;
        }

        size_t getSize() const {
            return size;
        }

        void clear() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = nullptr;
            size = 0;
        }
    };
}
