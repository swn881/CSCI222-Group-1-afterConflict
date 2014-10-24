#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "FunctionalitiesManagement.h"
#include "PreferenceManagement.h"
#include "ResearchPaper.h"
#include "User.h"
#include "Functionalities.h"

using namespace std;

void FuncManagement::autoAssignPapersToReviewers()
{
    int recordNum = countUser();

    User user[recordNum];

    ifstream infile;
    infile.open("System/UserList.txt");

    for(int i = 0; i < recordNum; i++)
    {
        infile >> user[i];
    }

    infile.close();
    //at this point i will have the list of users

    int paperNum = countPaper();

    ResearchPaper researchPaper[paperNum];

    infile.open("System/Papers/Papers.txt");

    for(int i = 0; i < paperNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();
    //at this point i will have the list of papers

    Functionalities functionalities;
    loadFunctionalities(functionalities);
    //number of papers that can be assigned to each user or vice versa is loaded into the functionalities at this point

    int preferenceNum = countPreference();

    Preference preference[preferenceNum];

    infile.open("System/Preference.txt");

    for(int i = 0; i < preferenceNum; i++)
    {
        infile >> preference[i];
    }

    infile.close();
    //at this point i will have the list of preferences of each users

    //for each paper, i look for users whose preferece is "Yes" on each paper
    //if there are more users to be assigned to the paper than the the allowed users(allowed users- being the number set in the system)
    //we have to first compare how closely related is the expertise of the user to the keywords in the paper
    //if there are 0 matches, we dont use the person; the more matches the better
    //if all have equal matches we randomly select among the people

    vector <string> maybe; //keep track of users who have their preference of MAYBE and YES on each paper
    vector <string> yes;
    int userPreference = 0; //the users preference on the paper
    for(int i = 0; i < paperNum; i++)
    {
        for(int j = 0; j < preferenceNum; j++) //at this point we can assume that preference num is equal to the num of users
        {
            //in the file we will equal number of users who have given their preference
            //so at this point, auto assignment of preference must have been done
            userPreference = preference[j].getPreference(i);  //user number 1's preference on first paper (ON COMING IN THE FIRST TIME)

            //check his preference on the paper
            //we will only consider yes, or maybe and push it into the vector
            /*
                preferences:
                1. yes
                2. no
                3. maybe
                4. conflict of interest

            */
            if(userPreference == 1)
            {
                yes.push_back(preference[j].getUsername());
            }
            else if (userPreference == 3)
            {
                maybe.push_back(preference[j].getUsername());
            }
        }
        //by the end of this for loop we will have recorded each users preference on paper 1 (ON FIRST ENTRY)
        //we check the size of the YES vector with the number of reviewers that can be assigned to the paper (HOW MANY REVIEWERS EACH PAPER CAN RECEIVE)

        //HOW DO WE KEEP TRACK OF HOW MANY PAPERS A USER HAS BEEN ASSIGNED WITH?

        if (yes.size() == functionalities.getReviewerPaperReceive())
        {
            //if the size if equal then we can just assigned these set of users with the paper

        }
    }
}

void FuncManagement::checkNumPaperAssigned(string user)
{
    //function to check how many paper user has been assigned
}

//remember to read from file then write to file to ensure getting the latest version of the file;
void FuncManagement::enableAutResponse()
{
    Functionalities functionalities;
    loadFunctionalities(functionalities);

    //tell the user what the current status is
    if (functionalities.getAuthorResponse() == 1)
    {
        cout << "Authors at the current moment are able to respond to the reviews on their paper." << endl;
    }
    else
    {
        cout << "Authors at the current moment are not able to respond to the reviews on their paper." << endl;
    }
    //checking to make sure user enters correctly
    int choice;
    bool check = false;
    while (check == false)
    {
        cout << "Are you sure you want to enable/disable author response?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "Change successful!" << endl;
                functionalities.setAuthorResponse();
                check = true;
            }
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
                check = false;
            }

        }

    }
    //write it into file again
    writeFunctionalities(functionalities);
}

void FuncManagement::enableRevDiscussion()
{
    Functionalities functionalities;
    loadFunctionalities(functionalities);

    if (functionalities.getReviewDiscussion() == 1)
    {
        cout << "PC at the current moment are able to discuss about reviews." << endl;
    }
    else
    {
        cout << "PC at the current moment are not able to discuss about reviews." << endl;
    }

    //checking to make sure user enters correctly
    int choice;
    bool check = false;
    while (check == false)
    {
        cout << "Are you sure you want to enable/disable review discussion?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "Change successful!" << endl;
                functionalities.setReviewDiscussion();
                check = true;
            }
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
                check = false;
            }

        }

    }

    writeFunctionalities(functionalities);
}

void FuncManagement::enableRevSubmission()
{
    Functionalities functionalities;
    loadFunctionalities(functionalities);

    //tell the user what the current status is
    if (functionalities.getReviewSubmission() == 1)
    {
        cout << "PCs at the current moment are able to upload their reviews on assigned papers." << endl;
    }
    else
    {
        cout << "PCs at the current moment are not able to upload their reviews on assigned papers." << endl;
    }
    //checking to make sure user enters correctly
    int choice;
    bool check = false;
    while (check == false)
    {
        cout << "Are you sure you want to enable/disable review submission?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "Change successful!" << endl;
                functionalities.setReviewSubmission();
                check = true;
            }
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
                check = false;
            }

        }

    }


    writeFunctionalities(functionalities);
}

void FuncManagement::enablePapSubmission()
{
    Functionalities functionalities;
    loadFunctionalities(functionalities);

        //tell the user what the current status is
    if (functionalities.getPaperSubmission() == 1)
    {
        cout << "Authors at the current moment are able to upload their papers." << endl;
    }
    else
    {
        cout << "Authors at the current moment are not able to upload their papers." << endl;
    }
    //checking to make sure user enters correctly
    int choice;
    bool check = false;
    while (check == false)
    {
        cout << "Are you sure you want to enable/disable paper submission?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "Change successful!" << endl;
                functionalities.setPaperSubmission();
                check = true;
            }
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
                check = false;
            }

        }

    }
    writeFunctionalities(functionalities);
}

void FuncManagement::setReviewerPaperReceive()
{
    Functionalities functionalities;
    loadFunctionalities(functionalities);
    int temp;
    cout << "The number of reviewers each paper will receive at the current moment is " << functionalities.getReviewerPaperReceive() << endl;

    cout << "What is the new number of reviewers each paper will receive? " << endl;
    cout << "Number of reviewer per paper: ";
    cin >> temp;
    functionalities.setReviewerPaperReceive(temp);
    writeFunctionalities(functionalities);
}

void FuncManagement::setPaperReviewerReceive()
{
    //remember to read from file then write to file when done, to make sure to get most up to date from records
    Functionalities functionalities;
    loadFunctionalities(functionalities);
    int temp;
    cout << "The number of papers each reviewer will receive at the current moment is " << functionalities.getPaperReviewerReceive() << endl;

    cout << "What is the new number of papers each reviewer will receive?" << endl;
    cout << "Number of paper per reviewer: ";
    cin >> temp;
    functionalities.setPaperReviewerReceive(temp);
    writeFunctionalities(functionalities);
}


//this point on, they do not interfere with the Functionalities.txt
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

void FuncManagement::loadFunctionalities(Functionalities& functionalities)
{
    ifstream infile;
    infile.open("System/Functionalities.txt");

    infile >> functionalities;

    infile.close();
}

void FuncManagement::writeFunctionalities(Functionalities& functionalities)
{
    ofstream outfile;
    outfile.open("System/Functionalities.txt");

    outfile << functionalities;

    outfile.close();
}
