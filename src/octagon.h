#pragma once
#include "figure.h"
#include <cmath>

template <Number T>
class Octagon : public Figure<T> {
private:
    Point<T>* vertices;
public:
    Octagon() : vertices(nullptr) {}
    explicit Octagon(const Point<T> p[8]) {
        vertices = new Point<T>[8];
        for (int i = 0; i < 8; ++i) vertices[i] = p[i];
    }
    ~Octagon() { delete[] vertices; }

    void get_center(T* outX, T* outY) const override {
        T x_sum=0, y_sum=0; for (int i=0; i<8; ++i) { x_sum+=vertices[i].X; y_sum+=vertices[i].Y; }
        *outX = x_sum / 8.0; *outY = y_sum / 8.0;
    }
    double get_area() const override {
        double val = 0;
        int i = 0;
        while(i < 8) {
            val += (vertices[i].X * vertices[(i + 1) % 8].Y) - (vertices[(i + 1) % 8].X * vertices[i].Y);
            i++;
        }
        return std::abs(val) / 2.0;
    }
    void print(std::ostream& os) const override {
        os << "Octagon: "; for (int i = 0; i < 8; ++i) os << vertices[i] << " ";
    }
};