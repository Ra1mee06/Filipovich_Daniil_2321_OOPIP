#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include "SmartPointer.h"
#include "ForwardIterator.h"
#include "ReverseIterator.h"
#include <initializer_list>
#include <stdexcept>
#include <memory>

using namespace std;

template <typename T>
class List {
private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    size_t size;

public:

    List() : head(nullptr), tail(nullptr), size(0) {}

    List(initializer_list<T> init) : List() {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    List(const List& other) : List() {
        for (auto node = other.head; node; node = node->next) {
            push_back(node->value);
        }
    }

    List& operator=(const List& other) {
        if (this == &other) return *this;
        clear();
        for (auto node = other.head; node; node = node->next) {
            push_back(node->value);
        }
        return *this;
    }

    List(List&& other) noexcept : head(std::move(other.head)), tail(std::move(other.tail)), size(other.size) {
        other.size = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this == &other) return *this;
        clear();
        head = move(other.head);
        tail = move(other.tail);
        size = other.size;
        other.size = 0;
        return *this;
    }

    ~List() {
        clear();
    }

    void push_back(const T& value) {
        auto newNode = make_shared<Node<T>>(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void pop_back() {
        if (!tail) {
            throw out_of_range("List is empty");
        }
        tail = tail->prev.lock();
        if (tail) {
            tail->next.reset();
        }
        else {
            head.reset();
        }
        size--;
    }

    shared_ptr<Node<T>> getHead() const {
        return head;
    }

    void clear() {
        head.reset();
        tail.reset();
        size = 0;
    }

    size_t getSize() const {
        return size;
    }

    unique_ptr<Iterator<T>> createForwardIterator() const {
        return make_unique<ForwardIterator<T>>(head);
    }

    unique_ptr<Iterator<T>> createReverseIterator() const {
        return make_unique<ReverseIterator<T>>(tail);
    }
};

#endif
