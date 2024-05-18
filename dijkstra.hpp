#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <algorithm>


class Graph {
public:
    Graph() = default;
    explicit Graph(const std::map <std::string, std::map<std::string, int>>& graph): m_graph{graph} {};
    
    void insert(const std::string& name1, const std::string& name2, int val);
    
    const std::map<std::string, std::map<std::string, int>>&  getStorage() const {
        return m_graph;
    }

private:
    std::map<std::string, std::map<std::string, int>> m_graph; // unordered maps
};

void read_into_graph(Graph& G, std::istream & is_);

class Dijkstra {
public:
    void route(const Graph& g, const std::string& start); // Dijkstra's algorithm
    std::vector <std::string> getWay(const std::string& finish) const; // returns way from start to finish

    int getKilometres(const std::string& finish); // distance from start to finish

    const std::map <std::string,int>& getDistances() const {
        return m_distances;
    }
    const std::map <std::string, std::string>& getPrev() const { //previous route
        return m_prev;
    }
private:
    std::string m_start;
    std::map <std::string,int> m_distances;
    std::map <std::string, std::string> m_prev;
};

//let's try it
class GraphError: public std::exception {
public:
    explicit GraphError(const std::string& message): m_message{message} {}
    const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};
