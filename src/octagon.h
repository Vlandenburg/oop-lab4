#pragma once
#include "figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>

template<is_numeric T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> _vertices;
    static const size_t VERTEX_COUNT = 8;

public:
    Octagon() : _vertices(std::make_unique<Point<T>[]>(VERTEX_COUNT)) {}
    
    explicit Octagon(const Point<T> p[VERTEX_COUNT]) : _vertices(std::make_unique<Point<T>[]>(VERTEX_COUNT)) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) _vertices[i] = p[i];
    }
    
    Octagon(const Octagon<T>& other) : _vertices(std::make_unique<Point<T>[]>(VERTEX_COUNT)) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            _vertices[i] = other._vertices[i];
        }
    }
    
    Octagon(Octagon<T>&& other) noexcept = default;

    Octagon<T>& operator=(const Octagon<T>& other) {
        if (this != &other) {
            for (size_t i = 0; i < VERTEX_COUNT; ++i) {
                _vertices[i] = other._vertices[i];
            }
        }
        return *this;
    }

    Octagon<T>& operator=(Octagon<T>&& other) noexcept = default;

    bool operator==(const Octagon<T>& other) const {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            bool found = false;
            for (size_t j = 0; j < VERTEX_COUNT; ++j) {
                if (_vertices[i] == other._vertices[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }

    Point<T> center() const override {
        T sx = 0, sy = 0;
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            sx += _vertices[i].x;
            sy += _vertices[i].y;
        }
        return {sx / VERTEX_COUNT, sy / VERTEX_COUNT};
    }

    double area() const override {
        double current_area = 0.0;
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            current_area += (_vertices[i].x * _vertices[(i + 1) % VERTEX_COUNT].y) - (_vertices[(i + 1) % VERTEX_COUNT].x * _vertices[i].y);
        }
        return std::abs(current_area) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Octagon";
    }

    void print_vertices(std::ostream& os) const override {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            os << _vertices[i] << (i == VERTEX_COUNT - 1 ? "" : ", ");
        }
    }
};