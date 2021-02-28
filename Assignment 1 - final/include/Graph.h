#ifndef GRAPH_H_
#define GRAPH_H_
using namespace std;
#include <vector>
#include "../include/Tree.h"
#include "../include/json.hpp"
using json=nlohmann:: json;



class Graph{
public:
    Graph(vector<vector<int>> matrix);
    Graph();

    void infectNode(int nodeInd);
    void makeACarrier(int nodeInd);
    int isInfected(int nodeInd);
    void removeAgent(int nodeInd); //to be used in CT class
    vector<int> getNeighbors(int);
    vector<vector<int>> getEdges() const;
    vector<int> getVertix();
    Tree* BFS(const Session&, int);
private:
    vector<vector<int>> edges;
    vector<int> vertix;//0 for healthy, 1 for carrier, 2 for infected
};

#endif
