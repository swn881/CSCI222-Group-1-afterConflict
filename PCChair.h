#include "ProgramCommittee.h"
#include "User.h"

#ifndef _PCCHAIR_
#define _PCCHAIR_

class PCChair : public ProgramCommittee
{
    private:

    public:
        void assignPC();
        void monitorPC();
        void functionalityManagement();

        int count();
        void writeFile(User*, int);
        void loadFile(User*, int);
        void obtainMoreDetails(User);

        void latestEvents();
        void approvePaper(std::string);
};

#endif // _PCCHAIR_
