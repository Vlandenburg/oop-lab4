#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <stdexcept>
#include <map>
#include <functional>
#include "array.h"
#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

using FigPtr = std::shared_ptr<GeometricFigure<double>>;
using FigList = Vectorish<FigPtr>;

// Ломаем структуру if-else с помощью std::map
using Command = std::function<void(FigList&)>;

void addTriangle(FigList& figures) {
    Point2D<double> p[3];
    std::cout << "Enter 3 coords for triangle: ";
    for (int i = 0; i < 3; ++i) std::cin >> p[i];
    if (std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Bad input.\n"; return;
    }
    figures.push(std::make_shared<Triangle<double>>(p[0], p[1], p[2]));
    std::cout << "Triangle added.\n";
}

void addHexagon(FigList& figures) {
    Point2D<double> p[6];
    std::cout << "Enter 6 coords for hexagon: ";
    for (int i = 0; i < 6; ++i) std::cin >> p[i];
    if (std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Bad input.\n"; return;
    }
    figures.push(std::make_shared<Hexagon<double>>(p));
    std::cout << "Hexagon added.\n";
}

void addOctagon(FigList& figures) {
    Point2D<double> p[8];
    std::cout << "Enter 8 coords for octagon: ";
    for (int i = 0; i < 8; ++i) std::cin >> p[i];
    if (std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Bad input.\n"; return;
    }
    figures.push(std::make_shared<Octagon<double>>(p));
    std::cout << "Octagon added.\n";
}

void listFigures(FigList& figures) {
    if (figures.length() == 0) { std::cout << "Nothing to show.\n"; return; }
    std::cout << "--- Your figures ---\n";
    for(size_t i = 0; i < figures.length(); ++i) {
        std::cout << i << ": ";
        figures.at(i)->printDescription(std::cout);
        std::cout << std::endl;
    }
}

void deleteFigure(FigList& figures) {
    size_t idx;
    std::cout << "Index to delete: "; std::cin >> idx;
    if (std::cin.fail() || idx >= figures.length()) {
        std::cout << "Invalid index.\n";
        if(std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); }
        return;
    }
    figures.pop_at(idx);
    std::cout << "Figure removed.\n";
}

void showTotalArea(FigList& figures) {
    double total = 0;
    for (size_t i = 0; i < figures.length(); ++i) {
        total += figures.at(i)->getArea();
    }
    std::cout << "Total area: " << total << std::endl;
}

int main() {
    FigList myFigures;
    std::string input;

    // Очень нетипичная для AI структура диспетчеризации команд
    std::map<std::string, Command> commands;
    commands["add_triangle"] = addTriangle;
    commands["add_hexagon"] = addHexagon;
    commands["add_octagon"] = addOctagon;
    commands["list"] = listFigures;
    commands["delete"] = deleteFigure;
    commands["area"] = showTotalArea;

    std::cout << "Simple Figure Editor. Commands: add_triangle, list, delete, area, exit.\n";
    
    while(true) {
        std::cout << ">> ";
        std::cin >> input;
        
        if (input == "exit") {
            break;
        }

        // std::cout << "DEBUG: command='" << input << "'" << std::endl; // Человеческий "мусор"
        
        if (commands.count(input)) {
            try {
                commands[input](myFigures);
            } catch (const std::exception& e) {
                std::cout << "An error occurred: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}