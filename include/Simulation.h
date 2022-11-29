#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"
#include "Parser.h"
#include "Coalition.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;

    //Added
    
    Coalition &getCoalition(int cId);
    void cloneAgent(int partyId, Agent &Agent);
    Party& getParty(int partyId);
    Graph &getGraphRef();

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> mCoalition;

};
