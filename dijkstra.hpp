#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <map>
#include <algorithm>


class Graph final{
    std::unordered_map<std::string, std::unordered_map<std::string, int>> m_graph;

public:
    Graph() = default;
    explicit Graph(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph): m_graph{graph} {};
    void insert(const std::string& name1, const std::string& name2, int val);
    
    const std::unordered_map<std::string, std::unordered_map<std::string, int>>  getStorage() const { return m_graph; }
};


class Dijkstra final{
    void updateCityDistances(const std::string v, std::unordered_map<std::string, int>& distances,
                        std::priority_queue <std::pair <int, std::string>>& queue,
                        const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph,
                        std::unordered_map<std::string, std::string>& prev)const;

    void fillWay(const std::string start, std::unordered_map<std::string, int>& distances,
            const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph,
            std::unordered_map<std::string, std::string>& prev)const;

    std::vector<std::string> findWay(const std::string& start, const std::string& finish,
                                std::unordered_map<std::string, std::string>& prev)const;

public:
    std::vector<std::string> getWay(const Graph& g, const std::string& start, const std::string& finish) const;

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
