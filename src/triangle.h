#pragma once
#include "figure.h"
#include <cmath>

template<is_numeric T>
class Triangle : public Figure<T> {
private:
    Point<T> _vertices[3];

public:
    Triangle() = default;
    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        _vertices[0] = p1;
        _vertices[1] = p2;
        _vertices[2] = p3;
    }

    Point<T> center() const override {
        T sx = _vertices[0].x + _vertices[1].x + _vertices[2].x;
        T sy = _vertices[0].y + _vertices[1].y + _vertices[2].y;
        return {sx / 3, sy / 3};
    }

    double area() const override {
        return 0.5 * std::abs(_vertices[0].x * (_vertices[1].y - _vertices[2].y) +
                               _vertices[1].x * (_vertices[2].y - _vertices[0].y) +
                               _vertices[2].x * (_vertices[0].y - _vertices[1].y));
    }

    void print(std::ostream& os) const override {
        os << "Triangle: " << _vertices[0] << ", " << _vertices[1] << ", " << _vertices[2];
    }
};