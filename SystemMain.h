#include <iostream>

#ifndef _SYSTEMMAIN_
#define _SYSTEMMAIN_

class SystemMain
{
    private:
        std::string currentLoggedInUser;
        std::string userType;
    public:
        void mainPage();
        void homePage(); //PAGE TO GO AFTER LOGGED IN
        void adminPage();
        void authorPage();
        void PCpage();
        void PCChairPage();

};

#endif // _SYSTEMMAIN_
