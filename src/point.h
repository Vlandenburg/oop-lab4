#pragma once

#include <iostream>
#include <concepts>

template <typename T>
concept IsArithmetic = std::is_arithmetic_v<T>;

template <IsArithmetic CoordType>
struct Point {
    CoordType x, y;
};

template <IsArithmetic CoordType>
std::istream& operator>>(std::istream& is, Point<CoordType>& pt) {
    is >> pt.x >> pt.y;
    return is;
}

// Было: std.ostream - стало std::ostream
template <IsArithmetic CoordType>
std::ostream& operator<<(std::ostream& os, const Point<CoordType>& pt) {
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}