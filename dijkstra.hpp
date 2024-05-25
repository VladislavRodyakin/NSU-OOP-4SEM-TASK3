#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <map>
#include <algorithm>


class Graph final{
    std::unordered_map<std::string, std::unordered_map<std::string, int>> m_graph; // unordered maps

public:
    Graph() = default;
    explicit Graph(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph): m_graph{graph} {};
    void insert(const std::string& name1, const std::string& name2, int val);
    
    const std::unordered_map<std::string, std::unordered_map<std::string, int>>&  getStorage() const { return m_graph; }
};


class Dijkstra final{
    std::string m_start;
    std::unordered_map<std::string,int> m_distances;
    std::unordered_map<std::string, std::string> m_prev;

public:
    void route(const Graph& g, const std::string& start); // Dijkstra's algorithm
    std::vector<std::string> getWay(const std::string& finish) const; // returns way from start to finish

    int getKilometres(const std::string& finish); // distance from start to finish

    const std::unordered_map<std::string,int>& getDistances() const { return m_distances; }
    const std::unordered_map<std::string, std::string>& getPrev() const { return m_prev; }
};

//let's try it
class GraphError final: public std::exception {
    std::string m_message;

public:
    explicit GraphError(const std::string& message): m_message{message} {}
    const char* what() const noexcept override {
        return m_message.c_str();
    }
};
