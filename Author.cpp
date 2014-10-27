#include "Author.h"
#include "PaperManagement.h"
#include "UserBoundary.h"
#include "Conference.h"
#include <iostream>
#include <fstream>

using namespace std;

void Author::changeDetails(std::string currentlyLoggedIn)
{
    UserBoundary userBoundary;
    userBoundary.changeDetails(currentlyLoggedIn);
}

void Author::changePassword(string currentlyLoggedIn)
{
    UserBoundary userBoundary;
    userBoundary.changePassword(currentlyLoggedIn);
}

void Author::submitPaper()
{
    PaperManagement paperManagement;
    paperManagement.submitPaper();
}

void Author::modifyPaperSubmission(std::string currentlyLoggedIn)
{
    PaperManagement paperManagement;
    paperManagement.modifyPaperSubmission(currentlyLoggedIn);
}

void Author::notifications(string currenlyLoggedIn)
{
    PaperManagement paperManagement;
    paperManagement.notifications(currenlyLoggedIn);
}

void Author::participateConference(string currentlyLoggedIn)
{
    int numConference = countConference();

    if (numConference == 0)
    {
        cout << "There are no confereces available." << endl;
    }
    else
    {
        Conference conference[numConference];
        ifstream infile;
        infile.open("System/Conference.txt");
        for(int i = 0; i < numConference; i++)
        {
            infile >> conference[i];
        }
        infile.close();
        //get all the conference
        int choice;

        cout << "Which conference do you wish to participate? " << endl;
        for(int i = 0; i < numConference; i++)
        {
            cout << ">>>>>> " <<  conference[i].getConferenceName() << " <<<<<<" << endl;
            cout << "Do you wish to participate in this conferencE?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choice: ";
            cin >> choice;

            if(choice == 1)
            {
                cout << "Participating in the conference!" << endl;
                conference[i].addNumUser();
                conference[i].addUser(currentlyLoggedIn);
            }
        }
        //write to file
        ofstream outfile;
        outfile.open("System/Conference.txt");

        for(int i = 0; i < numConference; i++)
        {
            outfile << conference[i];
        }

        outfile.close();
    }
}

int Author::countConference()
{
    //counting the number of lines
    int recordCount = 0;
    ifstream infile;
    infile.open("System/Conference.txt");
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
