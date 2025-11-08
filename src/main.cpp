#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "array.h"
#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

void show_help() {
    std::cout << "Available commands:\n"
              << "  add <figure_type> - Add a new figure (triangle, hexagon, octagon)\n"
              << "  print_all         - Show details for all figures\n"
              << "  total_area        - Calculate the total area of all figures\n"
              << "  erase <index>     - Remove a figure by its index\n"
              << "  help              - Show this help message\n"
              << "  exit              - Close the program\n";
}

void demo_array_template() {
    std::cout << "\n--- Demonstrating Array template with <int> ---\n";
    Array<int> intArray;
    intArray.push_back(10);
    intArray.push_back(20);
    intArray.push_back(30);
    std::cout << "Initial array: ";
    for (size_t i = 0; i < intArray.size(); ++i) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    intArray.erase(1);
    std::cout << "Array after erasing element at index 1: ";
    for (size_t i = 0; i < intArray.size(); ++i) {
        std::cout << intArray[i] << " ";
    }
    std::cout << "\n--- End of demonstration ---\n\n";
}

int main() {
    using FigurePtr = std::shared_ptr<Figure<double>>;
    Array<FigurePtr> figures;
    std::string cmd;

    show_help();

    while (true) {
        std::cout << "> ";
        std::cin >> cmd;

        if (std::cin.fail() || std::cin.eof()) {
            break;
        }

        if (cmd == "add") {
            std::string type;
            std::cin >> type;
            try {
                if (type == "triangle") {
                    Point<double> p1, p2, p3;
                    std::cout << "Enter 3 points (x y) for triangle: ";
                    std::cin >> p1 >> p2 >> p3;
                    figures.push_back(std::make_shared<Triangle<double>>(p1, p2, p3));
                    std::cout << "Triangle added.\n";
                } else if (type == "hexagon") {
                    Point<double> points[6];
                    std::cout << "Enter 6 points (x y) for hexagon: ";
                    for(int i = 0; i < 6; ++i) std::cin >> points[i];
                    figures.push_back(std::make_shared<Hexagon<double>>(points));
                    std::cout << "Hexagon added.\n";
                } else if (type == "octagon") {
                    Point<double> points[8];
                    std::cout << "Enter 8 points (x y) for octagon: ";
                    for(int i = 0; i < 8; ++i) std::cin >> points[i];
                    figures.push_back(std::make_shared<Octagon<double>>(points));
                    std::cout << "Octagon added.\n";
                } else {
                     std::cout << "Error: Unknown figure type '" << type << "'.\n";
                }
            } catch (const std::exception& e) {
                std::cerr << "An error occurred: " << e.what() << std::endl;
            }
        } else if (cmd == "print_all") {
            if (figures.size() == 0) {
                std::cout << "The array of figures is empty.\n";
                continue;
            }
            for (size_t i = 0; i < figures.size(); ++i) {
                std::cout << i << ": " << *figures[i] << " | Center: " << figures[i]->center() 
                          << " | Area: " << figures[i]->area() << " | Vertices: ";
                figures[i]->print_vertices(std::cout);
                std::cout << std::endl;
            }
        } else if (cmd == "total_area") {
            double total = 0.0;
            for (size_t i = 0; i < figures.size(); ++i) {
                total += figures[i]->area();
            }
            std::cout << "Total area of all figures: " << total << std::endl;
        } else if (cmd == "erase") {
            size_t index;
            std::cout << "Enter index to erase: ";
            std::cin >> index;
            if (index < figures.size()) {
                figures.erase(index);
                std::cout << "Figure at index " << index << " erased.\n";
            } else {
                std::cout << "Error: Invalid index.\n";
            }
        } else if (cmd == "help") {
            show_help();
        } else if (cmd == "exit") {
            break;
        } else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }
    
    demo_array_template();

    return 0;
}