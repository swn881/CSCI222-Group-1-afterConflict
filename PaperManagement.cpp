#include <iostream>
#include <windows.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <algorithm>
#include "PaperManagement.h"
#include "ResearchPaper.h"
#include "User.h"
#include "PaperAssignment.h"
#include "Preference.h"
#include "PaperDiscussion.h"
#include "Functionalities.h"

using namespace std;

//To get the path of the folder...
string ExePath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of("\\/");
    return string(buffer).substr(0, pos);
}

void PaperManagement::notifications(string currentlyLoggedIn)
{
    int paperNum = countPaper();
    ResearchPaper researchPaper[paperNum];
    ifstream infile;
    infile.open("System/Papers/Papers.txt");
    for(int i = 0; i < paperNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();

    int recordNum = countUser();
    User user[recordNum];
    infile.open("System/UserList.txt");
    for(int i = 0; i < recordNum; i++)
    {
        infile >> user[i];
    }
    infile.close();

    string userEmail;
    for(int i = 0; i < recordNum; i++)
    {
        if (user[i].getUsername() == currentlyLoggedIn)
        {
            userEmail = user[i].getEmail();
        }
    }

    for(int i = 0; i < paperNum; i++)
    {
        bool isFound = false;
        vector<string> contributors = researchPaper[i].getContributedEmail();
        for(int j = 0; j < contributors.size() && isFound == false; j++)
        {
            if(contributors[j] == userEmail)
            {
                //means we want to display the status of this paper
                researchPaper[i].display();

                switch(researchPaper[i].getApproval())
                {
                    case -1:
                    {
                        cout << "The paper has either been rejected or still awaiting approval!" << endl;
                    }
                    break;
                    case 1:
                    {
                        cout << "The paper has been approved!" << endl;
                    }
                }

                isFound = true;
            }
        }
    }
}

void PaperManagement::manuallyAssignPaper(string currentlyLoggedIn)
{
    int paperNum = countPaper();
    ResearchPaper researchPaper[paperNum];
    ifstream infile;
    infile.open("System/Papers/Papers.txt");
    for(int i = 0; i < paperNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();

    int reviewNum = paperNum;
    PaperAssignment paperAssignment[reviewNum];
    infile.open("System/PaperAssignment.txt");
    for(int i = 0; i < reviewNum; i++)
    {
        infile >>paperAssignment[i];
    }
    infile.close();

    Functionalities functionalities;
    infile.open("System/Functionalities.txt");
    infile >> functionalities;
    infile.close();
    //load the functionalities in

    int recordNum = countUser();
    User user[recordNum];
    infile.open("System/UserList.txt");
    for(int i = 0; i < recordNum; i++)
    {
        infile >> user[i];
    }
    infile.close();
    //loaded each users

    //to manually assign a paper, we must check how many reviewers has been assigned to a apper
    //displays papers that are allowed to b assigned to a user
    //we should also check how many papers a reviewer has been assigned
    //displays users that are allowed to b assigned more papers
    vector<int>paperPosition; //keeping track of papers which can still be assigned to users
    vector<int>paperRemaining; //keep track on how many we can add
    vector<int>userPosition; //keeping track of users who can accept more papers
    vector<int>userRemaining; //how many more can we add

    string userEmail;
    for(int i = 0; i < recordNum; i++ )
    {
        if(user[i].getUsername() == currentlyLoggedIn)
        {
            userEmail = user[i].getEmail();
        }
    }

    for(int i = 0; i < reviewNum; i++)
    {
        if (paperAssignment[i].getNumAssignedForReview() < functionalities.getReviewerPaperReceive())
        {
            //means the number of papers it can accept is not maxed yet
            //save the position
            vector<string> contributedList = researchPaper[i].getContributedEmail(); //this is to check and make sure the user do not assign himself to his paper
            if(find(contributedList.begin(), contributedList.end(), userEmail) == contributedList.end())
            {
                paperPosition.push_back(i);
                paperRemaining.push_back(functionalities.getReviewerPaperReceive() - paperAssignment[i].getNumAssignedForReview()); //keep track of the diff on how many we can add
            }
        }
    }
    //we got the list of papers

    for(int i = 0; i < recordNum; i++)
    {
        if(user[i].getNumPaperAssigned() < functionalities.getPaperReviewerReceive() && user[i].getType() != "A" ) //make sure he is not author
        {
            //if lesser means we can assign more papers to him/her
            userPosition.push_back(i);
            userRemaining.push_back(functionalities.getPaperReviewerReceive() - user[i].getNumPaperAssigned());
            //keep track of how many more we can add
        }
    }
    //we got the list of users who still can receive more papers for review

    for (int i = 0; i < paperPosition.size(); i++)
    {
        int choice = 9;
        while(choice != 2 && paperRemaining[i] != 0)  //ill reduce paper remaining as i keep moving on
        {
            cout << "Papers that can be assigned more reviewers. . ." << endl;
            researchPaper[paperPosition[i]].display();

            cout << "You can add " << paperRemaining[i] << " more paper(s). " << endl;

            cout << "Do you want to assign more reviewers to this paper?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch(choice)
            {
                case 1:
                {
                    bool userCheck = false; //checking to check if there are actually anymore users to be assigned the paper
                    //if all of vectors is 0 means theres no more user to assign papers
                    for(int k = 0; k < userRemaining.size(); k++)
                    {
                        if(userRemaining[k] > 0)
                            userCheck = true; //if its true, there are users that can still be assigned more papers

                    }

                    //display the list of users who can still be assigned more papers
                    for(int k = 0; k < userPosition.size() && userCheck == true; k++)
                    {
                        if(userRemaining[k] != 0)
                        {
                            int decision = 9;
                            cout << endl;
                            cout << "Users who can be assigned more papers. . ." << endl;
                            user[userPosition[k]].display();
                            cout << "User can still be assigned " << userRemaining[k] << " more papers." << endl;

                            cout << endl;
                            cout << "Do you want to assign this user with this paper?" << endl;
                            researchPaper[paperPosition[i]].display();

                            cout << "1. Yes" << endl;
                            cout << "2. No " << endl;
                            cout << "Choice: ";
                            cin >> decision;

                            if (decision == 1)
                            {
                                paperRemaining[i]--; //paper cannot be assigned anymore users
                                userRemaining[k]--;
                                cout << "Assigned" << endl;
                                paperAssignment[paperPosition[i]].setNumAssignedForReview(paperAssignment[paperPosition[i]].getNumAssignedForReview() + 1);
                                paperAssignment[paperPosition[i]].addUser(user[userPosition[k]].getUsername());
                                //dont just add assignment, user class also must add

                                user[userPosition[k]].addNumPaperAssigned();
                                user[userPosition[k]].addPaperAssigned(researchPaper[paperPosition[i]].getPaperID());
                            }
                            else
                            {
                                cout << "not assigning" << endl;
                            }
                        }
                    }
                }
                break;
                case 2:
                {
                    cout << "Okay moving on to next paper " << endl << endl;
                }
                break;
                default:
                {
                    cout << "Wrong input." << endl;
                    cout << "Lets try that again!" << endl << endl;
                }
            }
        }
        //dont forget to write into file
    }
    //writing into files
    writeAssignment(paperAssignment, reviewNum);
    ofstream outfile;
    outfile.open("System/UserList.txt");
    for(int i = 0; i < recordNum; i++)
    {
        outfile << user[i];
    }
    outfile.close();
}


void PaperManagement::approvePaper(std::string currentlyLoggedIn)
{
    //to approve paper i need to make sure the user doesnt approve his own paper
    //making the assumption that ALL reviews has been done and there can be no more submission of reviews

    //load the papers in, the reviews, and the discussion too

    int paperNum = countPaper();
    ResearchPaper researchPaper[paperNum];
    ifstream infile;
    infile.open("System/Papers/Papers.txt");
    for(int i = 0; i < paperNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();

    int discussionNum = countDiscussion();
    PaperDiscussion paperDiscussion[discussionNum];
    infile.open("System/PaperDiscussion.txt");
    for(int i = 0; i < discussionNum; i++)
    {
        infile >> paperDiscussion[i];
    }
    infile.close();

    int reviewNum = paperNum;
    PaperAssignment paperAssignment[reviewNum];
    infile.open("System/PaperAssignment.txt");
    for(int i = 0; i < reviewNum; i++)
    {
        infile >> paperAssignment[i];
    }
    infile.close();
    //at this point we have the assignments of each user, the paper, and the discussions

    int recordNum = countUser();
    User user[recordNum];
    infile.open("System/UserList.txt");
    for(int i = 0; i < recordNum; i++)
    {
        infile >> user[i];
    }
    infile.close();

    //we want to keep track of users who submitted/contributed to the paper, we want to make sure that its not the current
    //logged in user who is currently approving the papers, DONT WANT HIM TO APPROVE A PAPER HE HIMSELF SUBMITTED
    int userPosition = 0;
    string userEmail; //EMAIL OF CURRENTLY LOGGED IN USER
    //i want to get the email of the currently logged in user
    for(int j = 0; j < recordNum; j++)
    {
        if(user[j].getUsername() == currentlyLoggedIn)
        {
            //the id matches, mean this is the person who is currently logged in
            userPosition = j;
            userEmail = user[j].getEmail();
        }
    }

    //for each paper show details about the user who contributed
    for (int i = 0; i < paperNum; i++)
    {
        bool isContributor = false; //to keep track if he is the contributor of the paper
        cout << ">>>>>> Paper Details <<<<<<" << endl;
        researchPaper[i].display();

        for(int j = 0; j < recordNum; j++)
            //now get the users who actually submitted the paper, match the email
            //get the number of contributors
        {
            vector<string> contributedEmails = researchPaper[i].getContributedEmail();
            //we got the emails of the user who contributed, now we need to check their emails to know if they submitted the paper or not
            for (int w = 0; w < contributedEmails.size(); w++)
            {
                if (user[j].getEmail() == contributedEmails[w])
                {
                    //if we find something, means the current user we in, contributed to the paper.
                    //display details about thie guy
                    cout << ">>> Users contributed to this paper <<< " << endl;
                    user[j].display();
                    //one extra checking, for the isContributor
                    if (userEmail == contributedEmails[w])
                    {
                        isContributor = true; //the guy currently logged in is the contributor of the paper
                    }
                }
            }
        }
        cout << endl;
        for(int j = 0; j < recordNum; j++)
        {
            int numAssigned = user[j].getNumPaperAssigned(); //get the number of assigned paper;
            if (numAssigned != 0)
            {
                vector<int> paperAssigned = user[j].getPaperAssigned();
                for(int k = 0; k < numAssigned; k++)
                {
                    if (paperAssigned[k] == researchPaper[i].getPaperID()) //if the paper ID matches, means they did submit the paper
                    {
                        cout << ">>> User assigned this paper <<< " << endl;
                        user[j].display();
                    }
                }
            }
            //at this point we get the users who are assigned to each paper TO REVIEW, NOT THOSE WHO SUBMITTED
        }
        cout << endl;

        //get the completed reviewsssss
        //get the review num of each paper
        int numReviews = paperAssignment[i].getNumUserReviewed();
        if(numReviews != 0)
        {
            vector<PaperReview*> paperReviews = paperAssignment[i].getUserReview();
            for(int k = 0; k < numReviews; k++)
            {
                cout << ">>> Reviews done by user <<< " << endl;
                cout << "Username: " << paperReviews[k]->getReviewedBy() << endl;
                paperReviews[k]->display();
                cout << endl;
            }
        }

        bool isFound = false;
        //get the discussion for the paper
        for (int j = 0; j < discussionNum && isFound == false; j++)
        {
            if(paperDiscussion[j].getPaperID() == researchPaper[i].getPaperID())
            {
                cout << "Paper discussions: " << endl;
                int numReviewerDiscussion = paperDiscussion[j].getNumReviewerResponse();
                if(numReviewerDiscussion != 0)
                {
                    vector<string>reviewerDiscussions = paperDiscussion[j].returnReviewerDiscussions();
                    for(int k = 0; k < numReviewerDiscussion; k++)
                    {
                        cout << reviewerDiscussions[k] << endl;
                        cout << endl;
                    }
                }

                isFound = true;
            }
        }

        if (isContributor == false)
        {
            bool check = false;
            int choice;
            while(check == false)
            {
                cout << "Do you want to approve this paper? " << endl;
                cout << "1. Yes" << endl;
                cout << "2. No (MEANS REJECTING)" << endl;
                cout << "Choice: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:
                    {
                        cout << "Paper approved!" << endl;
                        check = true;
                        researchPaper[i].setApproval();
                    }
                    break;
                    case 2:
                    {
                        cout << "Paper rejected" << endl;
                        researchPaper[i].setReject();
                        check = true;
                    }
                    break;
                    default:
                    {
                        cout << "Wrong input!" << endl;
                        cout << "Please try again!" << endl;
                        check = false;
                    }
                    break;
                }
            }
        }
        else
        {
            cout << "You are not allowed to approve a paper that you have contributed" << endl;
        }
        cout << "-------------------------------------------------------------------" << endl;
    }
    //dont forget to write into file;
    writeAll(researchPaper, paperNum);
}

void PaperManagement::reviewDiscussion(string currentlyLoggedIn)
{
    //this is used for reviewers
    //check which paper he is assigned with
    //making the assumption that review submission has already been closed
    //check who has been assigned to review the same paper

    int reviewNum = countPaper();
    PaperAssignment paperAssignment[reviewNum];

    ifstream infile;
    infile.open("System/PaperAssignment.txt");
    for(int i = 0; i < reviewNum; i++)
    {
        infile >> paperAssignment[i];
    }
    infile.close();

    int paperNum = reviewNum;
    ResearchPaper researchPaper [paperNum];
    infile.open("System/Papers/Papers.txt");
    for(int i = 0; i < paperNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();
    //we have load the file which has paper assignments and also the paper itself

    //gotta check if the paper already has an existing discussion or not
    int discussionNum = countDiscussion();
    PaperDiscussion paperDiscussion[discussionNum];
    infile.open("System/PaperDiscussion.txt");
    for(int i = 0; i < discussionNum; i++)
    {
        infile >> paperDiscussion[i];
    }
    infile.close();
    //we have all the currently existing discussions

    //we have to check what paper he is reviewing

    int paperID = 0;
    int paperPosition = 0;
    for(int i = 0; i < reviewNum; i++)
    {
        bool isFound = false;
        int numAssignedReview = paperAssignment[i].getNumAssignedForReview(); //get the number of user assigned to review this paper
        if (numAssignedReview != 0) //there are assigned users
        {
            //get the list of users assigned
            vector<string> userList = paperAssignment[i].getUserList();
            if (find(userList.begin(), userList.end(), currentlyLoggedIn) != userList.end()) //we manage to find the username assigned to this paper
                //to the guy who is trying to do the discussion
            {
                int choice = 9;
                cout << "Do you want to go into discussion for this paper?" << endl;
                researchPaper[i].display();
                cout << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Choice: ";
                cin >> choice;

                if (choice == 1)
                {
                    //get the id of the paper he is reviewing
                    isFound = true;
                    paperID = paperAssignment[i].getPaperID(); //he is reviewing this paper
                    paperPosition = i; // we want to keep this position around so we can get the reviews easily
                }
                else
                {
                    //user does not want to check discussion for the paper
                    cout << "Not going into paper discussion. . ." << endl;
                }
            }
        }

        if (isFound) //we found the paper ID this person is reviewing && user wanted to discuss about this paper
        {
            int discussionPosition;
            //now to check if the paper has existing discusiion, match the id
            bool isExist = false;
            for(int j = 0; j < discussionNum && isExist == false; j++)
            {
                if(paperDiscussion[j].getPaperID() == paperID)
                {
                    //we found a match, means there is an existing discussion
                    isExist = true;
                    discussionPosition = j;
                }
            }

            if (!isExist) //means we couldnt find a discussion, we should make a new one
            {
                PaperDiscussion newDiscussion;
                newDiscussion.setPaperID(paperID);

                int choice = 9;
                while (choice != 0)
                {
                    cout << "Starting the new discussion . . ." << endl;
                    cout << "What would you like to do?" << endl;
                    cout << "1. View other reviewers review on the paper" << endl;
                    cout << "2. Write about something. . ." << endl;
                    cout << "0. Quit" << endl;
                    cout << "Choice: ";
                    cin >> choice;

                    cout << endl;
                    if (choice == 1)
                    {
                        //display all the reviews done on this paper
                        int numUserReviewed = paperAssignment[paperPosition].getNumUserReviewed();
                        if (numUserReviewed != 0)
                        {
                            vector<PaperReview*> userReview = paperAssignment[paperPosition].getUserReview();
                            for (int q = 0; q < numUserReviewed; q++)
                            {
                                cout << "User ID: >>>>>> " << userReview[q]->getReviewedBy() << " <<<<<<" << endl;
                                cout << "Paper Review: " << endl;
                                userReview[q]->display();
                            }
                            cout << endl;
                        }
                    }
                    else if (choice == 2)
                    {
                        cin.ignore();
                        cout << "Start the discussion by writing something!" << endl;
                        cout << "Comment: ";
                        string tempString;
                        getline(cin, tempString, '\n');

                        tempString = currentlyLoggedIn + ": " + tempString; //add it with the id infront so it becomes swn881: discusssion
                        newDiscussion.addNumReviewerResponse(); //add the number of response by reviewers by 1
                        newDiscussion.addReviewerDiscussion(tempString);
                    }
                    else if (choice == 0)
                    {
                        cout << "Exitting!" << endl;
                        //write discussion into file
                        ofstream outfile;
                        outfile.open("System/PaperDiscussion.txt", ios::app);

                        outfile << newDiscussion;


                        outfile.close();
                    }
                }
            }
            else if (isExist)
            {
                int choice = 9;
                while (choice != 0)
                {
                    cout << "Participating in the discussion!" << endl;
                    cout << "What would you like to do? " << endl;
                    cout << "1. View other discussions" << endl;
                    cout << "2. View other reviewer's review" << endl;
                    cout << "3. Write a discussion!" << endl;
                    cout << "0. Exit" << endl;
                    cout << "Choice: ";
                    cin >> choice;
                    cout << endl;
                    switch (choice)
                    {
                        case 1:
                        {
                            cout << "Viewing other discussions. . ." << endl;
                            //displaying all the discussions in the system
                            int numReviewerResponse = paperDiscussion[discussionPosition].getNumReviewerResponse();
                            if (numReviewerResponse != 0)
                            {
                                vector<string> reviewerDiscussion = paperDiscussion[discussionPosition].returnReviewerDiscussions();
                                for(int q = 0; q < numReviewerResponse; q++)
                                {
                                    cout << reviewerDiscussion[q] << endl << endl;
                                }
                            }
                            else
                            {
                                cout << "No reviewer discussion!" << endl;
                                //this happens as author is able to give response to the reviews first before the reviewers
                            }
                        }
                        break;
                        case 2:
                        {
                            cout << "View other reviewer's review" << endl;
                            //display all the reviews done on this paper
                            int numUserReviewed = paperAssignment[paperPosition].getNumUserReviewed();
                            if (numUserReviewed != 0)
                            {
                                vector<PaperReview*> userReview = paperAssignment[paperPosition].getUserReview();
                                for (int q = 0; q < numUserReviewed; q++)
                                {
                                    cout << "User ID: >>>>>> " << userReview[q]->getReviewedBy() << " <<<<<<" << endl;
                                    cout << "Paper Review: " << endl;
                                    userReview[q]->display();
                                }
                                cout << endl;
                            }
                        }
                        break;
                        case 3:
                        {
                            cout << "Write a discusion!" << endl;
                            cin.ignore();
                            cout << "Write something!" << endl;
                            cout << "Comment: ";
                            string tempString;
                            getline(cin, tempString, '\n');

                            tempString = currentlyLoggedIn + ": " + tempString; //add it with the id infront so it becomes swn881: discusssion
                            paperDiscussion[discussionPosition].addNumReviewerResponse(); //add the number of response by reviewers by 1
                            paperDiscussion[discussionPosition].addReviewerDiscussion(tempString);
                        }
                        break;
                        case 0:
                        {
                            cout << "Exiting!" << endl;
                            //write discussion into file
                            ofstream outfile;
                            outfile.open("System/PaperDiscussion.txt");

                            for (int i = 0; i < discussionNum; i++)
                            {
                                outfile << paperDiscussion[i];
                            }

                            outfile.close();
                        }
                        break;
                        default:
                        {
                            cout << "Invalid input!" << endl;
                            cout <<"Please try again! " << endl;
                        }
                        break;
                    }
                }
            }

        }
    }
}

int PaperManagement::countDiscussion()
{
    int recordCount = 0;
    ifstream infile;
    infile.open("System/PaperDiscussion.txt");
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

void PaperManagement::submitAuthorResponse()
{
    //this is for author of the papers

}

void PaperManagement::monitorPC()
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
    //read in the user

    int reviewNum = countPaper();
    PaperAssignment paperAssignment[reviewNum];

    infile.open("System/PaperAssignment.txt");
    for(int i = 0; i < reviewNum; i++)
    {
        infile >> paperAssignment[i];
    }
    infile.close();
    //read in the file that has paper assignments and the review;

    int preferenceNum = countPreference(); //preferences are only given by PCs
    Preference preference[preferenceNum];

    infile.open("System/Preference.txt");
    for(int i = 0; i < preferenceNum; i++)
    {
        infile >> preference[i];
    }
    infile.close();
    //preference of each users loaded

    int paperNum = countPaper();
    ResearchPaper researchPaper[paperNum];

    infile.open("System/Papers/Papers.txt");
    for(int i = 0; i < paperNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();
    //read in the papers

    vector<User> userList;
    //i should sieve out users who have the role of authors and put them into a vector
    for(int i = 0; i < recordNum; i++)
    {
        if (user[i].getType() != "A") //not author
        {
            userList.push_back(user[i]);
        }
    }
    //we have the list of users, excluding authors
    cout << "Monitor PCs! O.O" << endl << endl;
    int choice = 9;
    while(choice != 0)
    {
        cout << "What would you like to view? " << endl;
        cout << "1. Number of papers assigned to each Program Committee" << endl;
        cout << "2. Paper assigned to each PC" << endl;
        cout << "3. Paper which has been reviewed by each PC" << endl;
        cout << "4. Paper which has not been reviewed by each PC" << endl;
        cout << "5. Reviews on paper wrote by each PC" << endl;
        cout << "6. Preferences on each paper by each PC" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cout << "Displaying the number of papers assigned to each PC. . ." << endl;
                for(int i = 0; i < userList.size(); i++)
                {
                    cout << "Username: " << userList[i].getUsername() << endl;
                    cout << "Number of paper assigned: " << userList[i].getNumPaperAssigned() << endl;
                    cout << endl;
                }
                cout << endl;
            }
            break;
            case 2:
            {
                cout << "Displaying paper assigned to each PC" << endl;
                for(int i = 0; i < userList.size(); i++)
                {
                    cout << "Username: " << userList[i].getUsername() << endl;
                    cout << "Paper assigned: ";
                    vector<int> paperAssigned = userList[i].getPaperAssigned();
                    for(int k = 0; k < paperAssigned.size(); k++)
                    {
                        if (k == (paperAssigned.size() - 1)) //means its the last record, dont display the comma
                        {
                            cout << paperAssigned[k] << endl;
                        }
                        else
                        {
                            cout << paperAssigned[k] << ",";
                        }
                    }
                    cout << endl;
                }
            }
            break;
            case 3:
            {
                cout << "Displaying paper which has been reviewed by each PC. . ." << endl;
                for(int i = 0; i < userList.size(); i++)
                {
                    cout << "Username: >>>>>> " << userList[i].getUsername() << " <<<<<<" << endl;
                    //check through each user, find out which paper they have been assigned, then check if they reviewed it or not
                    for(int k = 0; k < reviewNum; k++) //number of papers
                    {
                        int numOfReviewers = paperAssignment[k].getNumAssignedForReview(); //what is the number of assigned users to this paper?
                        if (numOfReviewers != 0 ) //there are reviewers for the paper
                        {
                            vector<PaperReview*> userReviewed;
                            vector<string>reviewerList = paperAssignment[k].getUserList(); //get the list of users assigned this paper
                            if(find(reviewerList.begin(), reviewerList.end(), userList[i].getUsername()) != reviewerList.end()) //he is one of those assigned to this paper
                            {
                                //means the user has been assigned this paper
                                int numOfReviews = paperAssignment[k].getNumUserReviewed(); //number of reviews done on this paper
                                bool hasReviewed = false;

                                if(numOfReviews == 0) //if 0 no reviews have been done on this paper yet
                                {
                                    hasReviewed = false;
                                }
                                else if (numOfReviewers != 0) //there are reviews done on this paper, we need to know if the current user we checking
                                    //actually was one of them that reviewed it
                                {
                                    userReviewed = paperAssignment[k].getUserReview();
                                    for(int q = 0; q < numOfReviews && hasReviewed == false; q++)
                                    {
                                        if(userList[i].getUsername() == userReviewed[q]->getReviewedBy())
                                        {
                                            hasReviewed = true; //the user did indeed review this paper
                                        }
                                    }
                                }

                                if (hasReviewed)
                                {
                                    cout << "Paper reviewed: " << paperAssignment[k].getPaperID() << endl;
                                }
                            }
                        }
                    }
                    cout << endl;
                }
            }
            break;
            case 4:
            {
                cout << "Displaying paper which has not been reviewed by each PC. . ." << endl;
                for(int i = 0; i < userList.size(); i++)
                {
                    cout << "Username: >>>>>> " << userList[i].getUsername() << " <<<<<<" << endl;
                    //check through each user, find out which paper they have been assigned, then check if they reviewed it or not
                    for(int k = 0; k < reviewNum; k++) //number of papers
                    {
                        int numOfReviewers = paperAssignment[k].getNumAssignedForReview(); //what is the number of assigned users to this paper?
                        if (numOfReviewers != 0 ) //there are reviewers for the paper
                        {
                            vector<PaperReview*> userReviewed;
                            vector<string>reviewerList = paperAssignment[k].getUserList(); //get the list of users assigned this paper
                            if(find(reviewerList.begin(), reviewerList.end(), userList[i].getUsername()) != reviewerList.end()) //he is one of those assigned to this paper
                            {
                                //means the user has been assigned this paper
                                int numOfReviews = paperAssignment[k].getNumUserReviewed(); //number of reviews done on this paper
                                bool hasReviewed = false;

                                if(numOfReviews == 0) //if 0 no reviews have been done on this paper yet
                                {
                                    hasReviewed = false;
                                }
                                else if (numOfReviewers != 0) //there are reviews done on this paper, we need to know if the current user we checking
                                    //actually was one of them that reviewed it
                                {
                                    userReviewed = paperAssignment[k].getUserReview();
                                    for(int q = 0; q < numOfReviews && hasReviewed == false; q++)
                                    {
                                        if(userList[i].getUsername() == userReviewed[q]->getReviewedBy())
                                        {
                                            hasReviewed = true; //the user did indeed review this paper
                                        }
                                    }
                                }

                                if (!hasReviewed)
                                {
                                    cout << "Paper not reviewed: " << paperAssignment[k].getPaperID() << endl;
                                }
                            }
                        }
                    }
                    cout << endl;
                }
            }
            break;
            case 5:
            {
                cout << "Displaying reviews on paper wrote by each PC. . ." << endl;
                for(int i = 0; i < userList.size(); i++)
                {
                    cout << "Username: >>>>>> " << userList[i].getUsername() << " <<<<<<" << endl;
                    //check through each user, find out which paper they have been assigned, then check if they reviewed it or not
                    for(int k = 0; k < reviewNum; k++) //number of papers
                    {
                        int position = 0;
                        int numOfReviewers = paperAssignment[k].getNumAssignedForReview(); //what is the number of assigned users to this paper?
                        if (numOfReviewers != 0 ) //there are reviewers for the paper
                        {
                            vector<PaperReview*> userReviewed;
                            vector<string>reviewerList = paperAssignment[k].getUserList(); //get the list of users assigned this paper
                            if(find(reviewerList.begin(), reviewerList.end(), userList[i].getUsername()) != reviewerList.end()) //he is one of those assigned to this paper
                            {
                                //means the user has been assigned this paper
                                int numOfReviews = paperAssignment[k].getNumUserReviewed(); //number of reviews done on this paper
                                bool hasReviewed = false;

                                if(numOfReviews == 0) //if 0 no reviews have been done on this paper yet
                                {
                                    hasReviewed = false;
                                }
                                else if (numOfReviewers != 0) //there are reviews done on this paper, we need to know if the current user we checking
                                    //actually was one of them that reviewed it
                                {
                                    userReviewed = paperAssignment[k].getUserReview();
                                    for(int q = 0; q < numOfReviews && hasReviewed == false; q++)
                                    {
                                        if(userList[i].getUsername() == userReviewed[q]->getReviewedBy())
                                        {
                                            position = q;
                                            hasReviewed = true; //the user did indeed review this paper
                                        }
                                    }
                                }

                                if (hasReviewed)
                                {
                                    cout << "Paper reviewed: " << paperAssignment[k].getPaperID() << endl;
                                    cout << endl;
                                    cout << "Review: " << endl;
                                    userReviewed[position]->display();
                                    cout << endl;
                                }
                            }
                        }
                    }
                    cout << endl;
                }
            }
            break;
            case 6:
            {
                cout << "Displaying preferences on each paper by each PC" << endl;
                for(int i = 0; i < preferenceNum; i++) //based on the number of preferences, which is based on the number of users (EXCLUDING AUTHORS)
                {
                    cout << "Username: >>>>>> " << preference[i].getUsername() << " <<<<<<"  << endl;
                    vector<int> userPreference = preference[i].getAllPreference(); //got the list of ALL preferences of the user
                    cout << "Preferences on each paper:" << endl;
                    for(int k = 0; k < paperNum; k++) //based on the number of papers! DIFFERENT
                    {
                        researchPaper[k].display();
                        cout << "Preference for this paper: ";
                        if (userPreference[k] == 1) //yes
                        {
                            cout << "1. Yes" << endl;
                        }
                        else if(userPreference[k] == 2)
                        {
                            cout << "2. No" << endl;
                        }
                        else if (userPreference[k] == 3)
                        {
                            cout << "3. Maybe" << endl;
                        }
                        else if (userPreference[k] == 4)
                        {
                            cout << "4. Conflict of interest" << endl;
                        }
                        cout << endl;
                    }
                    cout << endl;
                }
            }
            break;
            case 0:
            {
                cout << "Exiting. . ." << endl;
            }
            break;
            default:
            {
                cout << "Invalid input" << endl;
                cout << "Please try again!" << endl;
            }
            break;
        }
    }
}

int PaperManagement::countPreference()
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


void PaperManagement::modifyReview(string currentlyLoggedIn)
{
    int reviewNum = countPaper();
    PaperAssignment paperAssignment [reviewNum];

    ifstream infile;
    infile.open("System/PaperAssignment.txt");

    for(int i = 0; i < reviewNum; i++)
    {
        infile >> paperAssignment[i];
    }

    infile.close();

    ResearchPaper researchPaper [reviewNum];

    infile.open("System/Papers/Papers.txt");

    for(int i = 0; i < reviewNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();
    //at this point we read in the file which contains the papers and their reviewers
    //and also details about the paper itself

    for(int i = 0; i < reviewNum; i++)
    {
        int numOfReviewers = paperAssignment[i].getNumAssignedForReview();
        if(numOfReviewers != 0) //there are reviewers for the paper
        {
            int choice = 0;
            int position = 0;
            vector<PaperReview*> userReviewed;
            vector<string> userList = paperAssignment[i].getUserList(); //get the list of users who reviewed the paper and start comparing them
            if(find(userList.begin(), userList.end(), currentlyLoggedIn) != userList.end())
            {
                int numOfReviews = paperAssignment[i].getNumUserReviewed(); //reviews that had already been done on this paper
                bool hasReviewed = false;
                if(numOfReviews == 0) //there are no reviews at all for the paper
                {
                    hasReviewed = false;
                }
                else if (numOfReviews != 0) //there are some reviews, we need to match the username to the review
                {
                    //list of user who has reviewed the paper
                    userReviewed = paperAssignment[i].getUserReview();
                    for(int q = 0; q < numOfReviews && hasReviewed == false; q++)
                    {
                        if (currentlyLoggedIn == userReviewed[q]->getReviewedBy())
                        {
                            //means he has already reviewed the paper
                            //if he has reviewed, then we can modify the review
                            hasReviewed = true;
                            position = q;
                        }
                    }
                }
                bool check = false;
                if(hasReviewed) //allow him to modify his review
                {
                    while(check == false)
                    {
                        cout << endl;
                        cout << "Do you wish to modify review for this paper?" << endl;
                        researchPaper[i].display();
                        cout << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No" << endl;
                        cout << "3. View the paper review" << endl; //allow the user to see the review that he has done
                        cout << "Choice: ";
                        cin >> choice;
                        switch(choice)
                        {
                            case 1:
                            {
                                cout << "Modifying review for this paper" << endl;
                                check = true;
                                userReviewed[position]->editReview();
                            }
                            break;
                            case 2:
                            {
                                cout << "Not modifying review for this paper" << endl;
                                check = true;
                            }
                            break;
                            case 3:
                            {
                                cout << "Displaying paper review done on this paper" << endl;
                                userReviewed[position]->display();
                            }
                            break;
                            default:
                            {
                                cout << "Invalid Input!" << endl;
                                check = false;
                            }
                        }
                    }
                }
                else
                {
                    researchPaper[i].display();
                    cout << "You have done no review for this paper!" << endl;
                }
            }
        }
    }
    writeAssignment(paperAssignment, reviewNum);
}


void PaperManagement::reviewPaper(string currentlyLoggedIn)
{
    int reviewNum = countPaper(); //we can assume the number of paers that are assigned is equal to the number of papers submitted
    PaperAssignment paperAssignment[reviewNum];

    //get the list of papers and their reviewers
    ifstream infile;
    infile.open("System/PaperAssignment.txt");

    for(int i = 0; i < reviewNum; i++)
    {
        infile >> paperAssignment[i];
    }

    infile.close();

    ResearchPaper researchPaper[reviewNum];

    infile.open("System/Papers/Papers.txt");

    for(int i = 0; i < reviewNum; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();
    //at this point we read in the file which contains the papers and their reviewers
    //and also details about the paper itself

    //find the paper that this user has been assigned with
    for(int i = 0; i < reviewNum; i++) //for each paper, look through each user assigned to that paper
    {
        int numOfReviewers = paperAssignment[i].getNumAssignedForReview();
        if(numOfReviewers != 0) //if there are reviewers assigned to this paper
        {
            int choice = 0;

            vector<string> userList = paperAssignment[i].getUserList(); //get the list of users who reviewed the paper and start comparing them
            if(find(userList.begin(), userList.end(), currentlyLoggedIn) != userList.end())
            {
                //you found the user name of the currently logged in among the list of users assigned for this paper
                //means the user is able to review this paper, we should also check if the user has already reviewed this paper
                int numOfReviews = paperAssignment[i].getNumUserReviewed(); //reviews that had already been done on this paper

                bool hasReviewed = false; //to allow review of paper or not
                if(numOfReviews == 0) //no users reviewed yet, then we can just review the paper
                {
                    hasReviewed = false;
                }
                //if there are users who have reviewed the paper, we need to check if the user currently logged in
                //has already reviewed this paper or not;
                //if he has move on to next paper or next menu
                else if (numOfReviews != 0)
                {
                    //list of user who has reviewed the paper
                    vector<PaperReview*> userReviewed = paperAssignment[i].getUserReview();
                    for(int q = 0; q < numOfReviews && hasReviewed == false; q++)
                    {
                        if (currentlyLoggedIn == userReviewed[q]->getReviewedBy())
                        {
                            //means he has already reviewed the paper
                            //dont allow him to review again
                            hasReviewed = true;
                        }
                    }
                }
                bool check = false;

                if (hasReviewed == false) //if he has not reviewed the paper yet
                {
                    while(check == false)
                    {
                        researchPaper[i].display();

                        cout << "Do you wish to review this paper? " << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No " << endl;
                        cout << "Choice: ";
                        cin >> choice;

                        switch(choice)
                        {
                            case 1:
                            {
                                reverseTransfer(researchPaper[i]);
                                cout << "Reviewing paper. . ." << endl;
                                check = true;
                                paperAssignment[i].addUserReview(makeReview(currentlyLoggedIn));
                                paperAssignment[i].addNumUserReviewed();
                            }
                            break;
                            case 2:
                            {
                                cout << "Not reviewing paper . . ." << endl;
                                check = true;
                            }
                            break;
                            default:
                            {
                                cout << "Invalid Input!" << endl;
                                check = false;
                            }
                        }
                    }
                //while loop ends here
                }
                else
                {
                    researchPaper[i].display();
                    cout << endl;
                    cout << "You have already reviewed this paper!" << endl;
                }
            }
        }
    }
    //update into file
    writeAssignment(paperAssignment, reviewNum);

}

void PaperManagement::writeAssignment(PaperAssignment* paperAssignment, int reviewNum)
{
    ofstream outfile;
    outfile.open("System/PaperAssignment.txt");

    for(int i = 0; i < reviewNum; i++)
    {
        outfile << paperAssignment[i];
    }

    outfile.close();
}

PaperReview* PaperManagement::makeReview(std::string currentlyLoggedIn)
{
    PaperReview * paperReview = new PaperReview;
    paperReview->setReviewedBy(currentlyLoggedIn);

    string tempString;
    cin.ignore();

    cout << "What are the strengths of the paper? " << endl;
    cout << "Strengths: ";
    getline(cin, tempString, '\n');
    paperReview->setStrengths(tempString);

    cout << "What are the weaknesses of the paper? " << endl;
    cout << "Weakness: ";
    getline(cin, tempString, '\n');
    paperReview->setWeakness(tempString);

    cout << "Ways to improve this paper? " << endl;
    cout << "Improvements: ";
    getline(cin, tempString, '\n');
    paperReview->setComments(tempString);

    cout << "Would this paper be suitable as a short paper? " << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "Suitability: ";
    getline(cin, tempString, '\n');
    paperReview->setSuitability(atoi(tempString.c_str()));

    cout << "Extra comments. . ." << endl;
    cout << "Reviewer remarks: ";
    getline(cin, tempString, '\n');
    paperReview->setPcRemarks(tempString);

    cout << "OVERALL EVALUATION: " << endl;
    cout << "3 (strong accept)" << endl;
    cout << "2 (accept)" << endl;
    cout << "1 (weak accept)" << endl;
    cout << "0 (borderline paper)" << endl;
    cout << "-1 (weak reject)" << endl;
    cout << "-2 (reject)" << endl;
    cout << "-3 (strong reject)" << endl;
    cout << "Overall evaluation: ";
    getline(cin, tempString, '\n');
    paperReview->setOverall(atoi(tempString.c_str()));

    cout << "REVIEWER'S CONFIDENCE: " << endl;
    cout << "4 (expert)" << endl;
    cout << "3 (high)" << endl;
    cout << "2 (medium)" << endl;
    cout << "1 (low)" << endl;
    cout << "0 (null)" << endl;
    cout << "Reviewer's confidence: ";
    getline(cin, tempString, '\n');
    paperReview->setReviewerConfidence(atoi(tempString.c_str()));

    cout << "RELEVANCE: from 1 (lowest) to 5 (highest) " << endl;
    cout << "5 (Highly Relevant) " << endl;
    cout << "4 (Very Relevant) " << endl;
    cout << "3 (Moderately Relevant) " << endl;
    cout << "2 (Marginally Relevant) " << endl;
    cout << "1 (Not Relevant)" << endl;
    cout << "Relevance: ";
    getline(cin, tempString, '\n');
    paperReview->setRelevance(atoi(tempString.c_str()));

    cout << "ORIGINALITY: from 1 (lowest) to 5 (highest) " << endl;
    cout << "5 (Highly Original) " << endl;
    cout << "4 (Very Original) " << endl;
    cout << "3 (Moderately Original) " << endl;
    cout << "2 (Little Originality) " << endl;
    cout << "1 (Not Original)" << endl;
    cout << "Originality: ";
    getline(cin, tempString, '\n');
    paperReview->setOriginality(atoi(tempString.c_str()));

    cout << "SIGNIFICANCE: from 1 (lowest) to 5 (highest) " << endl;
    cout << "5 (Highly Significant)" << endl;
    cout << "4 (Very Significant) " << endl;
    cout << "3 (Moderately Significant)" << endl;
    cout << "2 (Little Significance) " << endl;
    cout << "1 (Not Significant)" << endl;
    cout << "Significance: ";
    getline(cin, tempString, '\n');
    paperReview->setSignificance(atoi(tempString.c_str()));

    cout << "PRESENTATION: from 1 (lowest) to 5 (highest) " << endl;
    cout << "5 (Excellent)" << endl;
    cout << "4 (Well Written) " << endl;
    cout << "3 (Acceptable)" << endl;
    cout << "2 (Poor) " << endl;
    cout << "1 (Unreadable)" << endl;
    cout << "Presentation: ";
    getline(cin, tempString, '\n');
    paperReview->setPresentation(atoi(tempString.c_str()));

    cout << "TECHNICAL QUALITY: from 1 (lowest) to 5 (highest) " << endl;
    cout << "5 (Technically Sound)" << endl;
    cout << "4 (Seems Sound)" << endl;
    cout << "3 (Minor Flaws)" << endl;
    cout << "2 (Major Flaws) " << endl;
    cout << "1 (Unsound)" << endl;
    cout << "Technical Quality: ";
    getline(cin, tempString, '\n');
    paperReview->setTechnicalQuality(atoi(tempString.c_str()));

    cout << "EVALUATION: from 1 (lowest) to 5 (highest) " << endl;
    cout << "5 (Thorough Evaluation)" << endl;
    cout << "4 (Strong Evaluation)" << endl;
    cout << "3 (Sound Evaluation)" << endl;
    cout << "2 (Weak Evaluation) " << endl;
    cout << "1 (No Evaluation)" << endl;
    cout << "Evaluation:  ";
    getline(cin, tempString, '\n');
    paperReview->setEvaluation(atoi(tempString.c_str()));

    return paperReview;
}


void PaperManagement::modifyPaperSubmission(string currentLoggedInUser)
{
    int recordNum = countUser();
    User user[recordNum];

    //access the user text to get the user class and do comparison
    ifstream infile;
    infile.open("System/UserList.txt");
    for(int i = 0; i < recordNum; i++)
    {
        infile >> user[i];
    }
    infile.close();

    bool check = false;
    int position = 0;
    //now save the position where it matches
    for(int i = 0; i < recordNum && check == false; i++)
    {
        if (currentLoggedInUser == user[i].getUsername())
        {
            position = i;
            check = true;
        }
    }
    //at this point we have the all the details of the user currently logged in

    int numOfPapers = countPaper();
    ResearchPaper researchPaper[numOfPapers];

    infile.open("System/Papers/Papers.txt");

    for(int i = 0; i < numOfPapers; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();

    //at this point all paper has been read in
    bool hasPaper = false; //to check if the user has any paper submitted at all
    int choice, modifyChoice;
    //if this function returns true, the user has submitted this paper, display to him what paper he has submitted
    for(int i = 0; i < numOfPapers; i++)
    {
        //display the paper that he has submitted
        if(researchPaper[i].checkEmail(user[position].getEmail()))
        {
            researchPaper[i].display();
            hasPaper = true;
            //error checking
            check = false;

            while (check != true)
            {
                cout << "Do you want to modify this paper?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Choice: ";
                cin >> choice;

                if(choice != 1 && choice != 2)
                {
                    check = false;
                    cout << "Invalid Choice!" << endl;
                    cout << "Please try again!" << endl;
                    cout << endl;
                }

                else
                {
                    check = true;
                }
            }
            //user made decision
            //1 means yes, to modify the paper
            if (choice == 1)
            {
                cout << endl;
                cout << "What do you wish to modify?" << endl;
                cout << "1. Modify the title" << endl;
                cout << "2. Modify the abstract" << endl;
                cout << "3. Modify the keywords" << endl;
                cout << "4. Resubmit the paper" << endl;
                cout << "Choice: " ;
                cin >> modifyChoice;

                string tempString;
                switch (modifyChoice)
                {
                    case 1:
                    {
                        cin.ignore();
                        cout << "Please input the new title: ";
                        getline(cin, tempString, '\n');
                        researchPaper[i].setTitle(tempString);
                    }
                    break;
                    case 2:
                    {
                        cin.ignore();
                        cout << "Please input the new abstract: ";
                        getline(cin, tempString, '\n');
                        researchPaper[i].setAbstract(tempString);
                    }
                    break;
                    case 3:
                    {
                        cin.ignore();
                        cout << ">>> TO ENTER KEYWORDS FOR THE PAPER, PLEASE SEPERATE EACH KEYWORD BY '.' <<<" << endl;
                        cout << "Please input the new keywords: ";
                        getline(cin, tempString, '\n');
                        researchPaper[i].setKeywords(tempString);
                    }
                    break;
                    case 4:
                    {
                        transferFile(researchPaper[i]);
                    }
                    break;
                    default:
                    {
                        cout << "Invalid choice." << endl;
                    }
                }
            }
            writeAll(researchPaper, numOfPapers); //writing it into file after editing
        }
    }
    if(hasPaper == false)
    {
        cout << "You have not submitted any paper!" << endl;
    }


    cout << endl;
    cout << "Going back to the menu. . ." << endl;
}

void PaperManagement::writeAll(ResearchPaper researchPaper[], int numOfPapers)
{
    ofstream outfile;
    outfile.open("System/Papers/Papers.txt");

    for(int i = 0; i < numOfPapers; i++)
    {
        outfile << researchPaper[i];
    }

    outfile.close();
}

int PaperManagement::countUser()
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


void PaperManagement::submitPaper()
{
    ResearchPaper researchPaper;
    string tempString;
    int choice = 0;
    int userContributed = 0; //number of users who contributed

    researchPaper.setPaperID(generateID());

    //enter details about authors
    cout << "Please enter author details. . ." << endl << endl;
    while (choice != 2)
    {
        cin.ignore();
        //UNI FIRST THEN EMAIL
        string tempString;
        cout << "Please enter your first name: ";
        getline(cin, tempString, '\n');
        researchPaper.setContributedFirst(tempString);

        cout << "Please enter your last name: ";
        getline(cin, tempString, '\n');
        researchPaper.setContributedLast(tempString);

        cout << "Please enter your university: ";
        getline(cin, tempString, '\n');
        researchPaper.setContributedUni(tempString);

        cout << "Please enter your email: ";
        getline(cin, tempString, '\n');
        researchPaper.setContributedEmail(tempString);

        userContributed++;

        bool check = false;

        while (check != true)
        {
            cout << "Are there anymore authors who contributed to the paper?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choice: ";
            cin >> choice;

            if(choice != 1 && choice != 2)
            {
                check = false;
                cout << "Invalid Choice!" << endl;
                cout << "Please try again!" << endl;
                cout << endl;
            }

            else
            {
                check = true;
            }

        }
    }
    researchPaper.setNumContributors(userContributed);
    cin.ignore();
    //enter details about paper
    cout << endl;
    cout << "Please enter details about paper.  . ." << endl;

    cout << "Please enter the title of the paper: ";
    getline(cin, tempString, '\n');
    researchPaper.setTitle(tempString);

    cout << "Please enter the abstract of the paper: ";
    getline(cin, tempString, '\n');
    researchPaper.setAbstract(tempString);

    cout << ">>> TO ENTER KEYWORDS FOR THE PAPER, PLEASE SEPERATE EACH KEYWORD BY '.' <<<" << endl;
    cout << "Please enter the keywords for the paper: ";
    getline(cin, tempString, '\n');
    researchPaper.setKeywords(tempString);



    //enter the file directory now
    transferFile(researchPaper);

    writeFile(researchPaper);
    cout << "You have successfully submitted a paper! " << endl << endl;
}

void PaperManagement::reverseTransfer(ResearchPaper researchPaper)
{
    string fileName;

    DIR *dir = opendir(".");
    if(dir)
    {
        struct direct *ent;
    }

    else
    {
        cout << "Error opening directory" << endl;
    }

    string fileDir = ExePath(); //path that im going to copy to this time


    int ID = researchPaper.getPaperID();
    //this will give me the user pdf file with my own generated ID
    stringstream ss;
    ss << ID;
    string toTransferFrom = "System/Papers/" + ss.str() + ".pdf";
    fileName = researchPaper.getTitle() + ".pdf";

    fileDir = fileDir + "\\" + fileName;

    ifstream fin;
    fin.open(toTransferFrom.c_str(), ios::binary);
    if(!fin.good())
    {
        cout << "File does not exist" << endl;
    }
    else
    {
        ofstream fout;
        fout.open(fileDir.c_str(), ios::binary);

        while (!fin.eof())
        {
            char buf[1000];
            fin.read(buf, sizeof(buf));
            fout.write(buf, sizeof(buf));
        }
        fout.close();

    }
    fin.close();
    cout << "Paper has been transferrred to " << fileDir << endl;
}

void PaperManagement::transferFile(ResearchPaper researchPaper)
{
    string fileName;

    DIR *dir = opendir(".");
    if(dir)
    {
        struct direct *ent;
    }

    else
    {
        cout << "Error opening directory" << endl;
    }
    string fileDir = ExePath();
    cout << "Please drop the file into ( " << fileDir << " )" << endl;
    cout << "Enter the file name including the extension (####.pdf)" << endl;
    cout << "File name: ";
    cin >> fileName;

    int ID = researchPaper.getPaperID();
    //this will give me the user pdf file with my own generated ID
    stringstream ss;
    ss << ID;
    string toTransferTo = "System/Papers/" + ss.str() + ".pdf";

    fileDir = fileDir + "/" + fileName;

    ifstream fin;
    fin.open(fileDir.c_str(), ios::binary);
    if(!fin.good())
    {
        cout << "File does not exist" << endl;
    }
    else
    {
        ofstream fout;
        fout.open(toTransferTo.c_str(), ios::binary);

        while (!fin.eof())
        {
            char buf[1000];
            fin.read(buf, sizeof(buf));
            fout.write(buf, sizeof(buf));
        }
        fout.close();

    }
    fin.close();


}

void PaperManagement::writeFile(const ResearchPaper& researchPaper)
{
    ofstream outfile;
    outfile.open("System/Papers/Papers.txt", ios::app);

    outfile << researchPaper;

    outfile.close();
}

int PaperManagement::generateID()
{
    int recordNum = countPaper();

    //there are no paper records yet, so just generate with 1000
    if (recordNum == 0)
    {
        return 1000;
    }
    ifstream infile;
    infile.open("System/Papers/Papers.txt");

    //read every record in
    ResearchPaper * researchPaper;
    researchPaper = new ResearchPaper[recordNum];

    for (int i = 0; i < recordNum; i++)
    {
        infile >> researchPaper[i];
    }

    //find the last record, get the ID , add it by 1
    int ID = (researchPaper[recordNum - 1].getPaperID()) + 1;

    infile.close();
    return ID;
}

int PaperManagement::countPaper()
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
