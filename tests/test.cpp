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
    assert(ss.str() == "[10;20]");
    
    std::cout << "Point test passed.\n";
}

void test_array() {
    CustomArray<int> arr;
    assert(arr.count() == 0);
    
    arr.add(1);
    arr.add(2);
    arr.add(3);
    assert(arr.count() == 3);
    assert(arr.get(0) == 1 && arr.get(1) == 2 && arr.get(2) == 3);

    arr.remove_at(1);
    assert(arr.count() == 2);
    assert(arr.get(0) == 1 && arr.get(1) == 3);
    
    CustomArray<int> arr_copy = arr;
    assert(arr_copy.count() == 2);
    assert(arr_copy.get(0) == 1 && arr_copy.get(1) == 3);
    
    CustomArray<int> arr_move = std::move(arr);
    assert(arr_move.count() == 2);
    assert(arr.count() == 0);

    std::cout << "Array test passed.\n";
}

void test_figures() {
    // Triangle
    Triangle<double> t({0,0}, {4,0}, {0,3});
    assert(t.calculate_area() == 6.0);
    Point<double> t_center = t.calculate_center();
    assert(abs(t_center.x - 4.0/3.0) < 1e-9 && abs(t_center.y - 1.0) < 1e-9);

    // Hexagon
    Point<double> hex_pts[6] = {{1,0}, {0.5, 0.866}, {-0.5, 0.866}, {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}};
    Hexagon<double> h(hex_pts);
    assert(abs(h.calculate_area() - 2.598) < 1e-3);
    Point<double> h_center = h.calculate_center();
    assert(abs(h_center.x) < 1e-9 && abs(h_center.y) < 1e-9);

    // Octagon
    Point<double> oct_pts[8] = {{0.5, 1.207}, {-0.5, 1.207}, {-1.207, 0.5}, {-1.207, -0.5}, {-0.5, -1.207}, {0.5, -1.207}, {1.207, -0.5}, {1.207, 0.5}};
    Octagon<double> o(oct_pts);
    assert(abs(o.calculate_area() - 4.828) < 1e-3);
    Point<double> o_center = o.calculate_center();
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