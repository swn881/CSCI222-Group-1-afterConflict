#include <iostream>
#include <vector>

#ifndef _CONFERENCE_
#define _CONFERENCE_

class Conference
{
    friend std::ostream& operator<< (std::ostream&, Conference&);
    friend std::istream& operator>> (std::istream&, Conference&);
    private:
        std::string conferenceName;
        std::string location;
        int numUser;
        std::vector<std::string>userList;
    public:
        Conference() { numUser = 0; }
        void addNumUser() { numUser++; }
        void addUser(std::string temp) { userList.push_back(temp); }
        void setLocation(std::string temp) { location = temp; }
        void setConferenceName(std::string temp) { conferenceName = temp; }

        std::string getConferenceName() { return conferenceName; }
};

#endif // _CONFERENCE_
