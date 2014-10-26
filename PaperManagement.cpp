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

using namespace std;

//To get the path of the folder...
string ExePath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of("\\/");
    return string(buffer).substr(0, pos);
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
