#pragma once
#include "figure.h"
#include <cmath>

template<is_numeric T>
class Octagon : public Figure<T> {
private:
    Point<T> _vertices[8];

public:
    Octagon() = default;
    explicit Octagon(const Point<T> p[8]) {
        for (int i = 0; i < 8; ++i) _vertices[i] = p[i];
    }

    Point<T> center() const override {
        T sx = 0, sy = 0;
        for(int i = 0; i < 8; ++i) { sx += _vertices[i].x; sy += _vertices[i].y; }
        return {sx / 8, sy / 8};
    }

    double area() const override {
        double current_area = 0.0;
        for (int i = 0; i < 8; ++i) {
            current_area += (_vertices[i].x * _vertices[(i + 1) % 8].y) - (_vertices[(i + 1) % 8].x * _vertices[i].y);
        }
        return std::abs(current_area) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Octagon: ";
        for (int i = 0; i < 8; ++i) os << _vertices[i] << (i == 7 ? "" : ", ");
    }
};