/*
24. Имеются  расписания вылетов самолетов в  ряде  аэропор-
тов.  Требуется по  начальному  и  конечному  пунктам  методом
поиска  в ширину сформировать и выдать дерево возможных путей.
Проиллюстрировать этапы поиска (11).
Арутюнян Давид ПС-23
CLion 2018.3
gcc version 8.1.0
*/

#include <algorithm>
#include <iostream>
#include <string_view>

#include "GraphView.h"
#include "cxxopts/cxxopts.h"

int main(int argc, char* argv[])
{
    GraphView graph;
    std::string from;
    std::string to;
    std::string type;
    bool debug;
    try {
        cxxopts::Options options("Aeroflot", "Aeroflot flights timetable & path search");
        options.add_options()("search", "Specifies search type (DFS/BFS)",
            cxxopts::value<std::string>()->default_value("BFS"))("file", "Path to input file",
            cxxopts::value<std::string>())(
            "debug", "Specify if want to see all DFS/BFS steps", cxxopts::value<bool>()->default_value("false"));
        auto result = options.parse(argc, argv);
        type = result["search"].as<std::string>();
        if (result.count("file") == 0) {
            throw std::runtime_error("No `file` argument found!");
        }
        auto path = result["file"].as<std::string>();
        debug = result["debug"].as<bool>();

        graph.debug(debug);
        graph.parse(path);
        graph.print();
        std::cout << std::endl;

        std::cout << "From: ";
        std::cin >> from;
        std::cout << std::endl;

        std::cout << "To: ";
        std::cin >> to;
        std::cout << std::endl;

        std::cout
            << "Going from "
            << from
            << " to "
            << to << "..."
            << std::endl
            << std::endl;

        graph.search(from, to, type);
    } catch (std::exception& ex) {
        graph.error(ex);
    }
}
