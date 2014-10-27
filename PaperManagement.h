#include <iostream>
#include "ResearchPaper.h"
#include "PaperReview.h"
#include "PaperAssignment.h"

#ifndef _PAPERMANAGEMENT_
#define _PAPERMANAGEMENT_

class PaperManagement
{
    private:

    public:
        void submitPaper();
        void modifyPaperSubmission(std::string); //pass in the user ID
        void reviewPaper(std::string); //mostly checking and review actually done on make review
        void modifyReview(std::string); //modify paper review

        void writeFile(const ResearchPaper&); //write current paper record into file
        void writeAll(ResearchPaper[], int);
        void writeAssignment(PaperAssignment*, int);
        void transferFile(ResearchPaper); //get the file from the user and paste it in our directory
        void reverseTransfer(ResearchPaper);
        int generateID(); //function to generate ID
        int countPaper(); //count number of lines in file
        int countUser();
        int countPreference();

        PaperReview* makeReview(std::string); //the function that populates the review class with the correct review data

        void reviewDiscussion(std::string);
        int countDiscussion();
        void submitAuthorResponse();
        void approvePaper(std::string);

        void manuallyAssignPaper(std::string);
        void notifications(std::string);

        void monitorPC();

};

#endif // _PAPERMANAGEMENT_
