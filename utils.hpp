#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "dijkstra.hpp"

namespace Dj_utils {
    void showGraph(const std::map <std::string, std::map <std::string, int>>& graph);
    void showDistance(const std::map <std::string,int>& distance);
    void showPrev(const std::map <std::string, std::string>& prev );
    void showWay(const std::vector<std:: string>& Way);
}