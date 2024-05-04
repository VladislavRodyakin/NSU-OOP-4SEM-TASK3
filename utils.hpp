#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "dijkstra.hpp"

//separate namespace
void read(Graph& G, std::istream & is_); // to parser
void showGraph(const std::map <std::string, std::map <std::string, int>>& graph);
void showDistance(const std::map <std::string,int>& distance);
void showPrev(const std::map <std::string, std::string>& prev );
void showWay(const std::vector<std:: string>& Way);
