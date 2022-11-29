// #include "SelectionPolicy.h"
#include "../include/SelectionPolicy.h"
#include "../include/Agent.h"
#include "../include/Simulation.h"
#include "../include/Party.h"

SelectionPolicy:: SelectionPolicy(){}

MandatesSelectionPolicy::MandatesSelectionPolicy() {}

int MandatesSelectionPolicy ::select(int partyId, vector<int>chosenParties, Graph &gr)
{
    int maxMan = -1;
    int partyIDwithMaxMandates = -1;
    for (int i : chosenParties)
    {
        if(gr.getParty(i).getMandates()>maxMan)
        {
            maxMan = gr.getParty(i).getMandates();
            partyIDwithMaxMandates = i;
        }
    }
    return partyIDwithMaxMandates;
}

MandatesSelectionPolicy* MandatesSelectionPolicy:: clone() 
{
    return new MandatesSelectionPolicy(*this);
}

EdgeWeightSelectionPolicy::EdgeWeightSelectionPolicy() {}

int EdgeWeightSelectionPolicy::select(int partyId, vector<int>chosenParties, Graph &gr)
{
    int maxWeight = -1;
    int partyIDwithMaxWeight = -1;

    for (int i : chosenParties)
    {
        int currWeight = gr.getEdgeWeight(partyId,i);
        
        if(currWeight>maxWeight)
        {
            maxWeight = currWeight;
            partyIDwithMaxWeight = i;
        }
    }
    return partyIDwithMaxWeight;
}

EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy:: clone() 
{
    return new EdgeWeightSelectionPolicy(*this);
}

;