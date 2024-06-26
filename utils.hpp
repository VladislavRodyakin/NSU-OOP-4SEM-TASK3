#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <unordered_map>
#include "dijkstra.hpp"

namespace Dj_utils{
    void read_into_graph(Graph& G, std::istream & is_);

    void showGraph(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph);
    void showWay(const std::vector<std:: string>& Way);
}