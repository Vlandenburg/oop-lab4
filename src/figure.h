#pragma once

#include "point.h"
#include <iostream>

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;

    operator double() const {
        return area();
    }
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}