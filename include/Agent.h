#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "Graph.h"
#include "../include/Coalition.h"

class SelectionPolicy;
class Simulation;
class Party;

class Agent

{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);

    //Added
    Agent(int agentId, int partyId, Agent& other);
    int getCoalitionId();
    SelectionPolicy* getSelectionPolicy();
    void addPartiesVec(Simulation &sim);
    

    //Rule of five

    //destructor
    virtual ~Agent();
    //copy constructor
    Agent(const Agent& other);
    //copy assignment
    Agent& operator=(const Agent& other);
    //move constructor
    Agent(Agent&& other);
    //move assignment
    Agent& operator = (Agent&& other);
    
   

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    
    // Added    
    int mCoalitionId;
    vector<int> chosenParties;
    bool isSearching;
    
};
