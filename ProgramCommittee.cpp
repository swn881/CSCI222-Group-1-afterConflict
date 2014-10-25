#include "ProgramCommittee.h"
#include "PreferenceManagement.h"
#include <iostream>

using namespace std;

//user -> author -> program committee
void ProgramCommittee::specifyPreference(std::string currentlyLoggedIn)
{
    PrefManagement prefManagement;
    prefManagement.specifyPreference(currentlyLoggedIn);
}

