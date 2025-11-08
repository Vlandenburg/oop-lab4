#pragma once
#include "figure.h"
#include <cmath>

template<is_numeric T>
class Hexagon : public Figure<T> {
private:
    Point<T> _vertices[6];

public:
    Hexagon() = default;
    explicit Hexagon(const Point<T> p[6]) {
        for (int i = 0; i < 6; ++i) _vertices[i] = p[i];
    }

    Point<T> center() const override {
        T sx = 0, sy = 0;
        for(int i = 0; i < 6; ++i) { sx += _vertices[i].x; sy += _vertices[i].y; }
        return {sx / 6, sy / 6};
    }

    double area() const override {
        double current_area = 0.0;
        for (int i = 0; i < 6; ++i) {
            current_area += (_vertices[i].x * _vertices[(i + 1) % 6].y) - (_vertices[(i + 1) % 6].x * _vertices[i].y);
        }
        return std::abs(current_area) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Hexagon: ";
        for (int i = 0; i < 6; ++i) os << _vertices[i] << (i == 5 ? "" : ", ");
    }
};