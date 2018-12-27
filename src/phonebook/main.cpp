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

#include "BTree.h"
#include "FileReader.h"
#include "FileRepository.h"
#include "FillService.h"
#include "MasterFileAdapter.h"
#include "SlaveFileAdapter.h"
#include "Table.h"
#include "cxxopts/cxxopts.h"
#include <iostream>
#include <limits>
#include <string>

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
    bool help = false;

    try {
        cxxopts::Options options("Phonebook", "Personal Phonebook driver");
        options.add_options()("order", "B-tree maximum order (default = 4)", cxxopts::value<int>()->default_value("4"))(
            "debug", "Debug mode", cxxopts::value<bool>()->default_value("false"))("master", "Path to master DB",
            cxxopts::value<std::string>())(
            "slave", "Path to slave DB", cxxopts::value<std::string>())("help", "Help info",
            cxxopts::value<bool>()->default_value("false"));
        auto result = options.parse(argc, argv);
        help = result["help"].as<bool>();
        if (help) {
            std::cout
                << "--order: B-tree maximum order (default = 4)\n"
                << "--debug: Debug mode\n"
                << "--master: Path to master DB\n"
                << "--slave: Path to slave DB\n"
                << "--help: Help info\n";
            return EXIT_SUCCESS;
        }
        debug = result["debug"].as<bool>();
        order = result["order"].as<int>();
        if (result.count("master") > 0) {
            FileRepository::overrideMasterFilePath(result["master"].as<std::string>());
        }
        if (result.count("slave") > 0) {
            FileRepository::overrideSlaveFilePath(result["slave"].as<std::string>());
        }

        if (order < 2) {
            throw std::runtime_error("Order cannot be less then 2!");
        }

        BTree tree(order);
        Table table;
        table
            .column("full_name")
            .column("phone");

        TFile master, slave;
        {
            FileReader reader(FileRepository::getMasterFilePath());
            MasterFileAdapter adapter(reader);
            FillService::fill<int>(tree, adapter);
        }
        {
            FileReader reader(FileRepository::getSlaveFilePath());
            SlaveFileAdapter adapter(reader);
            FillService::fill(table, adapter);
        }

        while (true) {
            try {
                std::cout << "Traversal of the B-tree("
                          << std::to_string(order) << ")"
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
