#pragma once
#include <iostream>
#include <concepts>

template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <Number T>
struct Point {
    T X, Y;
};

template <Number T>
std::istream& operator>>(std::istream& in, Point<T>& p) { in >> p.X >> p.Y; return in; }

template <Number T>
std::ostream& operator<<(std::ostream& out, const Point<T>& p) { out << "(" << p.X << ", " << p.Y << ")"; return out; }