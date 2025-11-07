#pragma once
#include "figure.h"
#include <cmath>

template <Number T>
class Hexagon : public Figure<T> {
private:
    Point<T>* points;
public:
    Hexagon() : points(nullptr) {}
    explicit Hexagon(const Point<T> p[6]) {
        points = new Point<T>[6];
        for (int i = 0; i < 6; ++i) points[i] = p[i];
    }
    ~Hexagon() { delete[] points; }

    void get_center(T* outX, T* outY) const override {
        T x=0, y=0; for (int i=0; i<6; ++i) { x+=points[i].X; y+=points[i].Y; }
        *outX = x / 6.; *outY = y / 6.;
    }
    double get_area() const override {
        double area = 0;
        for (int i=0; i<6; ++i) {
            area += (points[i].X * points[(i + 1) % 6].Y) - (points[(i + 1) % 6].X * points[i].Y);
        }
        return std::abs(area) * 0.5;
    }
    void print(std::ostream& os) const override {
        os << "Hexagon: "; for (int i = 0; i < 6; ++i) os << points[i] << " ";
    }
};