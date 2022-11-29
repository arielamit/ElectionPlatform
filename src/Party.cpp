#include "Party.h"
#include "vector"
#include "../include/JoinPolicy.h"
#include "../include/Agent.h"
#include "../include/Simulation.h"

using std::vector;

//constructor
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) , mTimer(0) , mOfferVec{}
{
    // You can change the implementation of the constructor, but not the signature!
}

// empty constuctor for Debug perpuses 
// Party::Party() : mId{}, mName{}, mMandates{}, mJoinPolicy{}, mState(Waiting), mTimer(0), mOfferVec{}
// {

// }

//destructor
Party::~Party()
{
    if(mJoinPolicy)
    {
        delete mJoinPolicy;
        mJoinPolicy = nullptr;
    }
}

//copy constructor
Party::Party(const Party& other): mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(nullptr)
, mState(other.mState) , mTimer(other.mTimer),mOfferVec(other.mOfferVec)
{
        mJoinPolicy =  other.mJoinPolicy->clone();
}

//copy assignment
Party& Party:: operator=(const Party & other)
{
    if(mJoinPolicy)
        delete mJoinPolicy;
    
    mId= other.mId;
    mName=other.mName;
    mMandates=other.mMandates;
    mState = other.mState;
    *mJoinPolicy=(*(other.mJoinPolicy));
    mTimer = other.mTimer;
    mOfferVec = other.mOfferVec;

    return *this;
}

//move constructor
Party::Party(Party&& other):  mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState) , mTimer(other.mTimer),mOfferVec(other.mOfferVec)
{
    other.mJoinPolicy = nullptr;
}

//move assignment
Party& Party:: operator = (Party&& other)
{
    if (mJoinPolicy)
        delete mJoinPolicy;
     mId= other.mId;
     mName=other.mName;
     mMandates=other.mMandates;
     mJoinPolicy=other.mJoinPolicy;
     mTimer=other.mTimer;
     other.mJoinPolicy=nullptr;
     mState=other.mState;
     mOfferVec = other.mOfferVec;

    return *this;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    if(getState() == CollectingOffers) //check if the party have to join some coalition
    {
        if(mTimer<3) 
            mTimer = mTimer +1;
       
        if(mTimer == 3)
        {
            int chosenCoalition = mJoinPolicy->join(mOfferVec,s); //choose coalition by join policy
            s.getCoalition(chosenCoalition).addMandates(mMandates); //add the party to the choosen coalition - add this party's number of mandates to the chosen coalition
            //clone agent
            Agent age = s.getAgents()[chosenCoalition];
            s.cloneAgent(mId,age);
            setState(Joined);
        }   
    }
}

int Party::getId() 
{
    return mId;
}

void Party::AddOfferFromCoal(int coalition)
{
    mOfferVec.push_back(coalition);
}

