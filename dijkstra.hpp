#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <algorithm>

const int Inf = std::numeric_limits<int>::max();

class Graph {
public:
    void insert(const std::string& name1, const std::string& name2, int val);
    const std::map <std::string, std::map <std::string, int>>&  getStorage () const {
        return graph;
    }
    explicit Graph(const std::map <std::string, std::map<std::string, int>>& graph_) : graph{graph_} {};
    Graph() = default;

private:
    std::map <std::string, std::map <std::string, int>> graph;
};

void read(Graph& G, std::istream & is_);


//let's try it
class GraphError: public std::exception {
public:
    explicit GraphError(const std::string& message): message{message} {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};



class Dijkstra {
public:
    void route (const Graph& g, const std::string& start); // Dijkstra's algorithm
    std::vector <std::string> getWay(const std::string& finish) const; // returns way from start to finish

    int getKilometres (const std::string& finish) { // distance from start to finish
        if(distances.count(finish)) {
            return distances[finish];
        }
        return 0;
    }

    //методы доступа
    // for what purpose?
    const std::map <std::string,int>& getDistances() const {
        return distances; //rename to distances
    }
    const std::map <std::string, std::string>& getPrev() const { // a previous route?
        return prev;
    }
private:
    std::string Start;
    std::map <std::string,int> distances;
    std::map <std::string, std::string> prev;
};

