#include <iostream>
#include "UserControl.h"

#ifndef _USERBOUNDARY_
#define _USERBOUNDARY_

class UserBoundary
{
    private:
        UserControl userControl;
    public:
        ~UserBoundary();
        void registerUser();
        void login(std::string&, std::string&);
        void changePassword(std::string);
        void changeDetails(std::string);
};

#endif // _USERBOUNDARY_
