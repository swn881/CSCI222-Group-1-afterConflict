#include <iostream>
#include <vector>

#ifndef _PAPERDISCUSSION_
#define _PAPERDISCUSSION_

class PaperDiscussion
{
    friend std::ostream& operator<< (std::ostream&, PaperDiscussion&);
    friend std::istream& operator>> (std::istream&, PaperDiscussion&);
    private:
        int paperID;
        int numReviewerResponse; //keep track of how many reviewer response made
        std::vector<std::string> reviewerDiscussion;
        int numUserResponse; //should be based on the number of reviewers assignd to the paper
        std::vector<std::string> userResponse;
    public:
        PaperDiscussion() { paperID = 0; numReviewerResponse = 0; numUserResponse = 0; }
        void setPaperID(int temp) { paperID = temp; }
        void addNumReviewerResponse() { numReviewerResponse++; }
        void addReviewerDiscussion (std::string temp) { reviewerDiscussion.push_back(temp); }
        void addNumUserResponse() { numUserResponse++;}
        void addUserResponse(std::string temp) { userResponse.push_back(temp); }

        int getPaperID() { return paperID; }
        int getNumReviewerResponse() { return numReviewerResponse; }
        std::vector<std::string> returnReviewerDiscussions() { return reviewerDiscussion; }
        std::vector<std::string> returnUserResponse() { return userResponse; }

};

#endif // _PAPERDISCUSSION_
