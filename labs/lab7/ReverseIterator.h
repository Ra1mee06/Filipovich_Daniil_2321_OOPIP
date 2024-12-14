#ifndef REVERSEITERATOR_H
#define REVERSEITERATOR_H

#include <stdexcept>
#include "Iterator.h"
#include "Node.h"
#include <memory>

template <typename T>
class ReverseIterator : public Iterator<T> {
private:
    std::shared_ptr<Node<T>> current;

public:
    ReverseIterator(std::shared_ptr<Node<T>> start) : current(start) {}

    bool hasNext() const override {
        return current != nullptr;
    }

    T next() override {
        if (!current) {
            throw std::out_of_range("No more elements");
        }
        T value = current->value;
        current = current->prev.lock();
        return value;
    }
};

#endif

