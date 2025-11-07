#pragma once
#include "figure.h"
#include <memory>
#include <cmath>

template <IsNumber T>
class Octagon : public GeometricFigure<T> {
private:
    std::unique_ptr<Point2D<T>[]> m_points;
public:
    Octagon() : m_points(nullptr) {}
    explicit Octagon(const Point2D<T> p[8]) : m_points(std::make_unique<Point2D<T>[]>(8)) {
        for (size_t i = 0; i < 8; ++i) m_points[i] = p[i];
    }
    Point2D<T> getCenter() const override {
        T sx = 0, sy = 0; for (size_t i = 0; i < 8; ++i) { sx += m_points[i].x; sy += m_points[i].y; }
        return {sx / 8.0, sy / 8.0};
    }
    double getArea() const override {
        double area_val = 0;
        for (size_t i = 0; i < 8; ++i) {
            area_val += (m_points[i].x * m_points[(i + 1) % 8].y) - (m_points[(i + 1) % 8].x * m_points[i].y);
        }
        return std::abs(area_val) / 2.0;
    }
    void printDescription(std::ostream& os) const override {
        os << "Octagon, points: "; for (size_t i = 0; i < 8; ++i) os << m_points[i] << " ";
    }
};