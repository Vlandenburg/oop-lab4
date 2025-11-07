#pragma once
#include "figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <utility>

template <NumericType T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> _vertices;

public:
    Triangle() : _vertices(nullptr) {}
    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        if (0.5 * std::abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) < 1e-9) {
            throw std::invalid_argument("Points are on a line.");
        }
        _vertices = std::make_unique<Point<T>[]>(3);
        _vertices[0] = p1; _vertices[1] = p2; _vertices[2] = p3;
    }
    Triangle(const Triangle& other) : _vertices(new Point<T>[3]) {
        for (size_t i = 0; i < 3; ++i) _vertices[i] = other._vertices[i];
    }
    Triangle(Triangle&& other) noexcept : _vertices(std::move(other._vertices)) {}
    Triangle& operator=(Triangle&& other) noexcept {
        if (this != &other) _vertices = std::move(other._vertices);
        return *this;
    }
    Triangle& operator=(const Triangle& other) {
        if (this == &other) return *this;
        _vertices.reset(new Point<T>[3]);
        for (size_t i = 0; i < 3; ++i) _vertices[i] = other._vertices[i];
        return *this;
    }

    Point<T> calculate_center() const override {
        if (!_vertices) return {0,0};
        T totalX = _vertices[0].x + _vertices[1].x + _vertices[2].x;
        T totalY = _vertices[0].y + _vertices[1].y + _vertices[2].y;
        return {totalX / 3.0, totalY / 3.0};
    }
    double calculate_area() const override {
        if (!_vertices) return 0.0;
        return 0.5 * std::abs(_vertices[0].x * (_vertices[1].y - _vertices[2].y) + _vertices[1].x * (_vertices[2].y - _vertices[0].y) + _vertices[2].x * (_vertices[0].y - _vertices[1].y));
    }
    void display(std::ostream& stream) const override {
        if (!_vertices) { stream << "Empty Triangle"; return; }
        stream << "Triangle with points: " << _vertices[0] << ", " << _vertices[1] << ", " << _vertices[2];
    }
};