#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <functional>
#include <string>

typedef boost::property<boost::vertex_name_t, std::string> TVertexNameProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, TVertexNameProperty> TGraph;

class GraphView {
private:
    enum ESearchType {
        DFS = 0,
        BFS,
    };
    std::vector<std::string_view> search_t{ "DFS", "BFS" };

    TGraph mGraph;
    std::map<TGraph::vertex_descriptor, std::string> mVertexMap;
    std::map<std::string, TGraph::vertex_descriptor> mIndexMap;
    std::map<std::pair<int, int>, std::string> mHashMap;
    bool mIsDebugMode = false;

    std::tuple<std::string, std::string, std::string> getFromToPair(const std::string& path);

    void traverse(std::function<void(unsigned long, unsigned long)> callback);

    void dfs(int from, int to,
        std::vector<bool>& visited,
        std::vector<int>& paths,
        int pathIndex,
        std::vector<std::vector<int>>& adj);

    void bfs(int from, int to, std::vector<std::vector<int>>& adj);

public:
    void parse(const std::string_view& path);

    std::pair<TGraph*, std::map<TGraph::vertex_descriptor, std::string>*> get();

    void print();

    void error(const std::exception& ex);

    void search(const std::string_view& from, const std::string_view& to, const std::string_view& type);

    void debug(const bool debug);
};

#endif //ALGORITHMS_GRAPH_H
