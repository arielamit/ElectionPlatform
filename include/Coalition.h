#pragma once
#include <vector>
#include "../include/Agent.h"


class SelectionPolicy;


using std::vector;


// Added file that represents Coalition

class Coalition
{
public:
    Coalition(int coalId, int numOfMandates);
    //Add empty constructor
    Coalition ();

    int getId();
    int getNumOfMandates();
    void addMandates(int mandates);
    void addOffereVec(int partyId);
    bool isContainParty(int partyId);
    

private:
    int mId;
    int mMandates; 
    vector<int> offersVec;
};