#include <boost/algorithm/string.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

#include "GraphView.h"

void GraphView::parse(const std::string_view& path)
{
    std::vector<std::string> vertices;
    std::string line;
    std::ifstream input;
    input.open(path.data());
    if (!input) {
        throw std::runtime_error("Unable to open file in path " + std::string(path.data()));
    }
    while (std::getline(input, line)) {
        vertices.push_back(line);
        line.clear();
    }
    std::map<std::string, TGraph::vertex_descriptor> indexes;
    std::map<TGraph::vertex_descriptor, std::string> names;
    TGraph g(vertices.size() * 2);
    unsigned long i = 0;
    for (const auto& vertex : vertices) {
        auto pair = getFromToPair(vertex);
        boost::put(boost::vertex_name_t(), g, i, pair.first);
        auto vFirst = boost::vertex(i, g);
        indexes[pair.first] = vFirst;
        names[vFirst] = pair.first;
        i++;
        boost::put(boost::vertex_name_t(), g, i, pair.second);
        auto vSecond = boost::vertex(i, g);
        indexes[pair.second] = vSecond;
        names[vSecond] = pair.second;
        i++;
        boost::add_edge(indexes.at(pair.first), indexes.at(pair.second), g);
    }
    mGraph = g;
    mVertexMap = names;
}

std::pair<std::string, std::string> GraphView::getFromToPair(const std::string& path)
{
    std::vector<std::string> strs;
    boost::split(strs, path, boost::is_any_of("-"));
    auto pair = std::pair<std::string, std::string>(strs.at(0), strs.at(1));
    return pair;
}

std::pair<TGraph*, std::map<TGraph::vertex_descriptor, std::string>*> GraphView::get()
{
    return std::pair(&mGraph, &mVertexMap);
}

void GraphView::print()
{
    TGraph* graph;
    std::map<TGraph::vertex_descriptor, std::string>* map;
    std::tie(graph, map) = get();
    auto vertices = boost::vertices(*graph);
    for (auto vit = vertices.first; vit != vertices.second; ++vit) {
        auto neighbors = boost::adjacent_vertices(*vit, *graph);
        for (auto nit = neighbors.first; nit != neighbors.second; ++nit) {
            std::cout << map->at(*vit) << ' ' << map->at(*nit) << std::endl;
        }
    }
}

void GraphView::error(const std::exception& ex)
{
    std::cerr << "[Error]: " << ex.what() << std::endl;
}
