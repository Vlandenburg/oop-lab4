#pragma once

#include "figure.h"
#include <memory>
#include <cmath>

template <Scalar T>
class Hexagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> vertices;

public:
    Hexagon(const Point<T> p[6]) : vertices(new Point<T>[6]) {
        for (size_t i = 0; i < 6; ++i) {
            vertices[i] = p[i];
        }
    }

    Hexagon(const Hexagon<T>& other) : vertices(new Point<T>[6]) {
        for (size_t i = 0; i < 6; ++i) {
            vertices[i] = other.vertices[i];
        }
    }

    Hexagon<T>& operator=(const Hexagon<T>& other) {
        if (this != &other) {
            vertices.reset(new Point<T>[6]);
            for (size_t i = 0; i < 6; ++i) {
                vertices[i] = other.vertices[i];
            }
        }
        return *this;
    }

    Point<T> center() const override {
        T sumX = 0, sumY = 0;
        for (size_t i = 0; i < 6; ++i) {
            sumX += vertices[i].x;
            sumY += vertices[i].y;
        }
        return {sumX / 6.0, sumY / 6.0};
    }

    double area() const override {
        double currentArea = 0.0;
        for (size_t i = 0; i < 6; ++i) {
            Point<T> p1 = vertices[i];
            Point<T> p2 = vertices[(i + 1) % 6];
            currentArea += (double)(p1.x * p2.y - p2.x * p1.y);
        }
        return std::abs(currentArea) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Hexagon: [";
        for (size_t i = 0; i < 6; ++i) {
            os << vertices[i] << (i == 5 ? "" : ", ");
        }
        os << "]";
    }
};