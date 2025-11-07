#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <stdexcept>
#include "array.h"
#include "figure.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

using FigurePtr = std::shared_ptr<Figure<double>>;
using FigureList = CustomArray<FigurePtr>;

void print_help() {
    std::cout << "\n--- HELP MENU ---\n"
              << "  add <figure>   - Create a shape (triangle, hexagon, octagon)\n"
              << "  list           - Show all shapes in memory\n"
              << "  sum_area       - Get total area of all shapes\n"
              << "  del <index>    - Delete shape at index\n"
              << "  help           - Show this info again\n"
              << "  quit           - Exit\n";
}

void handle_bad_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Error: Invalid number format entered.\n";
}

// Новые helper-функции
void process_add_triangle(FigureList& list) {
    Point<double> p1, p2, p3;
    std::cout << "Input 3 points for triangle (format: x y): ";
    if (!(std::cin >> p1 >> p2 >> p3)) { handle_bad_input(); return; }
    list.add(std::make_shared<Triangle<double>>(p1, p2, p3));
    std::cout << "Success: Triangle added to list.\n";
}

void process_add_hexagon(FigureList& list) {
    Point<double> pts[6];
    std::cout << "Input 6 points for hexagon (format: x y): ";
    bool ok = true;
    for(int i = 0; i < 6; ++i) if (!(std::cin >> pts[i])) { ok = false; break; }
    if (!ok) { handle_bad_input(); return; }
    list.add(std::make_shared<Hexagon<double>>(pts));
    std::cout << "Success: Hexagon added to list.\n";
}

void process_add_octagon(FigureList& list) {
    Point<double> pts[8];
    std::cout << "Input 8 points for octagon (format: x y): ";
    for(int i = 0; i < 8; ++i) {
        if (!(std::cin >> pts[i])) {
            handle_bad_input();
            return;
        }
    }
    list.add(std::make_shared<Octagon<double>>(pts));
    std::cout << "Success: Octagon added to list.\n";
}


int main() {
    FigureList all_figures;
    std::string command;
    print_help();

    while (std::cout << "cmd> ", std::cin >> command) {
        try {
            if (command == "add") {
                std::string type;
                std::cin >> type;
                if (type == "triangle") process_add_triangle(all_figures);
                else if (type == "hexagon") process_add_hexagon(all_figures);
                else if (type == "octagon") process_add_octagon(all_figures);
                else std::cout << "Unknown shape type: " << type << "\n";
            } else if (command == "list") {
                if (all_figures.count() == 0) { std::cout << "List is empty.\n"; continue; }
                for (size_t i = 0; i < all_figures.count(); ++i) {
                    std::cout << i << ". ";
                    all_figures.get(i)->display(std::cout);
                    std::cout << "\n   Center: " << all_figures.get(i)->calculate_center()
                              << ", Area: " << all_figures.get(i)->calculate_area() << "\n";
                }
            } else if (command == "sum_area") {
                double total = 0.0;
                for (size_t i = 0; i < all_figures.count(); ++i) total += all_figures.get(i)->calculate_area();
                std::cout << "Total area of all shapes: " << total << "\n";
            } else if (command == "del") {
                size_t index;
                if (!(std::cin >> index)) { handle_bad_input(); continue; }
                all_figures.remove_at(index);
                std::cout << "Shape at index " << index << " was removed.\n";
            } else if (command == "help") {
                print_help();
            } else if (command == "quit") {
                std::cout << "Exiting...\n";
                break;
            } else {
                std::cout << "Unknown command. Try 'help'.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Operation failed: " << e.what() << "\n";
        }
    }

    return 0;
}