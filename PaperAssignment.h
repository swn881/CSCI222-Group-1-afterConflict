#include <iostream>
#include <vector>

#ifndef _PAPERASSIGNMENT_
#define _PAPERASSIGNMENT_

class PaperAssignment
{
    friend std::ostream& operator << (std::ostream&, PaperAssignment&);
    friend std::istream& operator >> (std::istream&, PaperAssignment&);
    private:
        std::string userName;
        int numPaperAssigned; //num of paper assigned to this user
        std::vector<int> paperAssigned; //the id of each paper assigned
    public:

};

#endif // _PAPERASSIGNMENT_
