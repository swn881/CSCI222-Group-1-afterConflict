#include "PCChair.h"
#include <iostream>

#ifndef _ADMIN_
#define _ADMIN_

class Admin : public PCChair
{
    private:

    public:
        void assignPCChair();
        void generateConference();
};

#endif // _ADMIN_
