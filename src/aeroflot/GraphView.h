#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <string>

typedef boost::property<boost::vertex_name_t, std::string> TVertexNameProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, TVertexNameProperty> TGraph;

class GraphView {
private:
    TGraph mGraph;
    std::map<TGraph::vertex_descriptor, std::string> mVertexMap;

    std::pair<std::string, std::string> getFromToPair(const std::string& path);

public:
    void parse(const std::string_view& path);

    std::pair<TGraph*, std::map<TGraph::vertex_descriptor, std::string>*> get();

    void print();

    void error(const std::exception& ex);
};

#endif //ALGORITHMS_GRAPH_H
