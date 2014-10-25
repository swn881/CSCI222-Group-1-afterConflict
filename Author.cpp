#include "Author.h"
#include "PaperManagement.h"
#include "UserBoundary.h"
#include <iostream>

using namespace std;

void Author::changeDetails(std::string currentlyLoggedIn)
{
    UserBoundary userBoundary;
    userBoundary.changeDetails(currentlyLoggedIn);
}

void Author::changePassword(string currentlyLoggedIn)
{
    UserBoundary userBoundary;
    userBoundary.changePassword(currentlyLoggedIn);
}

void Author::submitPaper()
{
    PaperManagement paperManagement;
    paperManagement.submitPaper();
}

void Author::modifyPaperSubmission(std::string currentlyLoggedIn)
{
    PaperManagement paperManagement;
    paperManagement.modifyPaperSubmission(currentlyLoggedIn);
}
