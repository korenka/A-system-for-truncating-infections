#include "../include/Session.h"
#include <iostream>
#include <ostream>
#include "../include/json.hpp"
#include <fstream>
#include "../include/Agent.h"
#include "../include/Tree.h"
#include "../include/Graph.h"
using json=nlohmann:: json;
using namespace std;

Session::Session(const string &path): g(),treeType(), agents(),currCycle(),infected_Nodes(){
    json readInput;
    std::ifstream readInput_file(path, ifstream::binary);
    readInput_file >> readInput;

    g = Graph(readInput["graph"]);

    string s = readInput["tree"];
    if(s=="M") {treeType=MaxRank;}
    else if(s=="C"){treeType=Cycle;}
    else{treeType=Root;}

    for (int i = 0; i < (int)readInput["agents"].size(); i++) {
        if(readInput["agents"][i][0]=="V") {agents.push_back(new Virus(readInput["agents"][i][1]));}
        else {agents.push_back(new ContactTracer());}
    }
    currCycle=0;
}

void Session::clear() {
//    g.~Graph();
    for ( int i = 0; i < (int)agents.size(); ++i) {
        delete(agents[i]);
    }
    agents.clear();
}

//==============Rule of 5=================
Session:: ~Session(){ //Destructor
    clear();
}

Session::Session(const Session &other)
        :g(other.g.getEdges()), treeType(other.treeType), agents(other.agents),
         currCycle(other.currCycle), infected_Nodes(other.infected_Nodes){ //Copy constructor
}



Session& Session::operator=(const Session &other){ //assignment operator
    if(this == &other){return *this;}
    clear();
    g = other.g;
    treeType=other.treeType;
    agents = other.agents;
    currCycle = other.currCycle;
    infected_Nodes = other.infected_Nodes;
    return *this;
}

Session::Session(Session &&other): //move CSTR
        g(other.g.getEdges()), treeType(other.treeType), agents(other.agents),
        currCycle(other.currCycle), infected_Nodes(other.infected_Nodes) {
    other.clear();
}

const Session& Session::operator=(Session&& other){
    if(this != &other){
        clear();
        g = other.g;
        treeType=other.treeType;
        agents = other.agents;
        currCycle = other.currCycle;
        infected_Nodes = other.infected_Nodes;
        other.clear();
    }
    return *this;
}

//=============End rule of 5===============


const Graph Session::getGraph() const {
    return g;
}

void Session::simulate() {
    while(!terminate()){
        int stopAt=agents.size();
        for (int i = 0; i < stopAt; ++i) {
            agents[i]->act(*this);
        }
        currCycle++;
    }
    writeOutput();
}

void Session::setGraph(const Graph& graph){g=graph;}

void Session::enqueueInfected(int node){ //Push infected node to queue
    infected_Nodes.push(node);
    g.infectNode(node);
}
void Session::infectNode(int node) {
    g.infectNode(node);
}

void Session::makeACarrier(int nodeInd) {g.makeACarrier(nodeInd);}

int Session::dequeueInfected() { //Return infected node
    if(infected_Nodes.empty())
        return -1;
    int returned_Node = infected_Nodes.front();
    infected_Nodes.pop();
    return (returned_Node);
}

TreeType Session::getTreeType() const {return treeType;}
void Session::addAgent(const Agent& agent){
    addAgent(agent);
}
void Session::addAgent( Agent& agent){
    Agent* copy=agent.clone();
    agents.push_back(copy);
}
int Session::getCurrCycle()const{
    return currCycle;
}

vector<int> Session::getInfectedNodes() {
    vector<int> infected;
    int v=g.getEdges().size();
    for (int i = 0; i < v ; ++i) {
            if(g.isInfected(i)==2)
                infected.push_back(i);
    }
    return infected;
}

bool Session::terminate() {
    if(currCycle==0)
        return false;
    int n=g.getEdges().size();
    for (int i = 0; i < n; ++i) {
        vector<int> neighbors=g.getNeighbors(i);
        if(g.isInfected(i)==1)
            return false;
         for(int v:neighbors)
             if(g.isInfected(i)!=g.isInfected(v))
                 return false;
    }
    return true;
}

void Session::writeOutput() {
    ofstream file("output.json");
    json writeTo;
    writeTo["Graph:"]=g.getEdges();
    writeTo["Infected nodes:"]=getInfectedNodes();
    file << writeTo<<endl;
}

void Session::removeEdges(int i) {g.removeAgent(i);}
void Session::BFS(int node){
     g.BFS(*this,node);
}



