#pragma once
#include "figure.h"
#include <memory>
#include <cmath>

template <IsNumber T>
class Hexagon : public GeometricFigure<T> {
private:
    std::unique_ptr<Point2D<T>[]> m_points;
public:
    Hexagon() : m_points(nullptr) {}
    explicit Hexagon(const Point2D<T> p[6]) : m_points(std::make_unique<Point2D<T>[]>(6)) {
        for (size_t i = 0; i < 6; ++i) m_points[i] = p[i];
    }
    Point2D<T> getCenter() const override {
        T sx = 0, sy = 0; for (size_t i = 0; i < 6; ++i) { sx += m_points[i].x; sy += m_points[i].y; }
        return {sx / 6.0, sy / 6.0};
    }
    double getArea() const override {
        double area_val = 0;
        for (size_t i = 0; i < 6; ++i) {
            area_val += (m_points[i].x * m_points[(i + 1) % 6].y) - (m_points[(i + 1) % 6].x * m_points[i].y);
        }
        return std::abs(area_val) * 0.5;
    }
    void printDescription(std::ostream& os) const override {
        os << "Hexagon, points: "; for (size_t i = 0; i < 6; ++i) os << m_points[i] << " ";
    }
};