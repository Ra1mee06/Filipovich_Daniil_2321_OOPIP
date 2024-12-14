#pragma once
#include <cstddef>

template <typename T>
class ShPtr {
private:
    T* ptr;
    size_t* ref_count;

    void release() {
        if (ref_count) {
            --(*ref_count);
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
    }

public:
    ShPtr() : ptr(nullptr), ref_count(new size_t(1)) {}

    explicit ShPtr(T* p) : ptr(p), ref_count(new size_t(1)) {}

    ShPtr(const ShPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    ShPtr& operator=(const ShPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    ShPtr(ShPtr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    ShPtr& operator=(ShPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    ~ShPtr() {
        release();
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    void reset() {
        release();
        ptr = nullptr;
        ref_count = new size_t(1);
    }

    void swap(ShPtr& other) {
        std::swap(ptr, other.ptr);
        std::swap(ref_count, other.ref_count);
    }

    T* get() const { return ptr; }

    size_t use_count() const { return ref_count ? *ref_count : 0; }

    ShPtr& operator=(std::nullptr_t) {
        release();
        ptr = nullptr;
        ref_count = new size_t(1);
        return *this;
    }
};
