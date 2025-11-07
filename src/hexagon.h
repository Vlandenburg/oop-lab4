#pragma once
#include "figure.h"
#include <memory>
#include <cmath>
#include <utility>

template <NumericType T>
class Hexagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> _vertices;

public:
    Hexagon() : _vertices(nullptr) {}
    explicit Hexagon(const Point<T> p[6]) : _vertices(new Point<T>[6]) {
        size_t i = 0;
        while (i < 6) { _vertices[i] = p[i]; i++; }
    }
    Point<T> calculate_center() const override {
        if (!_vertices) return {0,0};
        T x_total = 0, y_total = 0;
        for (size_t i = 0; i < 6; ++i) { x_total += _vertices[i].x; y_total += _vertices[i].y; }
        return {x_total / 6.0, y_total / 6.0};
    }
    double calculate_area() const override {
        if (!_vertices) return 0.0;
        double area = 0.0;
        for (size_t i = 0; i < 6; ++i) {
            area += (_vertices[i].x * _vertices[(i + 1) % 6].y) - (_vertices[(i + 1) % 6].x * _vertices[i].y);
        }
        return std::abs(area) / 2.0;
    }
    void display(std::ostream& os) const override {
        if (!_vertices) { os << "Empty Hexagon"; return; }
        os << "Hexagon with points: ";
        for (size_t i = 0; i < 6; ++i) os << _vertices[i] << (i == 5 ? "" : " ");
    }
};