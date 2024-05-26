#include <limits>
#include "dijkstra.hpp"

void Graph::insert(const std::string& name1, const std::string& name2, int val) {

    //checking whether there is a path from name1 to name2
    if(m_graph[name1].count(name2)) {
        std::string problem = "From " + name1 + " to " + name2 + " path already exists";
        throw GraphError(problem);
    }
    //asymmetric filling
    m_graph[name1][name2] = val;
    m_graph[name2];
}

void Dijkstra::updateCityDistances(const std::string v, std::unordered_map<std::string, int>& distances,
                        std::priority_queue <std::pair <int, std::string>>& queue,
                        const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph,
                        std::unordered_map<std::string, std::string>& prev) const{

    auto v_it = graph.find(v);

    for(const auto& city_roads : v_it->second) {
        int length = city_roads.second;
        std::string to = city_roads.first;

        if((distances[to] > distances[v] + length) && length > 0) {
            distances[to] = distances[v] + length;
            prev[to] = v;
            queue.push(make_pair(-distances[to],to));
        }
    }
}

void Dijkstra::fillWay(const std::string start, std::unordered_map<std::string, int>& distances,
            const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph,
            std::unordered_map<std::string, std::string>& prev) const{

    std::priority_queue <std::pair <int, std::string>> queue;
    queue.push(make_pair(0,start));
    while (!queue.empty()) {
        //queue holds elements in descending order
        //so we're sorting negative numbers
        int len = -queue.top().first;
        std::string v = queue.top().second;
        queue.pop();
        if (len > distances[v]) {
            continue;
        }

        updateCityDistances(v, distances, queue, graph, prev);
    }
}

std::vector<std::string> Dijkstra::findWay(const std::string& start, const std::string& finish,
                                std::unordered_map<std::string, std::string>& prev) const{

    auto connection = prev.find(finish);
    std::vector<std::string> Way;

    if(connection == prev.end()) {
        return Way;
    }

    Way.push_back(start);
    while(connection->second != start) {
        Way.push_back(connection->second);
        connection = prev.find(connection->second);
    }

    Way.push_back(finish);
    return Way;
}


std::vector<std::string> Dijkstra::getWay(const Graph& g, const std::string& start, const std::string& finish) const{
    auto graph = g.getStorage();
    if(graph.empty()) {
        throw GraphError("Graph is empty");
    }
    if(graph.count(start) == 0) {
        throw GraphError("Start city doesn't exist");
    }
    if(graph.count(finish) == 0) {
        throw GraphError("Finish city doesn't exist");
    }

    std::unordered_map<std::string,int> distances;
    std::unordered_map<std::string, std::string> prev;
    const int Inf = std::numeric_limits<int>::max();
    for(const auto& pair : graph) {
        distances.insert({pair.first, Inf});
    }
    distances[start] = 0;

    fillWay(start, distances, graph, prev);
    
    if (distances[finish] == Inf) {
        throw GraphError("There is no way from start to finish");
    }

    return findWay(start, finish, prev);
}