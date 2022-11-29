//vertion 27, 27 november, 5PM

// #include "Simulation.h"
#include "../include/Simulation.h"
#include "../include/Party.h"
#include "../include/Graph.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) ,mCoalition{}
{
    // You can change the implementation of the constructor, but not the signature!

    //update coalition Vec
    for(auto& agent: mAgents)
    {
        Coalition curr = Coalition(agent.getId(),mGraph.getMandates(agent.getPartyId()));
        mCoalition.push_back(curr);
    }
}

void Simulation::step()
{
    // first we 'step' every party and than we 'step' every agent

    for(int i = 0; i<mGraph.getNumVertices();i++)
        mGraph.getPartyRef(i).step(*this);
    for(auto& agent: mAgents)
        agent.step(*this);
}

bool Simulation::shouldTerminate() const
{
    bool allJoined = true;
    for(Coalition cor : mCoalition)
        if (cor.getNumOfMandates()>60)
            return true;
    for(int i = 0; i<mGraph.getNumVertices(); i++)
        if(getParty(i).getState()!=State::Joined)
            return false;
    return allJoined;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    
    vector <vector<int>> coalitionVector;
    for (Coalition cor : mCoalition)
    {
        vector<int> currCoal;
        for(Agent agent: mAgents)
            if(agent.getCoalitionId() == cor.getId() )
                currCoal.push_back(agent.getPartyId());
        coalitionVector.push_back(currCoal);
    }
    return coalitionVector; 
}

Graph& Simulation::getGraphRef()
{
    return mGraph;
}

Party& Simulation::getParty(int partyId) 
{
    return mGraph.getPartyRef(partyId);
}

void Simulation::cloneAgent(int partyId,  Agent &age )
{
    mAgents.push_back(Agent(mAgents.size(),partyId,age));
}

Coalition &Simulation::getCoalition(int coalId) 
{
    return mCoalition[coalId];
}

