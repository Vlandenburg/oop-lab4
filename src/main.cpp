#include <iostream>
#include <string>
#include <memory>
#include <vector> // Using for points, not for main array
#include <cstring>
#include "array.h"
#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

using SmartFig = std::shared_ptr<Figure<double>>;

template<typename T>
bool read_points(std::vector<Point<T>>& points, int count) {
    std::cout << "enter " << count << " points (x y):\n";
    for (int i = 0; i < count; ++i) {
        Point<T> p;
        std::cin >> p;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "bad input\n";
            return false;
        }
        points.push_back(p);
    }
    return true;
}

int main() {
    Storage<SmartFig> figures;
    char input_buffer[100];

    std::cout << "figure editor. commands: add_tri, add_hex, add_oct, list, del, area, exit\n";
    
    while(true) {
        std::cout << "> ";
        std::cin >> input_buffer;
        
        if (strcmp(input_buffer, "exit") == 0) {
            break;
        } else if (strcmp(input_buffer, "add_tri") == 0) {
            std::vector<Point<double>> pts;
            if (read_points(pts, 3)) {
                figures.add(std::make_shared<Triangle<double>>(pts[0], pts[1], pts[2]));
            }
        } else if (strcmp(input_buffer, "add_hex") == 0) {
            std::vector<Point<double>> pts;
            if (read_points(pts, 6)) {
                figures.add(std::make_shared<Hexagon<double>>(pts.data()));
            }
        } else if (strcmp(input_buffer, "add_oct") == 0) {
            std::vector<Point<double>> pts;
            if (read_points(pts, 8)) {
                figures.add(std::make_shared<Octagon<double>>(pts.data()));
            }
        } else if (strcmp(input_buffer, "list") == 0) {
            for (size_t i = 0; i < figures.count(); ++i) {
                double c_x, c_y;
                figures[i]->get_center(&c_x, &c_y);
                std::cout << i << " -> ";
                figures[i]->print(std::cout);
                std::cout << " | center: (" << c_x << "," << c_y << "), area: " << figures[i]->get_area() << std::endl;
            }
        } else if (strcmp(input_buffer, "del") == 0) {
            size_t i; std::cin >> i;
            figures.remove(i);
        } else if (strcmp(input_buffer, "area") == 0) {
            double total = 0;
            for(size_t i = 0; i < figures.count(); ++i) total += figures[i]->get_area();
            std::cout << "total area = " << total << std::endl;
        } else {
            std::cout << "what?\n";
        }
    }

    return 0;
}