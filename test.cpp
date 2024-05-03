
#include "gtest/gtest.h"
#include "../dijkstra.hpp"
#include <map>

using namespace std;

TEST(Insert, NoErrors) {
    Graph g;
    g.insert("Moscow", "Toronto", 10);
    g.insert("Moscow", "Novosibirsk", 15);
    g.insert("Novosibirsk", "Toronto", 20);
    g.insert("Kiev", "Toronto", 30);
    map <string, map <string, int>> check = g.getStorage();
    ASSERT_TRUE(check["Kiev"]["Toronto"] == 30);
    ASSERT_TRUE(check["Moscow"]["Toronto"] == 10);
    ASSERT_TRUE(check["Novosibirsk"]["Toronto"] == 20);
    ASSERT_TRUE(check["Toronto"].empty());

}

TEST(Insert, RepeatedPath) {
    Graph g;
    g.insert("Moscow", "Toronto", 10);
    g.insert("Moscow", "Novosibirsk", 15);
    ASSERT_THROW(g.insert("Moscow", "Toronto", 20),GraphError );
    g.insert("Novosibirsk", "Kiev", 15);
    ASSERT_THROW(g.insert("Moscow", "Novosibirsk", 20),GraphError );
    map <string, map <string, int>> check = g.getStorage();
    ASSERT_TRUE(check["Novosibirsk"]["Kiev"] == 15);


}

TEST(Reading,NoErrors) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Moscow Krasnoyarsk 2\n"
                      "Moscow Kiev 9"};
    map <string, map <string, int>> graphCheck = { {"Moscow",{
        {"Novosibirsk", 7},
        {"Krasnoyarsk", 2},
        {"Kiev", 9} } },
        { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };

    Graph g;
    read(g, inp);
    map <string, map <string, int>> graph = g.getStorage();
    ASSERT_TRUE (graphCheck == graph);

}
TEST(Reading,EmptyLines)  {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "\n"
                      "Moscow Krasnoyarsk 2\n"
                      "\n"
                      "\n"
                      "Moscow Kiev 9"
                      };
    map <string, map <string, int>> graphCheck = { {"Moscow",{
                                                                     {"Novosibirsk", 7},
                                                                     {"Krasnoyarsk", 2},
                                                                     {"Kiev", 9}} },
                                                   { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    Graph g;
    read(g, inp);
    map <string, map <string, int>> graph = g.getStorage();
    ASSERT_TRUE (graphCheck == graph);
}


TEST(Reading,InvalidLines)  {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "  \n"};
    Graph g;
    ASSERT_THROW(read(g, inp),GraphError);

    stringstream inp2 {" 8 Moscow Novosibirsk 7"};
    ASSERT_THROW(read(g, inp2),GraphError);

    stringstream inp3 {"Moscow - Novosibirsk 7"};
    ASSERT_THROW(read(g, inp3),GraphError);


}
TEST (Reading, RepeatedLines) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Moscow Krasnoyarsk 2\n"
                      "Moscow Novosibirsk 9"};
    Graph g;
    ASSERT_THROW(read(g, inp),GraphError);

}
TEST(Dijkstra, NoErrors) {
    map <string, map <string, int>> graph = { {"Moscow",{
                                                                     {"Novosibirsk", 7},
                                                                     {"Krasnoyarsk", 2},
                                                                     {"Kiev", 9} } },
                                                   { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    Graph G(graph);
    Dijkstra d;
    d.route(G, "Moscow");
    map <string, int> check = {{"Kiev", 9},{"Krasnoyarsk", 2},{"Moscow", 0}, {"Novosibirsk", 7} };
    ASSERT_TRUE(check == d.getDistances());
}

TEST(Dijkstra, NoStart) {
    map <string, map <string, int>> graph = { {"Moscow",{
                                                                {"Novosibirsk", 7},
                                                                {"Krasnoyarsk", 2},
                                                                {"Kiev", 9} } },
                                              { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    Graph G(graph);
    Dijkstra d;
    d.route(G, "Berdsk");
    ASSERT_TRUE(d.getDistances().empty());
    ASSERT_TRUE(d.getPrev().empty());
    ASSERT_EQ(d.getKilometres("Moscow"),0);
}

TEST(Dijkstra, NoFinish) {
    map <string, map <string, int>> graph = { {"Moscow",{
                                                                {"Novosibirsk", 7},
                                                                {"Krasnoyarsk", 2},
                                                                {"Kiev", 9} } },
                                              { "Novosibirsk", {} },{ "Krasnoyarsk", {} }, { "Kiev", {} } };
    Graph G(graph);
    Dijkstra d;
    d.route(G, "Moscow");
    ASSERT_EQ(d.getKilometres("Toronto"),0);

}
TEST(Dijkstra, EmptyGraph) {
    Graph g;
    Dijkstra D;
    D.route(g, "Monako");
    ASSERT_EQ(0, D.getKilometres("Moscow"));

}


TEST (DijkAndReading, NoErrors) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Novosibirsk Krasnoyarsk 2\n"
                      "Moscow Krasnoyarsk 150"};

    Graph g;
    Dijkstra D;
    read(g, inp);
    D.route(g, "Moscow");
    ASSERT_EQ(D.getKilometres("Novosibirsk"), 7);
    ASSERT_EQ(D.getKilometres("Krasnoyarsk"), 9);

    D.route(g,"Novosibirsk");
    ASSERT_EQ(D.getKilometres("Krasnoyarsk"), 2);

}

TEST(DijkAndReading, NoWay) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Novosibirsk Krasnoyarsk 2\n"
                      "Moscow Krasnoyarsk 150"};
    Graph g;
    Dijkstra D;
    read(g,inp);
    D.route(g, "Monako");
    ASSERT_EQ(0, D.getKilometres("Moscow"));
    D.route(g,"Moscow");
    ASSERT_EQ(0,D.getKilometres("Kiev"));

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
    Graph g;
    read(g,inp);
    Dijkstra D;

    D.route(g, "Novosibirsk");
    vector <string> way = D.getWay("Omsk");
    ASSERT_EQ(way[0], "Novosibirsk");
    ASSERT_EQ(way[1], "Omsk");

    way = D.getWay("Krasnoyarsk");
    ASSERT_EQ(way[0], "Novosibirsk");
    ASSERT_EQ(way[1], "Toronto");
    ASSERT_EQ(way[2], "Krasnoyarsk");

    D.route(g, "Moscow");
    way = D.getWay("Krasnoyarsk");
    ASSERT_EQ(way[0], "Moscow");
    ASSERT_EQ(way[1], "Toronto");
    ASSERT_EQ(way[2], "Krasnoyarsk");


}

TEST(DijkAndReading, GetWayErrors) {
    stringstream inp {"Moscow Novosibirsk 7\n"
                      "Moscow Toronto 9\n"
                      "Moscow Krasnoyarsk 14\n"
                      "Novosibirsk Toronto 10\n"
                      "Novosibirsk Omsk 15\n"
                      "Omsk Toronto  11\n"
                      "Toronto Krasnoyarsk 2\n"
                      "Krasnoyarsk Kiev 9\n"
                      "Kiev Omsk  6"};
    Graph g;
    read(g,inp);
    Dijkstra D;
    D.route(g, "Novosibirsk");
    vector <string> way = D.getWay("Moscow");
    ASSERT_TRUE(way.empty());

    way = D.getWay("Monako");
    ASSERT_TRUE(way.empty());
}
