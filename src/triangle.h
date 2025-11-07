#pragma once

#include "figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <utility>

template <IsArithmetic T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> points_;

    static double calc_s(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        double part1 = a.x * (b.y - c.y);
        double part2 = b.x * (c.y - a.y);
        double part3 = c.x * (a.y - b.y);
        return 0.5 * std::abs(part1 + part2 + part3);
    }

public:
    Triangle() : points_(nullptr) {}

    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        if (calc_s(p1, p2, p3) < 1e-9) {
            throw std::invalid_argument("Cannot form a triangle, points are on the same line.");
        }
        points_ = std::make_unique<Point<T>[]>(3);
        points_[0] = p1;
        points_[1] = p2;
        points_[2] = p3;
    }

    Triangle(const Triangle<T>& src) : points_(new Point<T>[3]) {
        for (size_t i = 0; i < 3; ++i) {
            points_[i] = src.points_[i];
        }
    }
    
    Triangle(Triangle<T>&& src) noexcept : points_(std::move(src.points_)) {}

    Triangle<T>& operator=(Triangle<T>&& src) noexcept {
        if (this != &src) {
            points_ = std::move(src.points_);
        }
        return *this;
    }

    Triangle<T>& operator=(const Triangle<T>& src) {
        if (this != &src) {
            points_.reset(new Point<T>[3]);
            for (size_t i = 0; i < 3; ++i) {
                points_[i] = src.points_[i];
            }
        }
        return *this;
    }

    Point<T> center() const override {
        if (!points_) return {0,0};
        T cx = (points_[0].x + points_[1].x + points_[2].x) / 3.0;
        T cy = (points_[0].y + points_[1].y + points_[2].y) / 3.0;
        return {cx, cy};
    }

    double area() const override {
        if (!points_) return 0.0;
        return calc_s(points_[0], points_[1], points_[2]);
    }

    void print(std::ostream& stream) const override {
        if (!points_) {
            stream << "Triangle: [empty]";
            return;
        }
        stream << "Triangle: [" << points_[0] << ", " << points_[1] << ", " << points_[2] << "]";
    }
};