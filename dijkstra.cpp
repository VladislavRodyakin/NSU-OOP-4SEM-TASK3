
#include "dijkstra.hpp"



void Graph::insert(const std::string& name1, const std::string& name2, int val) {

    //проверяем есть дорога от name1 до name2
    if(graph[name1].count(name2)) {
        std::string problem = "From " + name1 + " to " + name2 + " path already exists";
        throw GraphError(problem);
    }
    //заполняем несимметричным образом
    graph[name1][name2] = val;
    graph[name2];
}

void read(Graph& G, std::istream& is_)
{
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





void Dijkstra::route(const Graph &g, const std::string &start) {
    Start = start;
    if(!distances.empty()) {
        distances.clear();
        prev.clear();
    }
   auto& graph = g.getStorage();

    if(graph.empty()) {
        return;
    }
    if(graph.count(start) == 0) {
        return;
    }
    for(const auto& pair : graph) {
        distances.insert({pair.first, Inf});
    }
    distances[start] = 0;
    std::priority_queue <std::pair <int, std::string>> queue;
    queue.push(make_pair(0,start));
    while (!queue.empty()) {
        //в очереди элементы по убыванию, значит сортируем отрицательные числа
        int len = -queue.top().first;
        std::string v = queue.top().second;
        queue.pop();
        if (len > distances[v]) {
            continue;
        }

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
}

 std::vector<std:: string> Dijkstra::getWay(const std::string &finish) const {
    auto connection  = prev.find(finish);
    std::vector <std:: string> Way;
    if(connection == prev.end()) {
        return Way;
    }
    Way.push_back(Start);
    while(connection->second != Start) {
        Way.push_back(connection->second);
        connection = prev.find(connection->second);
    }
    Way.push_back(finish);
    return Way;

}
