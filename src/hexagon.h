#pragma once

#include "figure.h"
#include <memory>
#include <cmath>
#include <utility>

template <IsArithmetic T>
class Hexagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> points_;

public:
    Hexagon() : points_(nullptr) {}

    Hexagon(const Point<T> p[6]) : points_(new Point<T>[6]) {
        for (size_t i = 0; i < 6; ++i) { points_[i] = p[i]; }
    }
    
    Hexagon(const Hexagon<T>& src) : points_(new Point<T>[6]) {
        if (src.points_) {
            for (size_t i = 0; i < 6; ++i) {
                points_[i] = src.points_[i];
            }
        }
    }
    
    Hexagon(Hexagon<T>&& src) noexcept : points_(std::move(src.points_)) {}

    Hexagon<T>& operator=(const Hexagon<T>& src) {
        if (this != &src) {
            points_.reset(new Point<T>[6]);
            if (src.points_) {
                for (size_t i = 0; i < 6; ++i) {
                    points_[i] = src.points_[i];
                }
            }
        }
        return *this;
    }

    Hexagon<T>& operator=(Hexagon<T>&& src) noexcept {
        if (this != &src) {
            points_ = std::move(src.points_);
        }
        return *this;
    }


    Point<T> center() const override {
        if (!points_) return {0,0};
        T sum_x = 0, sum_y = 0;
        for (size_t i = 0; i < 6; ++i) {
            sum_x += points_[i].x;
            sum_y += points_[i].y;
        }
        return {sum_x / 6.0, sum_y / 6.0};
    }

    double area() const override {
        if (!points_) return 0.0;
        double total_area = 0.0;
        for (size_t i = 0; i < 6; ++i) {
            Point<T> p1 = points_[i];
            Point<T> p2 = points_[(i + 1) % 6];
            total_area += (double)(p1.x * p2.y - p2.x * p1.y);
        }
        return std::abs(total_area) / 2.0;
    }

    void print(std::ostream& os) const override {
        if (!points_) {
            os << "Hexagon: [empty]";
            return;
        }
        os << "Hexagon: [";
        for (size_t i = 0; i < 6; ++i) {
            os << points_[i] << (i == 5 ? "" : ", ");
        }
        os << "]";
    }
};