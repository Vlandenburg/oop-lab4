#pragma once

#include <cstddef>
#include <utility>
#include <stdexcept>

template <class T>
class Array {
private:
    T* elements;
    size_t count;
    size_t storage_size;

    void expand_storage(size_t new_cap) {
        T* new_elements = new T[new_cap];
        for (size_t i = 0; i < count; ++i) {
            new_elements[i] = std::move(elements[i]);
        }
        delete[] elements;
        elements = new_elements;
        storage_size = new_cap;
    }

public:
    Array() : elements(nullptr), count(0), storage_size(0) {}

    ~Array() {
        delete[] elements;
    }

    Array(const Array& other) : elements(new T[other.storage_size]), count(other.count), storage_size(other.storage_size) {
        for (size_t i = 0; i < count; ++i) {
            elements[i] = other.elements[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] elements;
            elements = new T[other.storage_size];
            count = other.count;
            storage_size = other.storage_size;
            for (size_t i = 0; i < count; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }
    
    Array(Array&& other) noexcept : elements(other.elements), count(other.count), storage_size(other.storage_size) {
        other.elements = nullptr;
        other.count = 0;
        other.storage_size = 0;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] elements;
            elements = other.elements;
            count = other.count;
            storage_size = other.storage_size;
            other.elements = nullptr;
            other.count = 0;
            other.storage_size = 0;
        }
        return *this;
    }

    void push_back(const T& val) {
        if (count == storage_size) {
            expand_storage(storage_size == 0 ? 1 : storage_size * 2);
        }
        elements[count++] = val;
    }

    void push_back(T&& val) {
        if (count == storage_size) {
            expand_storage(storage_size == 0 ? 1 : storage_size * 2);
        }
        elements[count++] = std::move(val);
    }

    void erase(size_t idx) {
        if (idx >= count) {
            throw std::out_of_range("Index is out of array bounds");
        }
        for (size_t i = idx; i < count - 1; ++i) {
            elements[i] = std::move(elements[i + 1]);
        }
        --count;
    }

    T& operator[](size_t idx) {
        if (idx >= count) {
            throw std::out_of_range("Index is out of array bounds");
        }
        return elements[idx];
    }

    const T& operator[](size_t idx) const {
        if (idx >= count) {
            throw std::out_of_range("Index is out of array bounds");
        }
        return elements[idx];
    }

    size_t size() const {
        return count;
    }
};