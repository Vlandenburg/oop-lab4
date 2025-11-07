#include <cassert>
#include <iostream>
#include <sstream>
#include "point.h"
#include "array.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

void test_point() {
    Point2D<int> p{10, 20};
    assert(p.x == 10 && p.y == 20);
    std::stringstream ss;
    ss << p;
    assert(ss.str() == "{10, 20}");
    std::cout << "Point test OK.\n";
}

void test_array() {
    Vectorish<int> v;
    assert(v.length() == 0);
    v.push(1); v.push(2); v.push(3);
    assert(v.length() == 3);
    assert(v.at(0) == 1 && v.at(2) == 3);
    v.pop_at(1);
    assert(v.length() == 2);
    assert(v.at(1) == 3);
    std::cout << "Array test OK.\n";
}

void test_figures() {
    Triangle<double> t({0,0}, {4,0}, {0,3});
    assert(t.getArea() == 6.0);
    Point2D<double> tc = t.getCenter();
    assert(abs(tc.x - 4.0/3.0) < 1e-9);

    Point2D<double> hex_pts[6] = {{1,0}, {0.5, 0.866}, {-0.5, 0.866}, {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}};
    Hexagon<double> h(hex_pts);
    assert(abs(h.getArea() - 2.598) < 1e-3);

    std::cout << "Figures test OK.\n";
}

int main() {
    test_point();
    test_array();
    test_figures();
    std::cout << "All tests passed successfully.\n";
    return 0;
}