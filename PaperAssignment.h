#include <iostream>
#include <vector>
#include "PaperReview.h"

#ifndef _PAPERASSIGNMENT_
#define _PAPERASSIGNMENT_

class PaperAssignment
{
    friend std::ostream& operator << (std::ostream&, PaperAssignment&);
    friend std::istream& operator >> (std::istream&, PaperAssignment&);
    private:
        int paperID;
        int numAssignedForReview;
        std::vector<std::string> userList; //list of usernames of those assigned this paper
        int numUserReviewed; //num of user who has reviewed the paper
        std::vector<PaperReview *>userReview;
    public:
        PaperAssignment() { paperID = 0; numAssignedForReview = 0; numUserReviewed = 0; }
        void setPaperID (int temp) { paperID = temp; }
        void setNumAssignedForReview (int temp) { numAssignedForReview = temp; }
        void addUser(std::string temp ) { userList.push_back(temp); }

        void addNumUserReviewed() { numUserReviewed ++; }
        void addUserReview(PaperReview* temp) { userReview.push_back(temp); }

        int getNumAssignedForReview() { return numAssignedForReview; }
        std::vector<std::string> getUserList() { return userList; }
        int getNumUserReviewed() { return numUserReviewed; }
        std::vector<PaperReview*> getUserReview() { return userReview; }

        int getPaperID() { return paperID; }
};

#endif // _PAPERASSIGNMENT_
