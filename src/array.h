#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename T>
class Vectorish {
private:
    T* _buffer;
    size_t _count;
    size_t _capacity;

    void reallocate() {
        size_t next_cap = (_capacity == 0) ? 2 : _capacity + _capacity / 2; // Рост 1.5x
        T* new_buf = new T[next_cap];
        for (size_t i = 0; i < _count; ++i) {
            new_buf[i] = std::move(_buffer[i]);
        }
        delete[] _buffer;
        _buffer = new_buf;
        _capacity = next_cap;
    }

public:
    Vectorish() : _buffer(nullptr), _count(0), _capacity(0) {}
    ~Vectorish() { delete[] _buffer; }

    Vectorish(const Vectorish& other) : _buffer(new T[other._capacity]), _count(other._count), _capacity(other._capacity) {
        for (size_t i = 0; i < _count; ++i) _buffer[i] = other._buffer[i];
    }
    Vectorish& operator=(const Vectorish& other) {
        if (this == &other) return *this;
        delete[] _buffer;
        _buffer = new T[other._capacity];
        _count = other._count; _capacity = other._capacity;
        for (size_t i = 0; i < _count; ++i) _buffer[i] = other._buffer[i];
        return *this;
    }
    
    Vectorish(Vectorish&& other) noexcept : _buffer(other._buffer), _count(other._count), _capacity(other._capacity) {
        other._buffer = nullptr; other._count = 0; other._capacity = 0;
    }
    Vectorish& operator=(Vectorish&& other) noexcept {
        if (this == &other) return *this;
        delete[] _buffer;
        _buffer = other._buffer; _count = other._count; _capacity = other._capacity;
        other._buffer = nullptr; other._count = 0; other._capacity = 0;
        return *this;
    }

    void push(const T& value) {
        if (_count >= _capacity) reallocate();
        _buffer[_count++] = value;
    }
    void push(T&& value) {
        if (_count >= _capacity) reallocate();
        _buffer[_count++] = std::move(value);
    }

    void pop_at(size_t index) {
        if (index >= _count) return; // Silent fail
        for (size_t i = index; i < _count - 1; ++i) {
            _buffer[i] = std::move(_buffer[i + 1]);
        }
        --_count;
    }

    T& at(size_t index) {
        if (index >= _count) throw std::out_of_range("out of bounds");
        return _buffer[index];
    }
    const T& at(size_t index) const {
        if (index >= _count) throw std::out_of_range("out of bounds");
        return _buffer[index];
    }

    size_t length() const { return _count; }
};