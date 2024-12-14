#pragma once

template <typename T>
struct Node {
    T value;
    Node* prev;
    Node* next;
    Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
};
