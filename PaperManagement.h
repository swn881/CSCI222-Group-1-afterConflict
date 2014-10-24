#include <iostream>
#include "ResearchPaper.h"

#ifndef _PAPERMANAGEMENT_
#define _PAPERMANAGEMENT_

class PaperManagement
{
    private:

    public:
        void submitPaper();
        void modifyPaperSubmission(std::string); //pass in the user ID
        void reviewPaper(std::string);

        void writeFile(const ResearchPaper&); //write current paper record into file
        void transferFile(ResearchPaper); //get the file from the user and paste it in our directory
        int generateID(); //function to generate ID
        int countPaper(); //count number of lines in file
        int countUser();
};

#endif // _PAPERMANAGEMENT_
