#include <boost/algorithm/string.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include <fstream>
#include <iostream>
#include <queue>
#include <string_view>
#include <vector>

#include "GraphView.h"
#include "cpp-console-table/CppConsoleTable.hpp"

using ConsoleTable = samilton::ConsoleTable;

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
        auto tuple = getFromToPair(vertex);
        unsigned long vFirst, vSecond;
        if (indexes.find(std::get<0>(tuple)) == indexes.end()) {
            boost::put(boost::vertex_name_t(), g, i, std::get<0>(tuple));
            vFirst = boost::vertex(i, g);
            indexes[std::get<0>(tuple)] = vFirst;
            names[vFirst] = std::get<0>(tuple);
            i++;
        } else {
            vFirst = (*indexes.find(std::get<0>(tuple))).second;
        }
        if (indexes.find(std::get<1>(tuple)) == indexes.end()) {
            boost::put(boost::vertex_name_t(), g, i, std::get<1>(tuple));
            vSecond = boost::vertex(i, g);
            indexes[std::get<1>(tuple)] = vSecond;
            names[vSecond] = std::get<1>(tuple);
            i++;
        } else {
            vSecond = (*indexes.find(std::get<1>(tuple))).second;
        }
        boost::add_edge(indexes.at(std::get<0>(tuple)), indexes.at(std::get<1>(tuple)), g);
        mHashMap[std::pair(vFirst, vSecond)] = std::get<2>(tuple);
    }
    mGraph = g;
    mVertexMap = names;
    mIndexMap = indexes;
}

std::tuple<std::string, std::string, std::string> GraphView::getFromToPair(const std::string& path)
{
    std::vector<std::string> strs;
    boost::split(strs, path, boost::is_any_of("-"));
    auto tuple = std::tuple<std::string, std::string, std::string>(strs.at(0), strs.at(1), strs.at(2));
    return tuple;
}

std::pair<TGraph*, std::map<TGraph::vertex_descriptor, std::string>*> GraphView::get()
{
    return std::pair(&mGraph, &mVertexMap);
}

void GraphView::print()
{
    if (mVertexMap.size() == 0) {
        return;
    }
    std::size_t indent = 1;
    ConsoleTable table(indent, indent);
    ConsoleTable::TableChars chars;
    chars.centreSeparation = '|';
    chars.leftRightSimple = '|';
    chars.topDownSimple = '-';
    chars.leftSeparation = '+';
    chars.rightSeparation = '+';
    chars.downSeparation = '+';
    chars.topSeparation = '+';
    chars.downLeft = '+';
    chars.downRight = '+';
    chars.topLeft = '+';
    chars.topRight = '+';
    table.setTableChars(chars);
    std::size_t index = 0;
    table[index][0] = "From";
    table[index][1] = "To";
    table[index][2] = "Flight Code";
    index++;
    traverse([&](auto first, auto second) {
        table[index][0] = mVertexMap.at(first);
        table[index][1] = mVertexMap.at(second);
        table[index][2] = mHashMap[std::pair(first, second)];
        index++;
    });
    std::cout << table;
}

void GraphView::error(const std::exception& ex)
{
    std::cerr << "[ERROR]: " << ex.what() << std::endl;
}

void GraphView::search(const std::string_view& from, const std::string_view& to, const std::string_view& type)
{
    std::vector<std::vector<int>> adj(mVertexMap.size());
    traverse([&](auto first, auto second) {
        adj[first].push_back(second);
    });
    std::size_t size = adj.size() * 2;
    if (mIndexMap.find(std::string(from)) == mIndexMap.end()) {
        throw std::runtime_error("No city \"" + std::string(from) + "\" found!");
    }
    if (mIndexMap.find(std::string(to)) == mIndexMap.end()) {
        throw std::runtime_error("No city \"" + std::string(to) + "\" found!");
    }
    int source = static_cast<int>(mIndexMap.at(std::string(from)));
    int goal = static_cast<int>(mIndexMap.at(std::string(to)));
    if (type == search_t[ESearchType::DFS]) {
        std::vector<bool> visited(size, false);
        std::vector<int> paths(size);
        int pathIndex = 0;
        dfs(source, goal, visited, paths, pathIndex, adj);
    } else if (type == search_t[ESearchType::BFS]) {
        bfs(source, goal, adj);
    } else {
        throw std::runtime_error("Unsupported search type " + std::string(type));
    }
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

void GraphView::dfs(int from,
    int to, std::vector<bool>& visited,
    std::vector<int>& paths, int pathIndex,
    std::vector<std::vector<int>>& adj)
{
    visited[from] = true;
    paths[pathIndex] = from;
    pathIndex++;
    constexpr auto printFoundPath = [](int pathIndex,
                                        const std::map<TGraph::vertex_descriptor, std::string>& vertexMap,
                                        const std::vector<int>& paths) {
        for (int i = 0; i < pathIndex; ++i) {
            std::cout << vertexMap.at(static_cast<unsigned long>(paths[i]));
            if (i < pathIndex - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    };
    if (from == to) {
        if (mIsDebugMode) {
            std::cout << "[FOUND]" << ' ';
        }
        printFoundPath(pathIndex, mVertexMap, paths);
    } else {
        std::vector<int>::iterator it;
        for (it = adj[from].begin(); it != adj[from].end(); ++it) {
            if (!visited[*it]) {
                if (mIsDebugMode) {
                    std::cout << "[DEBUG]" << ' ';
                    printFoundPath(pathIndex, mVertexMap, paths);
                }
                dfs(*it, to, visited, paths, pathIndex, adj);
            }
        }
    }
    pathIndex--;
    visited[from] = false;
}

void GraphView::bfs(int from, int to, std::vector<std::vector<int>>& adj)
{
    constexpr auto isNotVisited = [](int x, std::vector<int>& path) -> bool {
        for (auto& chunk : path) {
            if (chunk == x) {
                return false;
            }
        }
        return true;
    };
    constexpr auto printFoundPath = [](std::vector<int>& path,
                                        const std::map<TGraph::vertex_descriptor, std::string>& vertexMap) {
        for (std::size_t i = 0; i < path.size(); ++i) {
            std::cout << vertexMap.at(static_cast<unsigned long>(path[i]));
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    };
    std::queue<std::vector<int>> queue;
    std::vector<int> path;
    path.push_back(from);
    queue.push(path);
    while (!queue.empty()) {
        path = queue.front();
        queue.pop();
        int last = path[path.size() - 1];
        if (last == to) {
            if (mIsDebugMode) {
                std::cout << "[FOUND]" << ' ';
            }
            printFoundPath(path, mVertexMap);
        }
        auto children = adj[last];
        if (children.empty()) {
            continue;
        }
        for (std::size_t i = 0; i < children.size(); ++i) {
            if (isNotVisited(adj[last][i], path)) {
                std::vector<int> nextPath(path);
                if (mIsDebugMode) {
                    std::cout << "[DEBUG]" << ' ';
                    printFoundPath(nextPath, mVertexMap);
                }
                nextPath.push_back(adj[last][i]);
                queue.push(nextPath);
            }
        }
    }
}

void GraphView::debug(const bool debug)
{
    mIsDebugMode = debug;
}
