#pragma once
#include "point.h"
#include <iostream>

template <Number T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual void print(std::ostream& os) const = 0;
    virtual void get_center(T* outX, T* outY) const = 0;
    virtual double get_area() const = 0;

    explicit operator double() const { return get_area(); }
};

template <Number T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}