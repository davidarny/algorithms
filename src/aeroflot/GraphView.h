#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <functional>
#include <string>

typedef boost::property<boost::vertex_name_t, std::string> TVertexNameProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, TVertexNameProperty> TGraph;

class GraphView {
private:
    TGraph mGraph;
    std::map<TGraph::vertex_descriptor, std::string> mVertexMap;
    std::map<std::string, TGraph::vertex_descriptor> mIndexMap;

    std::pair<std::string, std::string> getFromToPair(const std::string& path);

    void traverse(std::function<void(unsigned long, unsigned long)> callback);

    void recursiveSearch(int from, int to,
        std::vector<bool>& visited,
        std::vector<int>& paths,
        int pathIndex,
        std::vector<std::vector<int>>& adjList);

public:
    void parse(const std::string_view& path);

    std::pair<TGraph*, std::map<TGraph::vertex_descriptor, std::string>*> get();

    void print();

    void error(const std::exception& ex);

    void search(const std::string_view& from, const std::string_view& to);
};

#endif //ALGORITHMS_GRAPH_H
