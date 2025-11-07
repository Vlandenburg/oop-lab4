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

using SharedFigure = std::shared_ptr<Figure<double>>;

void show_menu() {
    std::cout << "\nCommands list:\n"
              << "add <figure>   - Add a new figure (triangle, hexagon, octagon)\n"
              << "print          - Show details for all figures\n"
              << "total_area     - Calculate combined area\n"
              << "erase <index>  - Remove figure by its index\n"
              << "help           - Show this menu again\n"
              << "exit           - Close the application\n";
}

void clear_cin_buffer() {
    std::cout << "Input error. Please enter numeric values.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void run_template_examples() {
    std::cout << "\n--- Array Template Examples ---\n";
    std::cout << "Example 1: Array of concrete type (Triangle<int>)\n";
    Array<Triangle<int>> tri_arr;
    tri_arr.push_back(Triangle<int>({0,0}, {5,0}, {0,5}));
    std::cout << "Triangle created. Array size is now: " << tri_arr.size() << "\n";
    std::cout << "Its area: " << tri_arr[0].area() << "\n";

    std::cout << "\nExample 2: Array of base pointers (Figure<int>*)\n";
    Array<Figure<int>*> fig_ptr_arr;
    fig_ptr_arr.push_back(new Triangle<int>({0,0}, {2,2}, {4,0}));
    std::cout << "Figure pointer added. Array size is now: " << fig_ptr_arr.size() << "\n";
    std::cout << "Area from base pointer: " << fig_ptr_arr[0]->area() << "\n";
    delete fig_ptr_arr[0];
    
    std::cout << "--- End of Examples ---\n\n";
}

int main() {
    Array<SharedFigure> figures_collection;
    std::string user_cmd;

    show_menu();

    while (true) {
        std::cout << "> ";
        if (!(std::cin >> user_cmd)) {
            if (std::cin.eof()) break;
            clear_cin_buffer();
            continue;
        }

        try {
            if (user_cmd == "add") {
                std::string fig_type;
                std::cin >> fig_type;
                if (fig_type == "triangle") {
                    Point<double> p1, p2, p3;
                    std::cout << "Enter 3 points for triangle (x y): ";
                    if (!(std::cin >> p1 >> p2 >> p3)) { clear_cin_buffer(); continue; }
                    figures_collection.push_back(std::make_shared<Triangle<double>>(p1, p2, p3));
                    std::cout << "New triangle was added.\n";
                } else if (fig_type == "hexagon") {
                    Point<double> pts[6];
                    std::cout << "Enter 6 points for hexagon (x y): ";
                    for(int i = 0; i < 6; ++i) if (!(std::cin >> pts[i])) { clear_cin_buffer(); goto next_command_loop; }
                    figures_collection.push_back(std::make_shared<Hexagon<double>>(pts));
                    std::cout << "New hexagon was added.\n";
                } else if (fig_type == "octagon") {
                    Point<double> pts[8];
                    std::cout << "Enter 8 points for octagon (x y): ";
                    for(int i = 0; i < 8; ++i) if (!(std::cin >> pts[i])) { clear_cin_buffer(); goto next_command_loop; }
                    figures_collection.push_back(std::make_shared<Octagon<double>>(pts));
                    std::cout << "New octagon was added.\n";
                } else {
                    std::cout << "Unknown figure: " << fig_type << "\n";
                }
            } else if (user_cmd == "print") {
                if (figures_collection.size() == 0) {
                    std::cout << "The collection is empty.\n";
                    continue;
                }
                for (size_t j = 0; j < figures_collection.size(); ++j) {
                    std::cout << "Figure #" << j << ": " << *figures_collection[j] << "\n";
                    std::cout << "  Center point: " << figures_collection[j]->center() << "\n";
                    std::cout << "  Area value: " << figures_collection[j]->area() << "\n";
                }
            } else if (user_cmd == "total_area") {
                double sum_area = 0.0;
                for (size_t j = 0; j < figures_collection.size(); ++j) {
                    sum_area += figures_collection[j]->area();
                }
                std::cout << "Combined area of all figures: " << sum_area << "\n";
            } else if (user_cmd == "erase") {
                size_t idx;
                if (!(std::cin >> idx)) { clear_cin_buffer(); continue; }
                figures_collection.erase(idx);
                std::cout << "Figure #" << idx << " has been removed.\n";
            } else if (user_cmd == "help") {
                show_menu();
            } else if (user_cmd == "exit") {
                break;
            } else {
                std::cout << "Unknown command. Type 'help' to see options.\n";
            }
        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << "\n";
        }
        
        next_command_loop:;
    }

    run_template_examples();
    return 0;
}