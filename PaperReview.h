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
        int suitability; //1 means yes,  2 means no
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
        std::string getReviewedBy() { return reviewedBy; }

        void setReviewedBy(std::string temp) { reviewedBy = temp; }

        void setStrengths(std::string temp) { strengths = temp;}
        void setWeakness(std::string temp) { weakness = temp; }
        void setComments(std::string temp) { comments = temp; }
        void setSuitability(int temp) { suitability = temp; }
        void setPcRemarks(std::string temp) { pcRemarks = temp; }
        void setOverall(int temp) { overall = temp; }
        void setReviewerConfidence(int temp) { reviewerConfidence = temp; }
        void setRelevance(int temp) { relevance = temp; }
        void setOriginality(int temp) { originality = temp; }
        void setSignificance(int temp) { significance = temp; }
        void setPresentation(int temp) { presentation = temp; }
        void setTechnicalQuality(int temp) { technicalQuality = temp; }
        void setEvaluation(int temp) { evaluation = temp; }
};

#endif // _PAPERREVIEW_
