#ifndef TREE_H_
#define TREE_H_

#include <vector>
using namespace std;


class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree();
    virtual ~Tree();
    Tree(const Tree &other);
    Tree(Tree&& other);
    const Tree& operator=(const Tree& other);
    const Tree& operator=(Tree&& other);
    void setDepth(int);
    int getDepth();
    void setVisited(bool);
    bool isVisited();

    virtual Tree* clone() const=0;
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    vector<Tree*> getChildren();
    int getNodeInd();

protected:
    int nodeInd;
    std::vector<Tree*> children;

private:
    int depth;
    bool visited;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int _currCycle);
    CycleTree(const CycleTree &other);
    virtual int traceTree();
    virtual Tree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    MaxRankTree(const MaxRankTree &other);
    virtual int traceTree();
    virtual Tree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    RootTree(const RootTree &other);
    virtual int traceTree();
    virtual Tree* clone() const;

};

#endif
