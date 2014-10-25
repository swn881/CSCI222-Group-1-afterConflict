#include <iostream>

#ifndef _PAPERREVIEW_
#define _PAPERREVIEW_

class PaperReview
{
    friend std::ostream& operator << (std::ostream&, PaperReview&);
    friend std::istream& operator >> (std::istream&, PaperReview&);
    private:
        std::string reviewedBy;

        std::string strengths;
        std::string weakness;
        std::string comments;
        int suitability;
        std::string pcRemarks;
        int overall;
        int reviewerConfidence;
        int relevance;
        int originality;
        int significance;
        int presentation;
        int technicalQuality;
        int evaluation;
    public:
};

#endif // _PAPERREVIEW_
