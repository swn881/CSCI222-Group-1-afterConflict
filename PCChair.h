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

        int count();
        void writeFile(User*, int);
        void loadFile(User*, int);
        void obtainMoreDetails(User);
};

#endif // _PCCHAIR_
