#pragma once
#include <cstddef>
#include <utility>

template<class T>
class Array {
private:
    T* _data;
    size_t _size;
    size_t _capacity;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(_data[i]);
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

public:
    Array() : _data(nullptr), _size(0), _capacity(0) {}

    ~Array() { delete[] _data; }

    void push_back(T&& value) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = std::move(value);
    }

    void erase(size_t index) {
        if (index >= _size) return;
        for (size_t i = index; i < _size - 1; ++i) {
            _data[i] = std::move(_data[i + 1]);
        }
        --_size;
    }

    T& operator[](size_t index) { return _data[index]; }
    const T& operator[](size_t index) const { return _data[index]; }
    size_t size() const { return _size; }
};