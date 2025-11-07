#include <iostream>
#include <string>
#include <memory>
#include "array.h"
#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

using FigurePtr = std::shared_ptr<Figure<double>>;

void print_help() {
    std::cout << "Available commands:\n";
    std::cout << "add hexagon    - Add a hexagon\n";
    std::cout << "add octagon    - Add an octagon\n";
    std::cout << "add triangle   - Add a triangle\n";
    std::cout << "print          - Print all figures with details\n";
    std::cout << "total_area     - Calculate total area of all figures\n";
    std::cout << "erase [index]  - Erase figure at index\n";
    std::cout << "help           - Show this help message\n";
    std::cout << "exit           - Exit the program\n";
}

void template_demonstration() {
    std::cout << "\n--- Template Demonstration ---\n";

    std::cout << "1. Array of derived type (Triangle<int>):\n";
    Array<Triangle<int>> triangle_array;
    triangle_array.push_back(Triangle<int>({0,0}, {4,0}, {0,3}));
    std::cout << "Added a triangle. Array size: " << triangle_array.size() << std::endl;
    std::cout << "Area: " << triangle_array[0].area() << std::endl;

    std::cout << "\n2. Array of base type pointers (Figure<int>*):\n";
    Array<Figure<int>*> figure_ptr_array;
    figure_ptr_array.push_back(new Triangle<int>({0,0}, {1,1}, {2,0}));
    std::cout << "Added a figure pointer. Array size: " << figure_ptr_array.size() << std::endl;
    std::cout << "Area via pointer: " << figure_ptr_array[0]->area() << std::endl;
    delete figure_ptr_array[0];
    
    std::cout << "--- End of Demonstration ---\n\n";
}

int main() {
    Array<FigurePtr> figures;
    std::string command;

    print_help();

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "add") {
            std::string type;
            std::cin >> type;
            try {
                if (type == "triangle") {
                    Point<double> p1, p2, p3;
                    std::cout << "Enter 3 points (x y): ";
                    std::cin >> p1 >> p2 >> p3;
                    figures.push_back(std::make_shared<Triangle<double>>(p1, p2, p3));
                } else if (type == "hexagon") {
                    Point<double> p[6];
                    std::cout << "Enter 6 points (x y): ";
                    for(int i = 0; i < 6; ++i) std::cin >> p[i];
                    figures.push_back(std::make_shared<Hexagon<double>>(p));
                } else if (type == "octagon") {
                    Point<double> p[8];
                    std::cout << "Enter 8 points (x y): ";
                    for(int i = 0; i < 8; ++i) std::cin >> p[i];
                    figures.push_back(std::make_shared<Octagon<double>>(p));
                } else {
                    std::cout << "Unknown figure type.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error reading points: " << e.what() << std::endl;
            }
        } else if (command == "print") {
            if (figures.size() == 0) {
                std::cout << "Array is empty.\n";
                continue;
            }
            for (size_t i = 0; i < figures.size(); ++i) {
                std::cout << "[" << i << "] " << *figures[i] << std::endl;
                std::cout << "    Center: " << figures[i]->center() << std::endl;
                std::cout << "    Area: " << figures[i]->area() << std::endl;
            }
        } else if (command == "total_area") {
            double total = 0.0;
            for (size_t i = 0; i < figures.size(); ++i) {
                total += figures[i]->area();
            }
            std::cout << "Total area: " << total << std::endl;
        } else if (command == "erase") {
            size_t index;
            std::cin >> index;
            if (index < figures.size()) {
                figures.erase(index);
                std::cout << "Figure at index " << index << " erased.\n";
            } else {
                std::cout << "Invalid index.\n";
            }
        } else if (command == "help") {
            print_help();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command. Type 'help' for options.\n";
        }
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template_demonstration();

    return 0;
}