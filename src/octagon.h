#pragma once
#include "figure.h"
#include <memory>
#include <cmath>
#include <utility>

template <NumericType T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> _vertices;

public:
    Octagon() : _vertices(nullptr) {}
    explicit Octagon(const Point<T> p[8]) : _vertices(new Point<T>[8]) {
        for (size_t i = 0; i < 8; ++i) _vertices[i] = p[i];
    }
    Point<T> calculate_center() const override {
        if (!_vertices) return {0,0};
        T total_x = 0, total_y = 0;
        for (size_t i = 0; i < 8; ++i) { total_x += _vertices[i].x; total_y += _vertices[i].y; }
        return {total_x / 8.0, total_y / 8.0};
    }
    double calculate_area() const override {
        if (!_vertices) return 0.0;
        double area = 0.0;
        for (size_t i = 0; i < 8; ++i) {
            Point<T> p1 = _vertices[i];
            Point<T> p2 = _vertices[(i + 1) % 8];
            area += (p1.x * p2.y) - (p2.x * p1.y);
        }
        return std::abs(area) / 2.0;
    }
    void display(std::ostream& os) const override {
        if (!_vertices) { os << "Empty Octagon"; return; }
        os << "Octagon with points: ";
        for (size_t i = 0; i < 8; ++i) os << _vertices[i] << (i == 7 ? "" : " ");
    }
};