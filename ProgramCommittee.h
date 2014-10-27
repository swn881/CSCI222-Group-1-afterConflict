#include "Author.h"
#include <iostream>

#ifndef _PROGRAMCOMMITTEE_
#define _PROGRAMCOMMITTEE_

class ProgramCommittee : public Author
{
    private:

    public:
        void specifyPreference(std::string);
        void reviewPaper(std::string);
        void modifyReview(std::string);
        void reviewDiscussion(std::string);
};

#endif // _PROGRAMCOMMITTEE_
