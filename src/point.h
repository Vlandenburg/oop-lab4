#pragma once
#include <iostream>
#include <concepts>

template <typename Number>
concept NumericType = std::is_arithmetic_v<Number>;

template <NumericType U>
struct Point {
    U x, y;
};

template <NumericType U>
std::istream& operator>>(std::istream& input, Point<U>& p) {
    input >> p.x >> p.y;
    return input;
}

template <NumericType U>
std::ostream& operator<<(std::ostream& output, const Point<U>& p) {
    output << "[" << p.x << ";" << p.y << "]";
    return output;
}