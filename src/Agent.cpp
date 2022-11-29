#include "Agent.h"
#include "vector"
#include "../include/Agent.h"
#include "../include/Party.h"
#include "../include/Graph.h"
#include "../include/SelectionPolicy.h"
#include "../include/Simulation.h"

using std::vector;

//constructor
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy),mCoalitionId(agentId),chosenParties{},isSearching(true)
{
    // You can change the implementation of the constructor, but not the signature!
}

//destructor
Agent::~Agent()
{
    if(mSelectionPolicy)          
        delete mSelectionPolicy;
    mSelectionPolicy = nullptr;
}

//copy constructor
Agent::Agent(const Agent& other):  mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy((other.mSelectionPolicy)->clone()), mCoalitionId(other.mCoalitionId), chosenParties(other.chosenParties), isSearching(other.isSearching)
{

}

//copy assignment
Agent & Agent:: operator=(const Agent& other)
{
    if(this!= &other)
    {
        if (mSelectionPolicy)
            delete mSelectionPolicy;
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        *mSelectionPolicy = (*(other.mSelectionPolicy));
        mCoalitionId = other.mCoalitionId;
        chosenParties = other.chosenParties;
        isSearching = other.isSearching;
    }
    return *this;
}

//move constructor
Agent::Agent(Agent&& other):  mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy),mCoalitionId(other.mCoalitionId),chosenParties(other.chosenParties), isSearching(other.isSearching)
{
    other.mSelectionPolicy = nullptr;
}

//move assignment
Agent& Agent:: operator = (Agent&& other)
{
    if (mSelectionPolicy)
        delete mSelectionPolicy;
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mSelectionPolicy = other.mSelectionPolicy;
    mCoalitionId = other.mCoalitionId;
    chosenParties = other.chosenParties;
    isSearching = other.isSearching;
    other.mSelectionPolicy = nullptr;
    return *this;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    if(isSearching) //if the agent still active
    {
        if(chosenParties.size() == 0)    // first iteration of agent's offers
        {
            for(int i = 0 ;i< sim.getGraphRef().getNumVertices(); i++)
                if(sim.getGraphRef().getEdgeWeight(mPartyId,i)>0) //neigbors
                    chosenParties.push_back(i);
        }
        if(isSearching)
            addPartiesVec(sim); // update optinal parties - after clone
        if(isSearching)
        {
            int chosenParty =  mSelectionPolicy->select(mPartyId, chosenParties, sim.getGraphRef()); //get selection policy
            Coalition &currCoal = sim.getCoalition(mCoalitionId); 
            currCoal.addOffereVec(chosenParty); //add to coalition the party id we offer to join by selection policy
            sim.getGraphRef().getPartyRef(chosenParty).setState(CollectingOffers);
            sim.getGraphRef().getPartyRef(chosenParty).AddOfferFromCoal(mCoalitionId); //add the offer to the party
        }
    }
}

//clone curr agent
Agent::Agent(int agentId, int partyId, Agent &other) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy((other.mSelectionPolicy)->clone()), mCoalitionId(other.mCoalitionId), chosenParties{},isSearching(true)
{
   
}

SelectionPolicy* Agent::getSelectionPolicy()
{
    return mSelectionPolicy;
}

void Agent::addPartiesVec(Simulation &sim)
{
    int i = 0;
    Coalition &currCoalition = sim.getCoalition(mCoalitionId);

    for( int partyId :chosenParties )
    {
        if ((sim.getGraphRef().getParty(partyId).getState() == Joined) ||(currCoalition.isContainParty(partyId)))// the party already joined a coalition or the party already got offered
            chosenParties.erase(chosenParties.begin() + i);
        else
            i = i +1;
        if(chosenParties.size() == 0)
            isSearching = false;
    }
}

int Agent::getCoalitionId() 
{
    return mCoalitionId;
}
