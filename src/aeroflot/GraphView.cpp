#include <boost/algorithm/string.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <fstream>
#include <iostream>
#include <queue>
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
        if (indexes.find(pair.first) == indexes.end()) {
            boost::put(boost::vertex_name_t(), g, i, pair.first);
            auto vFirst = boost::vertex(i, g);
            indexes[pair.first] = vFirst;
            names[vFirst] = pair.first;
            i++;
        }
        if (indexes.find(pair.second) == indexes.end()) {
            boost::put(boost::vertex_name_t(), g, i, pair.second);
            auto vSecond = boost::vertex(i, g);
            indexes[pair.second] = vSecond;
            names[vSecond] = pair.second;
            i++;
        }
        boost::add_edge(indexes.at(pair.first), indexes.at(pair.second), g);
    }
    mGraph = g;
    mVertexMap = names;
    mIndexMap = indexes;
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
    traverse([&](auto first, auto second) {
        std::cout
            << mVertexMap.at(first)
            << '(' << first << ')'
            << '-'
            << mVertexMap.at(second)
            << '(' << second << ')'
            << std::endl;
    });
}

void GraphView::error(const std::exception& ex)
{
    std::cerr << "[Error]: " << ex.what() << std::endl;
}

void GraphView::search(const std::string_view& from, const std::string_view& to)
{
    std::vector<std::vector<int>> adjList(mVertexMap.size() - 1);
    traverse([&](auto first, auto second) {
        adjList[first].push_back(second);
    });
    std::size_t size = adjList.size() * 2;
    auto source = mIndexMap.at(std::string(from));
    auto goal = mIndexMap.at(std::string(to));
    std::vector<bool> visited(size, false);
    std::vector<int> paths(size);
    int pathIndex = 0;
    recursiveSearch(source, goal, visited, paths, pathIndex, adjList);
}

void GraphView::traverse(std::function<void(unsigned long, unsigned long)> callback)
{
    std::vector<std::vector<int>> g;
    TGraph* graph;
    std::map<TGraph::vertex_descriptor, std::string>* map;
    std::tie(graph, map) = get();
    auto vertices = boost::vertices(*graph);
    for (auto vit = vertices.first; vit != vertices.second; ++vit) {
        auto neighbors = boost::adjacent_vertices(*vit, *graph);
        for (auto nit = neighbors.first; nit != neighbors.second; ++nit) {
            std::invoke(callback, *vit, *nit);
        }
    }
}

void GraphView::recursiveSearch(int from,
    int to, std::vector<bool>& visited,
    std::vector<int>& paths, int pathIndex,
    std::vector<std::vector<int>>& adjList)
{
    visited[from] = true;
    paths[pathIndex] = from;
    pathIndex++;
    if (from == to) {
        for (int i = 0; i < pathIndex; ++i) {
            std::cout
                << mVertexMap.at(paths[i])
                << '(' << paths[i] << ')';
            if (i < pathIndex - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    } else {
        std::vector<int>::iterator it;
        for (it = adjList[from].begin(); it != adjList[from].end(); ++it) {
            if (!visited[*it]) {
                recursiveSearch(*it, to, visited, paths, pathIndex, adjList);
            }
        }
    }
    pathIndex--;
    visited[from] = false;
}
