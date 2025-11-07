#pragma once

#include "figure.h"
#include <memory>
#include <cmath>

template <Scalar T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> vertices;

public:
    Octagon(const Point<T> p[8]) : vertices(new Point<T>[8]) {
        for (size_t i = 0; i < 8; ++i) {
            vertices[i] = p[i];
        }
    }

    Octagon(const Octagon<T>& other) : vertices(new Point<T>[8]) {
        for (size_t i = 0; i < 8; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    
    Octagon<T>& operator=(const Octagon<T>& other) {
        if (this != &other) {
            vertices.reset(new Point<T>[8]);
            for (size_t i = 0; i < 8; ++i) {
                vertices[i] = other.vertices[i];
            }
        }
        return *this;
    }

    Point<T> center() const override {
        T sumX = 0, sumY = 0;
        for (size_t i = 0; i < 8; ++i) {
            sumX += vertices[i].x;
            sumY += vertices[i].y;
        }
        return {sumX / 8.0, sumY / 8.0};
    }

    double area() const override {
        double currentArea = 0.0;
        for (size_t i = 0; i < 8; ++i) {
            Point<T> p1 = vertices[i];
            Point<T> p2 = vertices[(i + 1) % 8];
            currentArea += (double)(p1.x * p2.y - p2.x * p1.y);
        }
        return std::abs(currentArea) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Octagon: [";
        for (size_t i = 0; i < 8; ++i) {
            os << vertices[i] << (i == 7 ? "" : ", ");
        }
        os << "]";
    }
};