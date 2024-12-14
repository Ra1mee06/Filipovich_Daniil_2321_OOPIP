#pragma once
#include "Node.h"
#include "SmartPointer.h"
#include "ExceptionHandler.h"

template <typename T>
class List {
private:
    ShPtr<Node<T>> head;
    ShPtr<Node<T>> tail;
    size_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    void push_front(const T& value) {
        ShPtr<Node<T>> newNode(new Node<T>(value));
        if (head.get() != nullptr) {
            head->prev = newNode.get();
            newNode->next = head.get();
        }
        else {
            tail = newNode;
        }
        head = newNode;
        ++size;
    }

    void push_back(const T& value) {
        ShPtr<Node<T>> newNode(new Node<T>(value));
        if (tail.get() != nullptr) {
            tail->next = newNode.get();
            newNode->prev = tail.get();
        }
        else {
            head = newNode;
        }
        tail = newNode;
        ++size;
    }

    T pop_front() {
        if (head.get() == nullptr) {
            throw ExceptionHandler("Список пуст");
        }
        T value = head->value;
        head = ShPtr<Node<T>>(head->next);
        if (head.get() != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        --size;
        return value;
    }

    void remove(const T& value) {
        Node<T>* current = head.get();
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                else {
                    head = ShPtr<Node<T>>(current->next);
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = ShPtr<Node<T>>(current->prev);
                }
                --size;
                return;
            }
            current = current->next;
        }
        throw ExceptionHandler("Элемент не найден");
    }

    size_t getSize() const { return size; }
};
