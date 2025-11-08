#pragma once
#include "point.h"

template<is_numeric T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;

    explicit operator double() const {
        return area();
    }
};

template<is_numeric T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}