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
#include "FileAdapter.h"
#include "FileReader.h"
#include "FileRepository.h"
#include "FillService.h"
#include "Table.h"
#include "cxxopts/cxxopts.h"

int main(int argc, char* argv[])
{
    std::string search;
    std::string update;
    std::string del;
    std::string insert;
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

        if (order < 3) {
            throw std::runtime_error("Order cannot be less then 3!");
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

        std::cout << "--------------------Welcome to Phonebook REPL!--------------------"
                  << std::endl
                  << "Available commands:" << std::endl
                  << std::string(2, ' ') << "search - search record by phone number" << std::endl
                  << std::string(2, ' ') << "update - update record by phone number" << std::endl
                  << std::string(2, ' ') << "insert - insert new phone number" << std::endl
                  << std::string(2, ' ') << "delete - delete record from book" << std::endl
                  << std::string(2, ' ') << "clear - clear REPL" << std::endl
                  << std::string(2, ' ') << "exit - exit from REPL" << std::endl
                  << std::endl;
        while (true) {
            try {
                std::cout << "Traversal of the B-tree("
                          << std::to_string(order) << ")"
                          << " is " << std::endl;
                tree.traverse(0);
                std::cout << std::endl;

                std::getline(std::cin, mode);

                if (mode == "search") {
                    std::cout << "Search phone: ";
                    std::getline(std::cin, search);
                    auto id = t_master.getIdByValue(search);
                    if (id == std::numeric_limits<int>::max()) {
                        throw std::runtime_error("No records found with phone " + search);
                    }
                    auto node = tree.search(id);
                    if (node != nullptr) {
                        std::cout << search << " is ";
                        auto name = t_slave.getValueById(id);
                        std::cout << name << std::endl;
                    } else {
                        std::cout << search << " is ";
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
                        auto name = t_slave.setValueById(
                                               id,
                                               update,
                                               FileRepository::getSlaveFilePath())
                                        .getValueById(id);
                        std::cout << name << std::endl;
                    } else {
                        throw std::runtime_error("No records found with phone " + buffer);
                    }
                } else if (mode == "insert") {
                    std::cout << "Insert phone: ";
                    std::getline(std::cin, insert);
                    std::string buffer(insert);
                    std::cout << "With value: ";
                    std::getline(std::cin, insert);
                    tree.insert(t_master.getMaxId() + 1);
                    t_master.row(t_master.getMaxId() + 1, buffer).sync(FileRepository::getMasterFilePath());
                    t_slave.row(t_slave.getMaxId() + 1, insert).sync(FileRepository::getSlaveFilePath());
                } else if (mode == "delete") {
                    std::cout << "Delete phone: ";
                    std::getline(std::cin, del);
                    auto id = t_master.getIdByValue(del);
                    tree.remove(id);
                    t_master.deleteValueById(id).sync(FileRepository::getMasterFilePath());
                    t_slave.deleteValueById(id).sync(FileRepository::getSlaveFilePath());
                } else if (mode == "exit") {
                    return EXIT_SUCCESS;
                } else if (mode == "clear") {
                    try {
#ifdef _WIN32
                        system("cls");
#else
                        system("clear");
#endif
                    } catch (...) {
                    }
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
