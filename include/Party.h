#pragma once
#include <string>
#include <vector>

using std::string;
using namespace std;

class JoinPolicy;
class Simulation;
class Agent;
class Coalition;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    //constructor
    Party(int id, string name, int mandates, JoinPolicy *);

    Party();

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;

    //Added

    string &getName();
    int getId();
    void AddOfferFromCoal(int caolition);

        
        // Rule of five
    
    //destructor
    virtual ~Party();
    //copy constructor
    Party(const Party& other);
    //copy assignment
    Party& operator=(const Party& other);
    //move constructor
    Party(Party&& other);
    //move assignment
    Party& operator = (Party&& other);


private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;

    //Added
    int mTimer;
    vector <int> mOfferVec;  
};
