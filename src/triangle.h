#pragma once
#include "figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <utility>

template <IsNumber ValType>
class Triangle : public GeometricFigure<ValType> {
private:
    std::unique_ptr<Point2D<ValType>[]> m_points;

public:
    Triangle() : m_points(nullptr) {}
    Triangle(const Point2D<ValType>& a, const Point2D<ValType>& b, const Point2D<ValType>& c) {
        m_points = std::make_unique<Point2D<ValType>[]>(3);
        Point2D<ValType> temp_pts[] = {a, b, c};
        for(int i = 0; i < 3; ++i) m_points[i] = temp_pts[i];
    }

    Point2D<ValType> getCenter() const override {
        if (!m_points) return {0,0};
        auto x_sum = m_points[0].x + m_points[1].x + m_points[2].x;
        auto y_sum = m_points[0].y + m_points[1].y + m_points[2].y;
        return {x_sum / 3.0, y_sum / 3.0};
    }
    double getArea() const override {
        if (!m_points) return 0.0;
        auto p1 = m_points[0]; auto p2 = m_points[1]; auto p3 = m_points[2];
        return 0.5 * std::abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    }
    void printDescription(std::ostream& os) const override {
        if (!m_points) { os << "Triangle (uninitialized)"; return; }
        os << "Triangle, points: " << m_points[0] << m_points[1] << m_points[2];
    }
};