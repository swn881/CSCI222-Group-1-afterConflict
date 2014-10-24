#include <iostream>
#include "Preference.h"

#ifndef _PREFERENCEMANAGEMENT_
#define _PREFERENCEMANAGEMENT_

class PrefManagement
{
    private:

    public:
        void specifyMaybe(std::string); //this function used by func management to specify "maybe" to the user. (only used when running automation of assignment process)
        void specifyPreference(std::string); //specify preference for currently logged in user
        bool checkUser(std::string); //function used to check if user has already specified a preference before

        int countPreference();
        int countUser();
        int countPaper();

        void writeApp(Preference); //write into preference file at the end
        void writeAll(Preference); //write all again cause the user who has already specified preference, specified preference again
};

#endif // _PREFERENCEMANAGEMENT_
