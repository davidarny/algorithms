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
#include "FileAdapter.h"
#include "FileReader.h"
#include "FileRepository.h"
#include "FillService.h"
#include "Table.h"
#include "cxxopts/cxxopts.h"
#include <iostream>
#include <limits>
#include <string>

int main(int argc, char* argv[])
{
    std::string search;
    std::string update;
    int del = std::numeric_limits<int>::max();
    int insert = std::numeric_limits<int>::max();
    int degree = std::numeric_limits<int>::max();
    int order = std::numeric_limits<int>::max();
    std::string mode;

    bool debug = true;
    bool help = false;

    try {
        cxxopts::Options options("Phonebook", "Personal Phonebook driver");
        options.add_options()("order", "B-tree maximum order (default = 4)", cxxopts::value<int>()->default_value("4"))("debug", "Debug mode", cxxopts::value<bool>()->default_value("false"))("master", "Path to master DB", cxxopts::value<std::string>())("slave", "Path to slave DB", cxxopts::value<std::string>())("help", "Help info", cxxopts::value<bool>()->default_value("false"));
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

        Table t_master, t_slave;
        TFile f_master, f_slave;
        {
            FileReader reader(FileRepository::getMasterFilePath());
            FileAdapter adapter(reader);
            FillService::fill<int>(tree, adapter);
            FillService::fill(t_master, adapter);
        }
        {
            FileReader reader(FileRepository::getSlaveFilePath());
            FileAdapter adapter(reader);
            FillService::fill(t_slave, adapter);
        }

        while (true) {
            try {
                std::cout << "Traversal of the B-tree("
                          << std::to_string(order) << ")"
                          << " is " << std::endl;
                tree.traverse();
                std::cout << std::endl;

                std::cout << "Working mode (search, update, exit): ";
                std::getline(std::cin, mode);

                if (mode == "search") {
                    std::cout << "Search phone: ";
                    std::getline(std::cin, search);
                    auto id = t_master.getIdByValue(search);
                    if (id == std::numeric_limits<int>::max()) {
                        throw std::runtime_error("No records found with phone " + search);
                    }
                    std::cout << search << " is ";
                    auto node = tree.search(id);
                    if (node != nullptr) {
                        auto name = t_slave.getValueById(id);
                        std::cout << name << std::endl;
                    } else {
                        std::cout << "not present" << std::endl;
                    }
                } else if (mode == "update") {
                    std::cout << "Update phone: ";
                    std::getline(std::cin, update);
                    std::string buffer(update);
                    std::cout << "With value: ";
                    std::getline(std::cin, update);
                    auto id = t_master.getIdByValue(buffer);
                    if (id == std::numeric_limits<int>::max()) {
                        throw std::runtime_error("No records found with phone " + buffer);
                    }
                    auto node = tree.search(id);
                    if (node != nullptr) {
                        auto name = t_slave.setValueById(id, update).getValueById(id);
                        std::cout << name << std::endl;
                    } else {
                        throw std::runtime_error("No records found with phone " + buffer);
                    }
                } else if (mode == "insert") {
                    std::cout << "Insert node: ";
                    std::cin >> insert;
                    tree.insert(insert);
                } else if (mode == "delete") {
                    std::cout << "Delete node: ";
                    std::cin >> del;
                    tree.remove(del);
                } else if (mode == "exit") {
                    return EXIT_SUCCESS;
                } else {
                    throw std::runtime_error("Command not found!");
                }
                std::cout << std::endl;
            } catch (std::exception& ex) {
                std::cerr << "[ERROR]: " << ex.what() << std::endl;
            } catch (...) {
                std::cerr << "[ERROR]: Internal error!" << std::endl;
            }
        }
    } catch (std::exception& ex) {
        std::cerr << "[ERROR]: " << ex.what() << std::endl;
    }
}
