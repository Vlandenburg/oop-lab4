#include <cassert>
#include <iostream>
#include <sstream>

#include "point.h"
#include "array.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

void test_point() {
    Point<int> p{10, 20};
    assert(p.x == 10 && p.y == 20);

    std::stringstream ss;
    ss << p;
    assert(ss.str() == "(10, 20)");
    
    std::cout << "Point test passed.\n";
}

void test_array() {
    Array<int> arr;
    assert(arr.size() == 0);
    
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    assert(arr.size() == 3);
    assert(arr[0] == 1 && arr[1] == 2 && arr[2] == 3);

    arr.erase(1);
    assert(arr.size() == 2);
    assert(arr[0] == 1 && arr[1] == 3);
    
    Array<int> arr_copy = arr;
    assert(arr_copy.size() == 2);
    assert(arr_copy[0] == 1 && arr_copy[1] == 3);
    
    Array<int> arr_move = std::move(arr);
    assert(arr_move.size() == 2);
    assert(arr.size() == 0);

    std::cout << "Array test passed.\n";
}

void test_figures() {
    // Triangle
    Triangle<double> t({0,0}, {4,0}, {0,3});
    assert(t.area() == 6.0);
    Point<double> t_center = t.center();
    assert(abs(t_center.x - 4.0/3.0) < 1e-9 && abs(t_center.y - 1.0) < 1e-9);

    // Hexagon (regular, side 1, centered at origin)
    Point<double> hex_pts[6] = {{1,0}, {0.5, 0.866}, {-0.5, 0.866}, {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}};
    Hexagon<double> h(hex_pts);
    assert(abs(h.area() - 2.598) < 1e-3);
    Point<double> h_center = h.center();
    assert(abs(h_center.x) < 1e-9 && abs(h_center.y) < 1e-9);

    // Octagon (regular, side 1, vertices calculated)
    Point<double> oct_pts[8] = {{0.5, 1.207}, {-0.5, 1.207}, {-1.207, 0.5}, {-1.207, -0.5}, {-0.5, -1.207}, {0.5, -1.207}, {1.207, -0.5}, {1.207, 0.5}};
    Octagon<double> o(oct_pts);
    assert(abs(o.area() - 4.828) < 1e-3);
    Point<double> o_center = o.center();
    assert(abs(o_center.x) < 1e-9 && abs(o_center.y) < 1e-9);

    std::cout << "Figures test passed.\n";
}

int main() {
    test_point();
    test_array();
    test_figures();
    std::cout << "All tests passed.\n";
    return 0;
}