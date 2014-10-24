#include <iostream>
#include <vector>
#include "ResearchPaper.h"
#include <stdlib.h>

using namespace std;

ResearchPaper::ResearchPaper()
{
    paperID = 0;
    numContributors = 0;
    title = "";
    abstract = "";
    keywords = "";
    approval = -1;
}

ostream& operator<< (ostream& out, const ResearchPaper& temp)
{
    out << temp.paperID << "," << temp.numContributors << "," ;

    for(int i = 0; i < temp.numContributors; i++)
    {
        //first last uni email
        out << temp.contributedFirst[i] << ",";
        out << temp.contributedLast[i] << ",";
        out << temp.contributedUni[i] << ",";
        out << temp.contributedEmail[i] << ",";
    }
    out << temp.title << "," << temp.abstract << "," << temp.keywords << ",";

    out << temp.approval << endl;

    return out;
}

istream& operator>> (istream& in, ResearchPaper& temp)
{
    string tempString;
    getline(in, tempString, ',');
    temp.paperID = atoi(tempString.c_str());
    getline(in, tempString, ',');
    temp.numContributors = atoi(tempString.c_str());


    for(int i = 0; i < temp.numContributors; i++)
    {
        //read in first name
        getline(in, tempString, ',');
        temp.contributedFirst.push_back(tempString);

        //read in last name
        getline(in, tempString, ',');
        temp.contributedLast.push_back(tempString);

        //read in uni
        getline(in, tempString, ',');
        temp.contributedUni.push_back(tempString);

        //read in email
        getline(in, tempString, ',');
        temp.contributedEmail.push_back(tempString);
    }
    getline(in, temp.title, ',');
    getline(in, temp.abstract, ',');
    getline(in, temp.keywords, ',');
    getline(in, tempString, '\n');
    temp.approval = atoi(tempString.c_str());


    return in;
}

int ResearchPaper::getPaperID()
{
    return paperID;
}

void ResearchPaper::setPaperID(int temp)
{
    paperID = temp;
}

void ResearchPaper::setNumContributors(int temp)
{
    numContributors = temp;
}

void ResearchPaper::setContributedFirst(std::string temp)
{
    contributedFirst.push_back(temp);
}

void ResearchPaper::setContributedLast(std::string temp)
{
    contributedLast.push_back(temp);
}

void ResearchPaper::setContributedUni(std::string temp)
{
    contributedUni.push_back(temp);
}

void ResearchPaper::setContributedEmail(std::string temp)
{
    contributedEmail.push_back(temp);
}

void ResearchPaper::setTitle(std::string temp)
{
    title = temp;
}

void ResearchPaper::setAbstract(std::string temp)
{
    abstract = temp;
}

void ResearchPaper::setKeywords(std::string temp)
{
    keywords = temp;
}

bool ResearchPaper::checkEmail(string emailOfUserToCheck)
{
    for(int i = 0; i < numContributors; i++)
    {
        if (contributedEmail[i] == emailOfUserToCheck)
        {
            return true;
        }
    }
    return false;
}

void ResearchPaper::display()
{
    cout << endl;
    cout << "Paper Details:" << endl;
    cout << "Title: " << title << endl;
    cout << "Abstract: " << abstract << endl;
    cout << "Keywords: " << keywords << endl;
    cout << endl;
}

int ResearchPaper::getApproval()
{
    return approval;
}
