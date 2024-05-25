#include "utils.hpp"

void Dj_utils::read_into_graph(Graph& G, std::istream& is_){
    std::string line;
    while (std::getline(is_, line)) {
        if (line.empty())
            continue;
        std::string name1, name2;
        int val;
        std::istringstream is(line);
        if (is >> name1 >> name2 >> val) {
            G.insert(name1, name2, val);
        }
        else {
            throw GraphError("Invalid line format:" + line);
        }
    }
}


void Dj_utils::showGraph(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph) {
    if(graph.empty()) {
        return;
    }
    std:: cout << "Graph storage:\n";
    for(auto const& pair: graph) { // redo according to c++20
        std::cout << pair.first << " connected to: ";
        for(const auto& x: pair.second) { // redo according to c++20
            std::cout << x.first << " (distance = " << x.second <<"); ";
        }
        std::cout << "\n";
    }
}


void Dj_utils::showDistance(const std::unordered_map<std::string,int>& distance)  {
    if(distance.empty()) {
        return;
    }
    std:: cout << "Distances:\n";
    for(auto const& pair: distance) { // redo according to c++20
        std::cout << "to " <<  pair.first << " is " << pair.second << "\n";
    }
}


void Dj_utils::showPrev(const std::unordered_map<std::string, std::string>& prev ) {
    std:: cout << "Previous ways:\n";
    for(auto& town: prev) { // redo according to c++20
        std:: cout << town.first << " " << town.second << "\n";
    }
}


void Dj_utils::showWay(const std::vector<std:: string>& Way) {
    std:: cout << "The shortest way:\n";
    for(auto& path: Way ) {
        std:: cout << path << " ";
    }
}

