#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "FunctionalitiesManagement.h"
#include "PreferenceManagement.h"
#include "ResearchPaper.h"
#include "User.h"

using namespace std;

FuncManagement::FuncManagement()
{
    ifstream infile;
    infile.open("System/Functionalities");

    infile >> functionalities;

    infile.close();
}

/*
//read in the current "status" of tasks
private:

public:
    *void generateConferenceProceeding(); //get the list of papers which has been approved
    *void specifyPreference(); //Specify preference for user who has been asigned papers and have yet to assign their own preference
    *void setReviewerPaperReceive(); //set the number of reviewers paper receive
    *void setPaperReviewerReceive(); //set the number of papers each reviewers receive
    void enableRevSubmission(): //enable review submission by pc
    void enablePapSubmission(); //enable paper submission by authors
    void enableAutResponse(); //emable author response towards their paper which has been reviewed
    void enableRevDiscussion(); //enable review discussion among reviewers
*/

void FuncManagement::enableAutResponse()
{
    functionalities.setAuthorResponse();
}

void FuncManagement::enableRevDiscussion()
{
    functionalities.setReviewDiscussion();
}

void FuncManagement::enableRevSubmission()
{
    functionalities.setReviewSubmission();
}

void FuncManagement::enablePapSubmission()
{
    functionalities.setPaperSubmission();
}

void FuncManagement::setReviewerPaperReceive()
{
    int temp;
    cout << "What is the new number of reviewers each paper will receive? " << endl;
    cout << "Number of reviewer per paper: ";
    cin >> temp;
    functionalities.setReviewerPaperReceive(temp);
}

void FuncManagement::setPaperReviewerReceive()
{
    int temp;
    cout << "What is the new number of papers each reviewer will receive?" << endl;
    cout << "Number of paper per reviewer: ";
    cin >> temp;
    functionalities.setPaperReviewerReceive(temp);
}


void FuncManagement::autoSpecifyPreference()
{
    PrefManagement prefManagement;

    int userNum = countUser();

    User user[userNum];
    ifstream infile;
    infile.open("System/UserList.txt");

    for(int i = 0; i < userNum; i++)
    {
        infile >> user[i];
    }
    infile.close();
    //at this point i have the list of users stored
    //now i want to check which user has not actually specified preference

    for (int i = 0; i < userNum; i++)
    {
        if (prefManagement.checkUser(user[i].getUsername()) == false) //this is the function to check if user has already specified a preference or not, true meaning it has specified a preference
        {
            //false meaning he has not specified a preference yet
            //set the preference for all papaers OF THE USER to maybe
            prefManagement.specifyMaybe(user[i].getUsername()); //will add it to the end
        }
    }
}


void FuncManagement::generateConferenceProceeding()
{
    vector<int> approvedPapers;
    int numOfPapers = countPaper();

    ResearchPaper researchPaper[numOfPapers];

    ifstream infile;
    infile.open("System/Papers/Papers.txt");

    for(int i = 0; i < numOfPapers; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();

    //at this point i have read all the papers in and i want to check their approvals and save their IDs

    for(int i = 0; i < numOfPapers; i++)
    {
        if (researchPaper[i].getApproval() == 1) //1 means the paper is approved
        {
            //if approved i add the id into the vector so i can have a list of accepted papers
            approvedPapers.push_back(researchPaper[i].getPaperID());
        }
    }

    //once i get the list of accepted papers then i throw them into a file
    //what do i do with it next?

    ofstream outfile;
    outfile.open("System/ConfProceeding.txt");

    for(unsigned int i = 0; i < approvedPapers.size(); i++)
    {
        outfile << approvedPapers[i] << endl;
    }
    outfile.close();

    //now i will have a list of accepted papers in a text file;
}

int FuncManagement::countPaper()
{
    //counting the number of lines
    int recordCount = 0;
    ifstream infile;
    infile.open("System/Papers/Papers.txt");
    while (!infile.eof())
    {
        string line = " ";
        getline(infile, line, '\n');
        if (!line.empty())
            recordCount++;
        infile.ignore();
    }
    infile.close();
    return recordCount;
}

int FuncManagement::countUser()
{
    //counting the number of lines
    int recordCount = 0;
    ifstream infile;
    infile.open("System/UserList.txt");
    while (!infile.eof())
    {
        string line = " ";
        getline(infile, line, '\n');
        if (!line.empty())
            recordCount++;
        infile.ignore();
    }
    infile.close();
    return recordCount;
}

int FuncManagement::countPreference()
{
    int recordCount = 0;
    ifstream infile;
    infile.open("System/Preference.txt");
    while (!infile.eof())
    {
        string line = " ";
        getline(infile, line, '\n');
        if (!line.empty())
            recordCount++;
        infile.ignore();
    }
    infile.close();
    return recordCount;
}
