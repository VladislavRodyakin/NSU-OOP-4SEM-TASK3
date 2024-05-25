#include <iostream>
#include <fstream>
#include "dijkstra.hpp"
#include "utils.hpp"

int main(int argc, char*argv []) {
    using namespace std;
    string path;
    if (argc == 1){
        path = "input.txt";
    }
    else {
        path = argv[1];
    }

    ifstream inp(path);
    if(!inp.is_open()) {
        cout << "FILE IS NOT OPEN!";
        return 0;
    }
    try {
        Graph g;
        Dj_utils::read_into_graph(g, inp);
        Dj_utils::showGraph(g.getStorage());
        string start = "Moscow";
        string finish = "Krasnoyarsk";
        Dijkstra d;
        d.route(g, start);
        Dj_utils::showDistance(d.getDistances());
        Dj_utils::showPrev(d.getPrev());
        Dj_utils::showWay(d.getWay(finish));
    }
    catch(const GraphError& ex){
        cout << ex.what();
    }
    return 0;
}
