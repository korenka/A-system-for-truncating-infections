#ifndef AGENT_H_
#define AGENT_H_
#include "../include/Session.h"

#include <vector>

class Agent{
public:
    Agent();
    virtual ~Agent();
    virtual void act(Session& session)=0;
    virtual  Agent* clone()=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session& session);
    virtual  Agent* clone() ;
};


class Virus: public Agent{
public:
    Virus(int _nodeInd);
    virtual void act(Session& session);
    virtual Agent* clone();

protected:
    const int nodeInd;
};

#endif