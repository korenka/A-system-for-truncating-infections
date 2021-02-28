#include "../include/Agent.h"
#include <iostream>
#include "../include/Session.h"
#include "../include/Tree.h"
using namespace std;

Agent::Agent(){} // Agent constructor
Agent::~Agent() noexcept {}
ContactTracer::ContactTracer(){} //CT constructor
void ContactTracer::act(Session& session){
    int infected_Node = session.dequeueInfected(); //gets infected node index
    if(infected_Node!=-1) {
        Graph temp = session.getGraph();
        Tree *tree =temp.BFS(session, infected_Node);
        int traced=tree->traceTree();
        session.removeEdges(traced);
        delete tree;
    }
}
Agent* ContactTracer::clone() {
    return new ContactTracer(*this);
}

Agent* Virus::clone()  {
    return new Virus(*this);
}
Virus::Virus(int nodeInd): nodeInd(nodeInd){} //Virus constructor
void Virus::act(Session& session){ // virus act
    Graph g=session.getGraph();
    if(g.isInfected(nodeInd)!=2){
        session.enqueueInfected(nodeInd);
    }
    vector<int> neigh=g.getNeighbors(nodeInd);
    for(int i=0;i<(int)neigh.size();i++) {
        if (g.isInfected(neigh[i])==0) {
            Virus *newV = new Virus(neigh[i]);
            session.addAgent(*newV);
            session.makeACarrier(neigh[i]);
            delete newV;
            break;
        }
    }
}


