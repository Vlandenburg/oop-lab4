#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>

template <class Item>
class CustomArray {
private:
    Item* m_data;
    size_t m_size;
    size_t m_capacity;

    void resize_storage() {
        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity + m_capacity / 2 + 1; // Рост ~1.5x
        Item* new_block = new Item[new_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            new_block[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = new_block;
        m_capacity = new_capacity;
    }

public:
    CustomArray() : m_data(nullptr), m_size(0), m_capacity(0) {}
    ~CustomArray() { delete[] m_data; }

    CustomArray(const CustomArray& other) : m_data(new Item[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) {
        for (size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
    }
    CustomArray& operator=(const CustomArray& other) {
        if (this == &other) return *this;
        delete[] m_data;
        m_data = new Item[other.m_capacity];
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        for (size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
        return *this;
    }
    
    CustomArray(CustomArray&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.m_data = nullptr; other.m_size = 0; other.m_capacity = 0;
    }
    CustomArray& operator=(CustomArray&& other) noexcept {
        if (this == &other) return *this;
        delete[] m_data;
        m_data = other.m_data; m_size = other.m_size; m_capacity = other.m_capacity;
        other.m_data = nullptr; other.m_size = 0; other.m_capacity = 0;
        return *this;
    }

    void add(const Item& value) {
        if (m_size >= m_capacity) resize_storage();
        m_data[m_size++] = value;
    }
    void add(Item&& value) {
        if (m_size >= m_capacity) resize_storage();
        m_data[m_size++] = std::move(value);
    }

    void remove_at(size_t index) {
        if (index >= m_size) throw std::out_of_range("Bad index provided");
        for (size_t i = index; i < m_size - 1; ++i) {
            m_data[i] = std::move(m_data[i + 1]);
        }
        --m_size;
    }

    Item& get(size_t index) {
        if (index >= m_size) throw std::out_of_range("Bad index provided");
        return m_data[index];
    }
    const Item& get(size_t index) const {
        if (index >= m_size) throw std::out_of_range("Bad index provided");
        return m_data[index];
    }

    size_t count() const { return m_size; }
};