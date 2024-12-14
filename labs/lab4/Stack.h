#pragma once
#include "List.h"
#include "ExceptionHandler.h"

template <typename T>
class Stack {
private:
    List<T> list;

public:
    Stack() = default;

    Stack(std::initializer_list<T> initList) {
        for (const auto& value : initList) {
            push(value);
        }
    }

    Stack(const Stack& other) : list(other.list) {}

    Stack& operator=(const Stack& other) {
        if (this == &other) return *this;
        list = other.list;
        return *this;
    }

    Stack(Stack&& other) noexcept : list(std::move(other.list)) {}

    Stack& operator=(Stack&& other) noexcept {
        if (this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    void push(const T& value) {
        list.push_front(value);
    }

    T pop() {
        return list.pop_front();
    }

    void remove(const T& value) {
        list.remove(value);
    }

    size_t getSize() const { return list.getSize(); }

    bool isEmpty() const { return list.getSize() == 0; }
};
