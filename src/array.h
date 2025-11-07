#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>

template <class Elem>
class Storage {
private:
    Elem* _elements;
    size_t _size;
    size_t _cap;

public:
    Storage() : _elements(nullptr), _size(0), _cap(0) {}
    ~Storage() { delete[] _elements; }

    void add(Elem&& value) {
        if (_size >= _cap) {
            size_t new_cap = _cap == 0 ? 4 : _cap * 2;
            Elem* new_storage = new Elem[new_cap];
            for (size_t i = 0; i < _size; ++i) new_storage[i] = std::move(_elements[i]);
            delete[] _elements;
            _elements = new_storage;
            _cap = new_cap;
        }
        *(_elements + _size) = std::move(value);
        _size++;
    }

    void remove(size_t index) {
        if (index >= _size) return;
        for (size_t i = index; i < _size - 1; ++i) _elements[i] = std::move(_elements[i + 1]);
        --_size;
    }

    Elem& operator[](size_t index) { return _elements[index]; }
    const Elem& operator[](size_t index) const { return _elements[index]; }
    size_t count() const { return _size; }
};