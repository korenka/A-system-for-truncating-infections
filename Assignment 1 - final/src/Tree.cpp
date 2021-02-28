#include "../include/Tree.h"
#include <iostream>
#include <vector>
#include "../include/Session.h"
#include "../include/Graph.h"
using namespace  std;

Tree::Tree(int rootLabel):nodeInd(rootLabel),children(),depth(0),visited(false){
    depth=0;
}
//defualt
Tree::Tree():nodeInd(0),children(),depth(0),visited(false){};

Tree::~Tree(){
    for ( int i = 0; i < (int)children.size(); ++i) {
        delete (children[i]);
    }
    children.clear();
    if(nodeInd)
         nodeInd=0;
}

//copy constractor
Tree::Tree(const Tree &other):nodeInd(other.nodeInd),children(),depth(other.depth),visited(other.visited){
    for(Tree* kid:other.children)
        children.push_back(kid);
    visited = other.visited;
}

//move constractor
Tree::Tree(Tree&& other):nodeInd(other.nodeInd),children(other.children),depth(other.depth),visited(other.visited){
    other.children.~vector();
    other.nodeInd=0;
}

//copy assignment
const Tree & Tree:: operator=(const Tree & other){
     if(this!=&other){
         for ( int i = 0; i < (int)children.size(); ++i) {
             delete(children[i]);
         }
         children.clear();

         nodeInd=other.nodeInd;
         visited=other.visited;
         for( int i=0;i<(int)other.children.size();i++)
             children.push_back(other.children[i]);
         depth=other.depth;
     }
    return *this;
}

 //Move assignment
 const Tree& Tree:: operator=(Tree&& other){
     if(this!=&other){
        children=other.children;
        nodeInd=other.nodeInd;
        visited=other.visited;
        other.children.~vector();
        other.nodeInd=0;
     }
     return *this;
 }

void Tree::setDepth(int _depth) {depth=_depth;}
int Tree::getDepth() {return depth;}
void Tree::setVisited(bool v) {visited=v;}
bool Tree::isVisited() {return visited;}

void Tree::addChild(const Tree &child) {
    int root=child.nodeInd;
    int indexToInsert=-1;
    Tree* toAdd=child.clone();
    if(children.empty())
    {
        children.push_back(toAdd);
    }
    else {
        for ( int i = 0; i < (int)children.size(); ++i) {
            if (root < children[i]->nodeInd) {
                indexToInsert = i;
                break;
            }
        }
        if (indexToInsert != -1) {
            for (unsigned int i = indexToInsert; i < children.size() - 1; ++i) {
                children[i + 1] = children[i];
            }
            children[indexToInsert]=toAdd;

        }
        else
            children.push_back(toAdd);
    }
}

vector<Tree*> Tree::getChildren() {return children;}
int Tree::getNodeInd() {return nodeInd;}

Tree* Tree::createTree(const Session &session, int rootLabel) {
    Graph g = session.getGraph();
    if(session.getTreeType()==MaxRank)
        return new MaxRankTree(rootLabel);
    else if (session.getTreeType()==Root)
        return new RootTree(rootLabel);
    else
        return new CycleTree(rootLabel,session.getCurrCycle());
}

CycleTree::CycleTree(int rootLabel, int _currCycle):Tree(rootLabel),currCycle(_currCycle){
 }
CycleTree::CycleTree(const CycleTree &other): Tree(other),currCycle(other.currCycle){}
int CycleTree::traceTree() {
    int steps=currCycle;
    if(steps==0||children.empty())
        return nodeInd;
    else{
        Tree* curr=children[0];
        steps--;
        while(steps>0){
            if(curr->getChildren().size()==0)
                return curr->getNodeInd();
            curr=curr->getChildren()[0];
            steps--;
        }
        return curr->getNodeInd();
    }
}
Tree* CycleTree::clone() const{
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) :Tree(rootLabel){

}
MaxRankTree::MaxRankTree(const MaxRankTree &other) :Tree(other){}
int MaxRankTree::traceTree() {
    int maxRank = children.size();
    int mDepth=getDepth();
    int mInd=nodeInd;
    queue<Tree *> q;
    q.push(this);
    this->setVisited(true);
    while (!q.empty()) {
        Tree *v = q.front();
        q.pop();
        for (Tree *u:v->getChildren()) {
            if (!u->isVisited()){
                u->setVisited(true);
                int rank=u->getChildren().size();
                if(rank>maxRank) {
                    maxRank = rank;
                    mDepth=u->getDepth();
                    mInd=u->getNodeInd();
                }
                else if(rank==maxRank){
                    if(mDepth<u->getDepth())
                        return mInd;
                    else if(mDepth>u->getDepth())
                        return u->getDepth();
                    else
                        return min(mInd,u->getNodeInd());
                }
                q.push(u);
            }
        }
    }
    return mInd;
}


Tree* MaxRankTree::clone() const{
    Tree* toReturn = new MaxRankTree(*this);
    return toReturn;
}

RootTree::RootTree(int rootLabel) :Tree(rootLabel){}
RootTree::RootTree(const RootTree &other) :Tree(other){}
int RootTree::traceTree() {return nodeInd;}
Tree* RootTree::clone()const{
    return new RootTree(*this);
}