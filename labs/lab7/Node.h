#ifndef NODE_H
#define NODE_H

#include <memory>
using namespace std;

template <typename T>
struct Node {
    T value;
    shared_ptr<Node<T>> next;
    weak_ptr<Node<T>> prev;

    Node(const T& val) : value(val), next(nullptr), prev() {}
};

#endif 

