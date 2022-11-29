#include "../include/JoinPolicy.h"
#include "../include/Agent.h"
#include "../include/Simulation.h"
#include "../include/Coalition.h"

JoinPolicy::JoinPolicy(){}

MandatesJoinPolicy::MandatesJoinPolicy(){}

int MandatesJoinPolicy:: join( vector <int> offers, Simulation & sim )
{
    int output = -1;
    int max = -1;
    for(int offerCoalId : offers)
    {
        int currMandates=sim.getCoalition(offerCoalId).getNumOfMandates();
        if(currMandates > max)
        {
            max = currMandates;
            output = offerCoalId;
        }
    }
    return output;
}

MandatesJoinPolicy* MandatesJoinPolicy:: clone() 
{
    return new MandatesJoinPolicy();
}

LastOfferJoinPolicy::LastOfferJoinPolicy(){}

int LastOfferJoinPolicy:: join(vector <int> offers, Simulation & sim )
{
    return offers.back();
}

LastOfferJoinPolicy* LastOfferJoinPolicy:: clone() 
{
    return new LastOfferJoinPolicy();
}
;

