/*
26. Имеется   телефонный   справочник   со   сведениями   о
владельцах  телефонов.  Организовать  индексацию  по   номерам
телефонов с помощью построения Б-дерева. Хранить дерево в виде
самостоятельного файла.  Обеспечить корректировку  информации.
Проиллюстрировать  этапы поиска информации по заданному номеру
телефона (15).
Арутюнян Давид
ПС-23
gcc 8.1.0
cmake 3.9.5
*/

#include <iostream>
#include <limits>
#include <string>

#include "BTree.h"
#include "cxxopts/cxxopts.h"

int main(int argc, char* argv[])
{
    int search = std::numeric_limits<int>::max();
    int del = std::numeric_limits<int>::max();
    int insert = std::numeric_limits<int>::max();
    int update = std::numeric_limits<int>::max();
    int degree = std::numeric_limits<int>::max();
    int order = std::numeric_limits<int>::max();
    std::string mode;

    bool debug = true;

    try {
        cxxopts::Options options("Phonebook", "Personal Phonebook driver");
        options.add_options()("order", "B-tree maximum order (default = 4)", cxxopts::value<int>()->default_value("4"))("debug", "Specify if want to run in debug mode", cxxopts::value<bool>()->default_value("false"));
        auto result = options.parse(argc, argv);
        debug = result["debug"].as<bool>();
        order = result["order"].as<int>();
        degree = (degree + 1) / 2;

        BTree tree(degree);

        while (true) {
            try {
                std::cout << "Traversal of the B-tree(" << std::to_string(order) << ")"
                          << " is " << std::endl;
                tree.traverse();
                std::cout << std::endl;

                std::cout << "Working mode (insert, delete, search, update, exit): ";
                std::cin >> mode;

                if (mode == "search") {
                    std::cout << "Search node: ";
                    std::cin >> search;

                    std::cout << std::to_string(search) << " is ";
                    if (tree.search(search) != nullptr) {
                        std::cout << "present" << std::endl;
                    } else {
                        std::cout << "not present" << std::endl;
                    }
                } else if (mode == "insert") {
                    std::cout << "Insert node: ";
                    std::cin >> insert;
                    tree.insert(insert);
                } else if (mode == "delete") {
                    std::cout << "Delete node: ";
                    std::cin >> del;
                    tree.remove(del);
                } else if (mode == "update") {
                    std::cout << "Update node: ";
                    std::cin >> update;
                    std::cout << "With value: ";
                    std::cin >> insert;
                    tree.update(update, insert);
                } else if (mode == "exit") {
                    return EXIT_SUCCESS;
                }
            } catch (std::exception& ex) {
                std::cerr << "[ERROR]: " << ex.what() << std::endl;
            } catch (...) {
                std::cerr << "[ERROR]: "
                          << "Internal error!" << std::endl;
            }
        }

    } catch (std::exception& ex) {
        std::cerr << "[ERROR]: " << ex.what() << std::endl;
    }
}
