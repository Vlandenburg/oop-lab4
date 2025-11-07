#pragma once
#include <iostream>
#include <concepts>

template <typename T>
concept IsNumber = std::is_arithmetic_v<T>;

template <IsNumber ScalarType>
struct Point2D {
    ScalarType x, y;
};

template <IsNumber T>
std::istream& operator>>(std::istream& in, Point2D<T>& p) {
    in >> p.x >> p.y;
    return in;
}

template <IsNumber T>
std::ostream& operator<<(std::ostream& out, const Point2D<T>& p) {
    out << "{" << p.x << ", " << p.y << "}";
    return out;
}