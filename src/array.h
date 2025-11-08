#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>

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

    Array(const Array& other) : _size(other._size), _capacity(other._capacity) {
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }

    Array(Array&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._capacity;
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    ~Array() { delete[] _data; }

    void push_back(const T& value) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = value;
    }

    void push_back(T&& value) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = std::move(value);
    }

    void erase(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < _size - 1; ++i) {
            _data[i] = std::move(_data[i + 1]);
        }
        --_size;
    }

    T& operator[](size_t index) { return _data[index]; }
    const T& operator[](size_t index) const { return _data[index]; }
    size_t size() const { return _size; }
};