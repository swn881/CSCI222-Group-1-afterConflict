#include <iostream>

#ifndef _USERCONTROL_
#define _USERCONTROL_

class UserControl
{
    private:

    public:
        ~UserControl();
        void registerUser(std::string, std::string, std::string, std::string, std::string, std::string, std::string);

        bool login(std::string, std::string, std::string&);
        bool checkUN(std::string);
        bool checkPW(std::string);

        void changePassword(std::string, std::string, std::string);

        void updateEmail(std::string, std::string);
        void updateUniversity(std::string, std::string);
        void updateExpertise(std::string, std::string);
        int count();
};

#endif // _USERCONTROL_
