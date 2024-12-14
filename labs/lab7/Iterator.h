#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
    virtual ~Iterator() = default;
};

#endif
