#pragma once
#include <vector>
#include "../include/Graph.h"


using std::vector;

class Simulation;
class Party;
class Graph;

class SelectionPolicy 
{ 
    public:
    SelectionPolicy();
    virtual int select(int partyId, vector<int>chosenParties, Graph &gr) = 0;  
    virtual SelectionPolicy* clone()  = 0;    
    virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
    public:
    MandatesSelectionPolicy();
    virtual int select(int partyId, vector<int>chosenParties, Graph &gr) override;
    MandatesSelectionPolicy* clone()  override;
    virtual ~MandatesSelectionPolicy() = default;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{ 
    public:
    EdgeWeightSelectionPolicy();
    virtual int select(int partyId, vector<int>chosenParties, Graph &gr) override;
    EdgeWeightSelectionPolicy* clone()  override;  
    virtual ~EdgeWeightSelectionPolicy() = default;
};