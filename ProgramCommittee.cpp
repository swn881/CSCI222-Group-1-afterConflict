#include "ProgramCommittee.h"
#include "PreferenceManagement.h"
#include "PaperManagement.h"
#include <iostream>

using namespace std;

//user -> author -> program committee
void ProgramCommittee::specifyPreference(std::string currentlyLoggedIn)
{
    PrefManagement prefManagement;
    prefManagement.specifyPreference(currentlyLoggedIn);
}

void ProgramCommittee::reviewPaper(std::string currentlyLoggedIn)
{
    PaperManagement paperManagement;
    paperManagement.reviewPaper(currentlyLoggedIn);
}

void ProgramCommittee::modifyReview(std::string currentlyLoggedIn)
{
    PaperManagement paperManagement;
    paperManagement.modifyReview(currentlyLoggedIn);
}
