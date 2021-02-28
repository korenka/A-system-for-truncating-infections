#include "../include/Graph.h"
#include <iostream>
#include "../include/json.hpp"
#include <fstream>
#include "../include/Session.h"
using json=nlohmann:: json;
using namespace std;
#include <vector>
#include <queue>


Graph::Graph(vector<vector<int>> matrix):edges(matrix),vertix(){
    vertix.resize(matrix.size());
    for ( int i = 0; i < (int)edges.size(); ++i) {
        vertix[i] = 0;
    }
}

Graph::Graph():edges(),vertix(){}

void Graph::infectNode(int nodeInd) {vertix[nodeInd]=2;}
void Graph::makeACarrier(int nodeInd) {vertix[nodeInd]=1;}
int Graph::isInfected(int nodeInd) {return vertix[nodeInd];}
void Graph::removeAgent(int nodeInd) { //Removes infected agent from graph
    for ( int i  = 0; i < (int)edges.size(); ++i) {
        edges[nodeInd][i]= 0;
        edges[i][nodeInd] = 0;
    }
}
vector<int> Graph::getNeighbors(int node) {
    vector<int> output;
    for (int i = 0; i < (int)edges.size(); ++i) {
        if(edges[i][node]==1)
            output.push_back(i);
    }
    return output;
}

vector<vector<int>> Graph::getEdges() const {return edges;}
vector<int> Graph::getVertix() {return vertix;}
Tree* Graph::BFS(const Session& session, int srcNode) {
    Tree *output = Tree::createTree(session, srcNode);
    if (session.getTreeType() != Root) {
        queue<Tree *> q;
        vector<bool> visited;
        visited.resize(edges.size());
        for (int i = 0; i < (int)visited.size(); ++i) {
            visited[i] = false;
        }
        q.push(output);
        visited[srcNode] = true;
        while (!q.empty()) {
            Tree *v = q.front();
            q.pop();
            int cnt = 0;
            for (int u:Graph::getNeighbors(v->getNodeInd())) {
                if (!visited[u]) {
                    visited[u] = true;
                    Tree *tempC = Tree::createTree(session, u);
                    tempC->setDepth(v->getDepth() + 1);
                    v->addChild(*tempC);
                    q.push(v->getChildren()[cnt]);
                    cnt++;
                    delete tempC;
                }
            }
       }
    }
    return output;
}