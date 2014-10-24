#include <iostream>
#include <vector>

#ifndef _PREFERENCE_
#define _PREFERENCE_

class Preference
{
    friend std::ostream& operator<< (std::ostream&, Preference&);
    friend std::istream& operator>> (std::istream&, Preference&);
    private:
        std::string userName; //userIO, paper1Preferemnce,paper2Preference. . . . .
        std::vector<int> preference; //num of preferences depends on the number of paper submitted in the system
        /*
            preferences:
            1. yes
            2. no
            3. maybe
            4. conflict of interest
            //to check if user has specified preference or not by checking the missing id in the preference file
        */
    public:
        void addPreference(int);
        void setUsername(std::string);
        std::string getUsername();
        int countPaper();
        int getPreference(unsigned int);

};

#endif // _PREFERENCE_
