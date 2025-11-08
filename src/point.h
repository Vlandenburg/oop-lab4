#pragma once
#include <iostream>
#include <concepts>

template<typename T>
concept is_numeric = std::is_arithmetic_v<T>;

template<is_numeric T>
struct Point {
    T x, y;
};

template<is_numeric T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template<is_numeric T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}