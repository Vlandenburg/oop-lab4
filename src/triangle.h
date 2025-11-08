#pragma once
#include "figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>

template<is_numeric T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> _vertices;
    static const size_t VERTEX_COUNT = 3;

public:
    Triangle() : _vertices(std::make_unique<Point<T>[]>(VERTEX_COUNT)) {}

    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) : _vertices(std::make_unique<Point<T>[]>(VERTEX_COUNT)) {
        _vertices[0] = p1;
        _vertices[1] = p2;
        _vertices[2] = p3;
    }

    Triangle(const Triangle<T>& other) : _vertices(std::make_unique<Point<T>[]>(VERTEX_COUNT)) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            _vertices[i] = other._vertices[i];
        }
    }

    Triangle(Triangle<T>&& other) noexcept = default;

    Triangle<T>& operator=(const Triangle<T>& other) {
        if (this != &other) {
            for (size_t i = 0; i < VERTEX_COUNT; ++i) {
                _vertices[i] = other._vertices[i];
            }
        }
        return *this;
    }

    Triangle<T>& operator=(Triangle<T>&& other) noexcept = default;

    bool operator==(const Triangle<T>& other) const {
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
        return 0.5 * std::abs(_vertices[0].x * (_vertices[1].y - _vertices[2].y) +
                               _vertices[1].x * (_vertices[2].y - _vertices[0].y) +
                               _vertices[2].x * (_vertices[0].y - _vertices[1].y));
    }

    void print(std::ostream& os) const override {
        os << "Triangle";
    }

    void print_vertices(std::ostream& os) const override {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            os << _vertices[i] << (i == VERTEX_COUNT - 1 ? "" : ", ");
        }
    }
};