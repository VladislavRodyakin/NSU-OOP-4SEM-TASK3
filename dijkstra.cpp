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

void read_into_graph(Graph& G, std::istream& is_)
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
    m_start = start;
    const int Inf = std::numeric_limits<int>::max();
    if(!m_distances.empty()) {
        m_distances.clear();
        m_prev.clear();
    }
   auto& graph = g.getStorage();

    if(graph.empty()) {
        return;
    }
    if(graph.count(start) == 0) {
        return;
    }
    for(const auto& pair : graph) {
        m_distances.insert({pair.first, Inf});
    }
    m_distances[start] = 0;
    std::priority_queue <std::pair <int, std::string>> queue;
    queue.push(make_pair(0,start));
    while (!queue.empty()) {
        //queue holds elements in descending order
        //so we're sorting negative numbers
        int len = -queue.top().first;
        std::string v = queue.top().second;
        queue.pop();
        if (len > m_distances[v]) {
            continue;
        }

        auto v_it = graph.find(v);
        for(const auto& city_roads : v_it->second) {
            int length = city_roads.second;
            std::string to = city_roads.first;
            if((m_distances[to] > m_distances[v] + length) && length > 0) {
                m_distances[to] = m_distances[v] + length;
                m_prev[to] = v;
                queue.push(make_pair(-m_distances[to],to));
            }
        }
    }
}

int Dijkstra::getKilometres(const std::string &finish){
    if(m_distances.count(finish)!=0) {
        return m_distances[finish];
    }
    return 0;
}

 std::vector<std::string> Dijkstra::getWay(const std::string &finish) const {
    auto connection = m_prev.find(finish);
    std::vector<std::string> Way;
    if(connection == m_prev.end()) {
        return Way;
    }
    Way.push_back(m_start);
    while(connection->second != m_start) {
        Way.push_back(connection->second);
        connection = m_prev.find(connection->second);
    }
    Way.push_back(finish);
    return Way;
}
