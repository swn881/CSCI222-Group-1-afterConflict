#include <iostream>
#include "Functionalities.h"

#ifndef _FUNCMANAGEMENT
#define _FUNCMANAGEMENT

class FuncManagement
{
    //read in the current "status" of tasks
    private:

    public:
        void generateConferenceProceeding(); //get the list of papers which has been approved
        void autoSpecifyPreference(); //Specify preference for user who has been asigned papers and have yet to assign their own preference
        void setReviewerPaperReceive(); //set the number of reviewers paper receive
        void setPaperReviewerReceive(); //set the number of papers each reviewers receive
        void enableRevSubmission(); //enable review submission by pc
        void enablePapSubmission(); //enable paper submission by authors
        void enableAutResponse(); //emable author response towards their paper which has been reviewed
        void enableRevDiscussion(); //enable review discussion among reviewers

        void autoAssignPapersToReviewers();
        void checkNumPaperAssigned(std::string);

        int countPaper();
        int countUser();
        int countPreference();

        void loadFunctionalities(Functionalities&); //read from functionalities
        void writeFunctionalities(Functionalities&); //write to functionalities file the new changes

};

#endif // _FUNCMANAGEMENT
