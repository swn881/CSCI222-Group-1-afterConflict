#include <iostream>

#ifndef _FUNCTIONALITIES_
#define _FUNCTIONALITIES_

class Functionalities
{
    friend std::ostream& operator<< (std::ostream&, Functionalities&);
    friend std::istream& operator>> (std::istream&, Functionalities&);
    private:
        //variable names a bit off, could had been named better
        int reviewDiscussion; //-1 means not allowed for review discussion, 1 means allowed
        int reviewSubmission; //-1 means not allowed for review submission, 1 means allowed
        int authorResponse; //-1 means not allowed for author response, 1 means allowed
        int paperSubmission; //-1 means not allowed for paperSubmission, 1 means allowed
        int paperReviewerReceive; //default at 3
        int reviewerPaperReceive; //default at 5
    public:
        void setReviewDiscussion();
        void setReviewSubmission();
        void setAuthorResponse();
        void setPaperSubmission();

        void setPaperReviewerReceive(int);
        void setReviewerPaperReceive(int);

        //get each status for reviewing and such
        int getReviewDiscussion();
        int getReviewSubmission();
        int getAuthorResponse();
        int getPaperSubmission();
        int getPaperReviewerReceive();
        int getReviewerPaperReceive();
};

#endif // _FUNCTIONALITIES_
