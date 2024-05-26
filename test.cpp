#include <gtest/gtest.h>
#include <map>
#include "dijkstra.hpp"
#include "utils.hpp"
using namespace std;

TEST(Insert, NoErrors) {
    Graph graph;
    graph.insert("Moscow", "Toronto", 10);
    graph.insert("Moscow", "Novosibirsk", 15);
    graph.insert("Novosibirsk", "Toronto", 20);
    graph.insert("Kiev", "Toronto", 30);
    unordered_map<string, unordered_map<string, int>> check = graph.getStorage();

    ASSERT_TRUE(check["Kiev"]["Toronto"] == 30);
    ASSERT_TRUE(check["Moscow"]["Toronto"] == 10);
    ASSERT_TRUE(check["Novosibirsk"]["Toronto"] == 20);
    ASSERT_TRUE(check["Toronto"].empty());
}

TEST(Insert, RepeatedPath) {
    Graph graph;
    graph.insert("Moscow", "Toronto", 10);
    graph.insert("Moscow", "Novosibirsk", 15);
    ASSERT_THROW(graph.insert("Moscow", "Toronto", 20), GraphError);

    graph.insert("Novosibirsk", "Kiev", 15);
    ASSERT_THROW(graph.insert("Moscow", "Novosibirsk", 20), GraphError);

    unordered_map<string, unordered_map<string, int>> check = graph.getStorage();
    ASSERT_TRUE(check["Novosibirsk"]["Kiev"] == 15);
}

TEST(Reading,NoErrors) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Moscow Krasnoyarsk 2\n"
                      "Moscow Kiev 9"};
    unordered_map<string, unordered_map<string, int>> graphCheck = { {"Moscow",{
        {"Novosibirsk", 7},
        {"Krasnoyarsk", 2},
        {"Kiev", 9} } },
        { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };

    Graph graph;
    ASSERT_NO_THROW(Dj_utils::read_into_graph(graph, inp));
    unordered_map<string, unordered_map<string, int>> graph_storage = graph.getStorage();
    ASSERT_TRUE(graphCheck == graph_storage);
}

TEST(Reading,EmptyLines)  {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "\n"
                      "Moscow Krasnoyarsk 2\n"
                      "\n"
                      "\n"
                      "Moscow Kiev 9"
                      };
    unordered_map<string, unordered_map<string, int>> graphCheck = { {"Moscow",{
                                                                     {"Novosibirsk", 7},
                                                                     {"Krasnoyarsk", 2},
                                                                     {"Kiev", 9}} },
                                                   { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    
    Graph graph;
    ASSERT_NO_THROW(Dj_utils::read_into_graph(graph, inp));
    unordered_map<string, unordered_map<string, int>> graph_storage = graph.getStorage();
    ASSERT_TRUE(graphCheck == graph_storage);
}


TEST(Reading,InvalidLines)  {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "  \n"};
    Graph graph;
    ASSERT_THROW(Dj_utils::read_into_graph(graph, inp), GraphError);

    stringstream inp2 {" 8 Moscow Novosibirsk 7"};
    ASSERT_THROW(Dj_utils::read_into_graph(graph, inp2), GraphError);

    stringstream inp3 {"Moscow - Novosibirsk 7"};
    ASSERT_THROW(Dj_utils::read_into_graph(graph, inp3) ,GraphError);
}

TEST (Reading, RepeatedLines) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Moscow Krasnoyarsk 2\n"
                      "Moscow Novosibirsk 9"};
    Graph graph;
    ASSERT_THROW(Dj_utils::read_into_graph(graph, inp), GraphError);
}

TEST(Dijkstra, NoErrors) {
    unordered_map<string, unordered_map<string, int>> graph = { {"Moscow",{
                                                                     {"Novosibirsk", 7},
                                                                     {"Krasnoyarsk", 2},
                                                                     {"Kiev", 9} } },
                                                   { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    Graph G(graph);
    Dijkstra d;
    ASSERT_NO_THROW(d.getWay(G, "Moscow", "Kiev"));
}

TEST(Dijkstra, NoStart) {
    unordered_map<string, unordered_map<string, int>> graph = { {"Moscow",{
                                                                {"Novosibirsk", 7},
                                                                {"Krasnoyarsk", 2},
                                                                {"Kiev", 9} } },
                                              { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    Graph G(graph);
    Dijkstra d;
    
    ASSERT_THROW(d.getWay(G, "Berdsk", "Kiev"), GraphError);
    try {
        d.getWay(G, "Berdsk", "Kiev");
    }
    catch (const GraphError& ex) {
        ASSERT_STREQ(ex.what(), "Start city doesn't exist");
    }
}


TEST(Dijkstra, NoFinish) {
    unordered_map<string, unordered_map<string, int>> graph = { {"Moscow",{
                                                                {"Novosibirsk", 7},
                                                                {"Krasnoyarsk", 2},
                                                                {"Kiev", 9} } },
                                              { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    Graph G(graph);
    Dijkstra d;
    
    ASSERT_THROW(d.getWay(G, "Moscow", "Toronto"), GraphError);
    try {
        d.getWay(G, "Moscow", "Toronto");
    }
    catch (const GraphError& ex) {
        ASSERT_STREQ(ex.what(), "Finish city doesn't exist");
    }
}

TEST(Dijkstra, EmptyGraph) {
    Graph graph;
    Dijkstra D;
    
    ASSERT_THROW(D.getWay(graph, "Monako", "Kiev"), GraphError);
    try {
        D.getWay(graph, "Monako", "Kiev");
    }
    catch (const GraphError& ex) {
        ASSERT_STREQ(ex.what(), "Graph is empty");
    }
}

TEST(DijkAndReading, NoErrors) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Novosibirsk Krasnoyarsk 2\n"
                      "Moscow Krasnoyarsk 150"};

    Graph graph;
    Dijkstra D;
    ASSERT_NO_THROW(Dj_utils::read_into_graph(graph, inp));
    
    ASSERT_NO_THROW(D.getWay(graph, "Moscow", "Novosibirsk"));
    vector<string> way = D.getWay(graph, "Moscow", "Novosibirsk");
    ASSERT_EQ(way[0], "Moscow");
    ASSERT_EQ(way[1], "Novosibirsk");
    
    ASSERT_NO_THROW(D.getWay(graph, "Novosibirsk", "Krasnoyarsk"));
    way = D.getWay(graph, "Novosibirsk", "Krasnoyarsk");
    ASSERT_EQ(way[0], "Novosibirsk");
    ASSERT_EQ(way[1], "Krasnoyarsk");
    
    ASSERT_NO_THROW(D.getWay(graph, "Moscow", "Krasnoyarsk"));
    way = D.getWay(graph, "Moscow", "Krasnoyarsk");
    ASSERT_EQ(way[0], "Moscow");
    ASSERT_EQ(way[1], "Novosibirsk");
    ASSERT_EQ(way[2], "Krasnoyarsk");
}

TEST(DijkAndReading, NoWay_Separate) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Novosibirsk Moscow 2\n"
                      "Toronto Krasnoyarsk 150\n"
                      "Krasnoyarsk Toronto 50"};

    Graph graph;
    Dijkstra D;
    Dj_utils::read_into_graph(graph,inp);
    
    ASSERT_THROW(D.getWay(graph, "Novosibirsk", "Krasnoyarsk"), GraphError);
    try {
        D.getWay(graph, "Novosibirsk", "Krasnoyarsk");
    }
    catch (const GraphError& ex) {
        ASSERT_STREQ(ex.what(), "There is no way from start to finish");
    }
}

TEST(DijkAndReading, NoWay_Directions) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Moscow Toronto 9\n"
                      "Moscow Krasnoyarsk 14\n"
                      "Novosibirsk Toronto 10\n"
                      "Novosibirsk Omsk 15\n"
                      "Omsk Toronto  11\n"
                      "Toronto Krasnoyarsk 2\n"
                      "Krasnoyarsk Kiev 9\n"
                      "Kiev Omsk  6"};

    Graph graph;
    Dijkstra D;
    Dj_utils::read_into_graph(graph,inp);
    
    ASSERT_THROW(D.getWay(graph, "Novosibirsk", "Moscow"), GraphError);
    try {
        D.getWay(graph, "Novosibirsk", "Moscow");
    }
    catch (const GraphError& ex) {
        ASSERT_STREQ(ex.what(), "There is no way from start to finish");
    }
}

TEST(DijkAndReading, GetWay) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                        "Moscow Toronto 9\n"
                        "Moscow Krasnoyarsk 14\n"
                        "Novosibirsk Toronto 10\n"
                        "Novosibirsk Omsk 15\n"
                        "Omsk Toronto  11\n"
                        "Toronto Krasnoyarsk 2\n"
                        "Krasnoyarsk Kiev 9\n"
                        "Kiev Omsk  6"};
    Graph graph;
    Dj_utils::read_into_graph(graph,inp);
    Dijkstra D;

    vector<string> way = D.getWay(graph, "Novosibirsk", "Omsk");
    ASSERT_EQ(way[0], "Novosibirsk");
    ASSERT_EQ(way[1], "Omsk");

    way = D.getWay(graph, "Novosibirsk", "Krasnoyarsk");
    ASSERT_EQ(way[0], "Novosibirsk");
    ASSERT_EQ(way[1], "Toronto");
    ASSERT_EQ(way[2], "Krasnoyarsk");

    way = D.getWay(graph, "Moscow", "Krasnoyarsk");
    ASSERT_EQ(way[0], "Moscow");
    ASSERT_EQ(way[1], "Toronto");
    ASSERT_EQ(way[2], "Krasnoyarsk");
}
