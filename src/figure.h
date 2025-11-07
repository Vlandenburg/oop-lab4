#pragma once
#include "point.h"
#include <iostream>

template <NumericType T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual void display(std::ostream& os) const = 0;
    virtual Point<T> calculate_center() const = 0;
    virtual double calculate_area() const = 0;

    explicit operator double() const {
        return calculate_area();
    }
};

template <NumericType T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.display(os);
    return os;
}