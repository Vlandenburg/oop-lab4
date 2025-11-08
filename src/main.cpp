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
    std::cout << "--- Commands ---\n"
              << "add      - add a new figure (triangle, hexagon, octagon)\n"
              << "print    - show all figures\n"
              << "erase    - remove a figure by index\n"
              << "exit     - close the program\n";
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    std::string cmd;

    show_help();

    while (true) { // Бесконечный цикл, который ждет команду "exit"
        std::cout << "> ";
        std::cin >> cmd;

        if (std::cin.fail() || std::cin.eof()) { // Защита от случайного Ctrl+Z
            break;
        }

        if (cmd == "add") {
            std::string type;
            std::cin >> type;
            if (type == "triangle") {
                Point<double> p1, p2, p3;
                std::cout << "Enter 3 points (x y): ";
                std::cin >> p1 >> p2 >> p3;
                figures.push_back(std::make_shared<Triangle<double>>(p1, p2, p3));
                std::cout << "Triangle added.\n";
            } else if (type == "hexagon") {
                std::vector<Point<double>> points(6);
                std::cout << "Enter 6 points (x y): ";
                for(int i = 0; i < 6; ++i) std::cin >> points[i];
                figures.push_back(std::make_shared<Hexagon<double>>(points.data()));
                std::cout << "Hexagon added.\n";
            } else if (type == "octagon") {
                std::vector<Point<double>> points(8);
                std::cout << "Enter 8 points (x y): ";
                for(int i = 0; i < 8; ++i) std::cin >> points[i];
                figures.push_back(std::make_shared<Octagon<double>>(points.data()));
                std::cout << "Octagon added.\n";
            } else {
                 std::cout << "Unknown figure type.\n";
            }
        } else if (cmd == "print") {
            if (figures.size() == 0) {
                std::cout << "List is empty.\n";
                continue;
            }
            for (size_t i = 0; i < figures.size(); ++i) {
                std::cout << i << ": " << *figures[i] << std::endl;
            }
        } else if (cmd == "erase") {
            size_t index;
            std::cout << "Enter index to erase: ";
            std::cin >> index;
            if (index < figures.size()) {
                figures.erase(index);
                std::cout << "Figure erased.\n";
            } else {
                std::cout << "Invalid index.\n";
            }
        } else if (cmd == "exit") {
            std::cout << "Exiting...\n";
            break; // Выход из цикла
        } else {
            std::cout << "Unknown command. Try 'add', 'print', 'erase', 'exit'.\n";
        }
    }

    return 0;
}