#include <iostream>
#include <vector>

#ifndef _RESEARCHPAPER_
#define _RESEARCHPAPER_

class ResearchPaper
{
    friend std::ostream& operator<< (std::ostream&, const ResearchPaper&);
    friend std::istream& operator>> (std::istream&, ResearchPaper&);
    private:
        int paperID;
        int numContributors;
        std::vector<std::string> contributedFirst;
        std::vector<std::string> contributedLast;
        std::vector<std::string> contributedUni;
        std::vector<std::string> contributedEmail;

        std::string title;
        std::string abstract;
        std::string keywords;

        int approval; //-1 - means not approved yet or it can also mean that its rejected, 1 means approved.

    public:
        ResearchPaper();
        void setPaperID(int);
        void setNumContributors(int);
        void setContributedFirst(std::string);
        void setContributedLast(std::string);
        void setContributedUni(std::string);
        void setContributedEmail(std::string);
        void setTitle(std::string);
        void setAbstract(std::string);
        void setKeywords(std::string);

        int getPaperID();
        int getApproval();
        std::string getKeywords() { return keywords; }
        std::vector<std::string> getContributedEmail() { return contributedEmail; }

        bool checkEmail(std::string);
        void display();
};

#endif // _RESEARCHPAPER_
