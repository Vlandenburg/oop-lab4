#pragma once
#include "point.h"
#include <iostream>

template <IsNumber ValType>
class GeometricFigure {
public:
    virtual ~GeometricFigure() = default;
    
    virtual void printDescription(std::ostream& os) const = 0;
    virtual Point2D<ValType> getCenter() const = 0;
    virtual double getArea() const = 0;

    explicit operator double() const {
        return getArea();
    }
};

template <IsNumber T>
std::ostream& operator<<(std::ostream& os, const GeometricFigure<T>& fig) {
    fig.printDescription(os);
    return os;
}