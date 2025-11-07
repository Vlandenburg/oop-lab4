// src/triangle.h

#pragma once

#include "figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <utility> // <-- Добавьте для std::move

template <Scalar T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> vertices;

    static double calculate_area(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
         return 0.5 * std::abs(
            p1.x * (p2.y - p3.y) +
            p2.x * (p3.y - p1.y) +
            p3.x * (p1.y - p2.y)
        );
    }

public:
    

    
    Triangle() : vertices(nullptr) {}

    

    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        if (calculate_area(p1, p2, p3) < 1e-9) {
            throw std::invalid_argument("Points are collinear, cannot form a triangle.");
        }
        vertices = std::make_unique<Point<T>[]>(3);
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
    }

    Triangle(const Triangle<T>& other) : vertices(new Point<T>[3]) {
        for (size_t i = 0; i < 3; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    
    

    
    Triangle(Triangle<T>&& other) noexcept : vertices(std::move(other.vertices)) {}

    
    Triangle<T>& operator=(Triangle<T>&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }

    

    Triangle<T>& operator=(const Triangle<T>& other) {
        if (this != &other) {
            vertices.reset(new Point<T>[3]);
            for (size_t i = 0; i < 3; ++i) {
                vertices[i] = other.vertices[i];
            }
        }
        return *this;
    }

    Point<T> center() const override {
        if (!vertices) return {0,0}; // Защита для объектов по умолчанию
        T centerX = (vertices[0].x + vertices[1].x + vertices[2].x) / 3.0;
        T centerY = (vertices[0].y + vertices[1].y + vertices[2].y) / 3.0;
        return {centerX, centerY};
    }

    double area() const override {
        if (!vertices) return 0.0; // Защита для объектов по умолчанию
        return calculate_area(vertices[0], vertices[1], vertices[2]);
    }

    void print(std::ostream& os) const override {
        if (!vertices) {
            os << "Triangle: [empty]";
            return;
        }
        os << "Triangle: [" << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << "]";
    }
};