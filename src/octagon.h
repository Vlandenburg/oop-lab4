#pragma once

#include "figure.h"
#include <memory>
#include <cmath>
#include <utility>

template <IsArithmetic T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> points_;

public:
    Octagon() : points_(nullptr) {}

    Octagon(const Point<T> p[8]) : points_(new Point<T>[8]) {
        for (size_t i = 0; i < 8; ++i) { points_[i] = p[i]; }
    }
    
    Octagon(const Octagon<T>& src) : points_(new Point<T>[8]) {
        if (src.points_) {
            for (size_t i = 0; i < 8; ++i) {
                points_[i] = src.points_[i];
            }
        }
    }
    
    Octagon(Octagon<T>&& src) noexcept : points_(std::move(src.points_)) {}

    Octagon<T>& operator=(const Octagon<T>& src) {
        if (this != &src) {
            points_.reset(new Point<T>[8]);
            if (src.points_) {
                for (size_t i = 0; i < 8; ++i) {
                    points_[i] = src.points_[i];
                }
            }
        }
        return *this;
    }

    Octagon<T>& operator=(Octagon<T>&& src) noexcept {
        if (this != &src) {
            points_ = std::move(src.points_);
        }
        return *this;
    }

    Point<T> center() const override {
        if (!points_) return {0,0};
        T total_x = 0, total_y = 0;
        for (size_t i = 0; i < 8; ++i) {
            total_x += points_[i].x;
            total_y += points_[i].y;
        }
        return {total_x / 8.0, total_y / 8.0};
    }

    double area() const override {
        if (!points_) return 0.0;
        double signed_area = 0.0;
        for (size_t i = 0; i < 8; ++i) {
            Point<T> current_pt = points_[i];
            Point<T> next_pt = points_[(i + 1) % 8];
            signed_area += (double)(current_pt.x * next_pt.y - next_pt.x * current_pt.y);
        }
        return std::abs(signed_area) / 2.0;
    }

    void print(std::ostream& os) const override {
        if (!points_) {
            os << "Octagon: [empty]";
            return;
        }
        os << "Octagon: [";
        for (size_t i = 0; i < 8; ++i) {
            os << points_[i] << (i == 7 ? "" : ", ");
        }
        os << "]";
    }
};