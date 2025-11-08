#include <cassert>
#include <iostream>
#include <sstream>
#include "point.h"
#include "array.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

void array_tests() {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    assert(arr.size() == 3);
    arr.erase(1);
    assert(arr.size() == 2);
    assert(arr[1] == 3);
}

void figure_tests() {
    Triangle<double> t({0,0}, {4,0}, {0,3});
    assert(t.area() == 6.0);
    Point<double> tc = t.center();
    assert(abs(tc.x - 4.0/3.0) < 1e-9);
}

int main() {
    array_tests();
    figure_tests();
    std::cout << "Tests passed\n";
    return 0;
}