#include <cassert>
#include <iostream>
#include <sstream>
#include "point.h"
#include "array.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

int main() {
    // Point test
    Point<int> p{10, 20};
    assert(p.X == 10 && p.Y == 20);
    
    // Array test
    Storage<int> v;
    assert(v.count() == 0);
    v.add(1); v.add(2); v.add(3);
    assert(v.count() == 3);
    v.remove(1);
    assert(v[1] == 3);

    // Figure test
    Triangle<double> t({0,0}, {4,0}, {0,3});
    assert(t.get_area() == 6.0);
    double cx, cy;
    t.get_center(&cx, &cy);
    assert(abs(cx - 4.0/3.0) < 1e-9);

    std::cout << "Tests OK\n";
    return 0;
}