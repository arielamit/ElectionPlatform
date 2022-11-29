#pragma once
#include <vector>


using std::vector;
class Agent;
class Coalition;
class Simulation;
class JoinPolicy

{
    public:
    JoinPolicy();
    virtual int join( vector<int> offers, Simulation & sim ) = 0;
    virtual ~JoinPolicy() = default;
    virtual JoinPolicy* clone()  = 0;

};

class MandatesJoinPolicy : public JoinPolicy 
{
    public:
    MandatesJoinPolicy();
    int join( vector <int> offers, Simulation & sim ) override;
    MandatesJoinPolicy* clone()  override;
    virtual ~MandatesJoinPolicy()=default;

};

class LastOfferJoinPolicy : public JoinPolicy 
{
    public:
    LastOfferJoinPolicy();
    virtual int join( vector <int> offers, Simulation & sim ) override;
    LastOfferJoinPolicy* clone() override;
    virtual ~LastOfferJoinPolicy()=default;
};