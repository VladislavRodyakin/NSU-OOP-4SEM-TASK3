#include <iostream>
#include <fstream>
#include "dijkstra.hpp"
#include "utils.hpp"

int main(int argc, char*argv []) {
    using namespace std;
    string path;
    if (argc == 1){
        path = "Input.txt";
    }
    else {
        path = argv[2];
    }

    ifstream inp(path);
    if(!inp.is_open()) {
        cout << "FILE IS NOT OPEN!";
        return 0;
    }
    try {
        Graph g;
        read(g, inp);
        showGraph(g.getStorage());
        string start = "Moscow";
        string finish = "Krasnoyarsk";
        Dijkstra d;
        d.route(g, start);
        showDistance(d.getDistances());
        showPrev(d.getPrev());
        showWay(d.getWay(finish));
    }
    catch(const GraphError& ex){
        cout << ex.what();
    }
    return 0;
}
