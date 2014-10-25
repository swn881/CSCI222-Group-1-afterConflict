#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "FunctionalitiesManagement.h"
#include "PreferenceManagement.h"
#include "ResearchPaper.h"
#include "User.h"
#include "Functionalities.h"
#include "PaperAssignment.h"

using namespace std;

void FuncManagement::menu()
{
    cout << "Functionalities Management page. . ." << endl << endl;
    int choice = 9;

    while (choice != 0)
    {
        cout << "1. Auto-assign papers to reviewers     //not implemented" << endl;
        cout << "2. Auto-assign preferences to reviewer" << endl;
        cout << "3. Manually set the number of papers A reviewer receive    //not implemented" << endl;
        cout << "4. Generate conference proceeding" << endl;
        cout << "5. Group paper         //not implemented" << endl;
        cout << "6. Set the number of reviewers paper receive" << endl;
        cout << "7. Set the number of papers reviewers receive" << endl;
        cout << "8. Enable/Disable paper reviews" << endl;
        cout << "9. Enable/Disable user response to the reviews" << endl;
        cout << "10. Enable/Disable discussion among reviewers" <<  endl;
        cout << "11. Enable/Disable paper submission" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            {
                cout << "Auto assign papers to reviewers" << endl;
                autoAssignPapersToReviewers();
            }
            break;
        case 2:
            {
                int decision;
                cout << "Auto assign preferences to reviewer" << endl;
                cout << "This is suggested to be done AFTER paper submission has been closed!" << endl;
                cout << "Are you sure?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Choice: ";
                cin >> decision;
                if (decision == 1)
                {
                    autoSpecifyPreference();
                    cout << "Assigned preference to reviewers " << endl;
                }

            }
            break;
        case 3:
            {
                cout << "Manually set the number of papers A reviewer receive" << endl;
            }
            break;
        case 4:
            {
                int decision;
                cout << "Generate conference proceeding" << endl;
                cout << "This is suggested to be done AFTER paper reviews has been closed!" << endl;
                cout << "Are you sure?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Choice: ";
                cin >> decision;
                if (decision == 1)
                {
                    autoSpecifyPreference();
                    cout << "Assigned preference to reviewers " << endl;
                }
                generateConferenceProceeding();
            }
            break;
        case 5:
            {
                cout << "Group apper" << endl;
            }
            break;
        case 6:
            {
                cout << "Set number of reviewers paper receive" << endl;
                setReviewerPaperReceive();
            }
            break;
        case 7:
            {
                cout << "Set number of papers reviewers receive" << endl;
                setPaperReviewerReceive();
            }
            break;
        case 8:
            {
                cout << "Enable/Disable paper reviews" << endl;
                enableRevSubmission();
            }
            break;
        case 9:
            {
                cout << "Enable/Disable user response to reviews" << endl;
                enableAutResponse();
            }
            break;
        case 10:
            {
                cout << "Enable/Disable discussion among reviewers" << endl;
                enableRevDiscussion();
            }
            break;
        case 11:
            {
                cout << "Enable/Disable paper submission" << endl;
                enablePapSubmission();
            }
            break;
        case 0:
            {
                cout << "EXITINNNN" << endl;
                cout << endl;
            }
            break;
        default:
            {
                cout << "Invalid choice!" << endl;
                cout << "Please try again!" << endl;
            }
        }
    }
}

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


    int userPreference = 0; //the users preference on the paper
    for(int i = 0; i < paperNum; i++)
    {
        vector <string> maybe; //keep track of users who have their preference of MAYBE and YES on each paper
        vector <string> yes;
        for(int j = 0; j < preferenceNum; j++) //at this point we can assume that preference num is equal to the num of users
        {

            //we also want to check how many papers the user has been assigned at the current moment
            //if he has already has e.g 5 papers assigned to him
            //then we dont consider him at all
            if(user[j].getNumPaperAssigned() < functionalities.getPaperReviewerReceive())
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
        }
        cout << "Paper " <<  i << ": ";
        for(int e = 0; e < yes.size(); e++)
            cout << yes[e] << "   ";
        cout << endl;

        cout << "Paper " <<  i << ": ";
        for (int t = 0; t < maybe.size(); t++)
            cout << maybe[t] << "   ";
        cout << endl;

        //by the end of this for loop we will have recorded each users preference on paper 1 (ON FIRST ENTRY)
        //we check the size of the YES vector with the number of reviewers that can be assigned to the paper (HOW MANY REVIEWERS EACH PAPER CAN RECEIVE)
        vector<string> confirmed; //this will contain the list of confirmed users to be assigned the paper *****
        if (yes.size() == functionalities.getReviewerPaperReceive())
        {
            //if the size if equal then we can just assigned these set of users with the paper
            //at this point we have already considered the num of papars each reviewer has currently been assigned with
            //to assign these users with this paper, we have to add the number of papers they have been assigned by 1,
            //add into the vector of the user class, the id of the paper
            //write it into the text file with the paper ID and the users that has been assigned with this paper

            cout << yes.size() << "   " << recordNum << endl;
            for (int r = 0; r < yes.size(); r++)
            {

                bool check = false;
                for(int q = 0; q < recordNum; q++)
                {
                    //find the users class, look through the list of users
                    if (yes[r] == user[q].getUsername())
                    {
                        //if equals this is the class of that user that we are trying to modify
                        user[q].addNumPaperAssigned();
                        user[q].addPaperAssigned(researchPaper[i].getPaperID()); //get the id of the paper
                        check = true; //move on to the next in the yes list
                    }
                }
            }
            //at this point all users that is assigned this paper has been updated!
            //we update the users at the end of all this
            //should we update the paper assignment class here? F YEAH

            //initialize the paper assignment class, this class stores the paper id, the user assigned to this paper and their reviews
            PaperAssignment paperAssignment;
            paperAssignment.setPaperID(researchPaper[i].getPaperID());
            paperAssignment.setNumAssignedForReview(yes.size());
            for(int w = 0;  w < yes.size(); w++)
            {
                paperAssignment.addUser(yes[w]);
            }

            writeAssignment(paperAssignment);
        }
        else if (yes.size() < functionalities.getReviewerPaperReceive())
        {
            //do a while loop here, to make sure that the size of the vector matches the number we need
            //if it is lesser, then we have to consider the users who gave preference of maybe.
            //check how many users from the maybe that we need,
            //choose the best candidate to be assigned as the reviewer for the paper based on their expertise
            while (yes.size != functionalities.getReviewerPaperReceive())
            {
                //check the list of maybe now
                //check the paper keywords and user expertise

                for (int w = 0; w < maybe.size(); w++)
                {
                    bool check = false;
                    for(int q = 0; q < recordNum; q++)
                    {
                        //find the users class, look through the list of users
                        if (maybe[w] == user[q].getUsername())
                        {
                            //if equals this is the user who we want to get his expertise from
                            userExpertise = user[q].getExpertise();

                            //since i saved the expertise in 1 string, each expertise seperated with ., i need to split the keywords
                            vector <string> expertise;



                            check = true; //move on to the next in the yes list
                        }
                    }
                }

            }


            //we assign all those in yes vector as the confirmed reviewers, add the number of papers they have been assigned
            //also add it into vector inside the user class the id of the paper
            //write it into text file
        }
//        else if (yes.size() > functionalities.getReviewerPaperReceive())
//        {
//            //if it is more than, then we have to consider the best suited users for the paper
//            //based on the keywords and expertise
//        }
    }
    //dont forget to write to file
}

void FuncManagement::writeAssignment(PaperAssignment paperAssignment)
{
    ofstream outfile;
    outfile.open("System/PaperAssignment.txt");

    outfile << paperAssignment;

    outfile.close();
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
            break;
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            break;
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
            break;
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            break;
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
            break;
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            break;
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
            break;
            case 2:
            {
                cout << "No changes made!" << endl;
                check = true;
            }
            break;
            default:
            {
                cout << "Invalid choice!" << endl;
                check = false;
            }
            break;
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
