#include "../include/Coalition.h"
#include "../include/SelectionPolicy.h"
#include "../include/Agent.h"
#include "../include/Party.h"

//constructor
Coalition:: Coalition(int id, int mandates): mId(id), mMandates(mandates), offersVec{}
{
   
}

// empty constuctor for Debug perpuses 
// Coalition:: Coalition() : mId{}, mMandates{}, offersVec{}    //TODO: check this line
// {
    
// }

int Coalition::getId()
{
    return mId;
}

int Coalition::getNumOfMandates() 
{
    return mMandates;
}

void Coalition::addMandates(int mandates)
{
    mMandates = mMandates + mandates;
}

void Coalition::addOffereVec(int partyId)
{
    offersVec.push_back(partyId);
}

//Checikng if the coalition contains a party
bool Coalition::isContainParty(int partyId)
{
    bool output = false;
    
    for (int id : offersVec)
    {
        if( id == partyId)
            return true;
    }

    return output;
}