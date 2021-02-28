#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"

using namespace std;

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    virtual ~Session();
    Session(const Session &other);
    Session& operator=(const Session &other);
    Session(Session &&other);
    const Session& operator=(Session&& other);
    
    void simulate();
    void addAgent(const Agent& agent);
    void addAgent(Agent& agent);
    void setGraph(const Graph& graph);
    const Graph getGraph()const;
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCurrCycle()const;
    vector<int> getInfectedNodes();
    bool terminate();
    void writeOutput();
    void removeEdges(int i);
    void BFS(int);
    void infectNode(int);
    void makeACarrier(int nodeInd);

private:
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
    int currCycle;
    queue<int> infected_Nodes; ///Diff

    void clear(); ///Diff - clear function
};



#endif
