#include <iostream>
#include <vector>

#ifndef _AUTHOR_
#define _AUTHOR_

class Author
{
    private:

    public:
        void changeDetails(std::string);
        void changePassword(std::string);
        void submitPaper();
        void modifyPaperSubmission(std::string);
        void notifications(std::string);

        void participateConference(std::string);

        int countConference();
};

#endif
