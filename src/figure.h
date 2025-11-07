#pragma once

#include "point.h"
#include <iostream>

template <IsArithmetic NumType>
class Figure {
public:
    virtual ~Figure() = default;

    virtual Point<NumType> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;

    explicit operator double() const {
        return area();
    }
};

template <IsArithmetic NumType>
std::ostream& operator<<(std::ostream& os, const Figure<NumType>& shape) {
    shape.print(os);
    return os;
}