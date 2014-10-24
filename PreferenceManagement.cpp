#include <iostream>
#include <fstream>
#include <algorithm>
#include "PreferenceManagement.h"
#include "Preference.h"
#include "ResearchPaper.h"

using namespace std;

void PrefManagement::specifyPreference(std::string currentlyLoggedInUser)
{
    Preference preference;
    preference.setUsername(currentlyLoggedInUser);
    //num of lines in the file represent the number of papers currently submitted
    int paperNum = countPaper();
    int choice;
    bool check = false;
    ResearchPaper researchPaper[paperNum];

    //the vector position would represent the position of the paper in the file (what line is it in), we can check rhe ID directly
    //assuming preference can only be done after paper submissions have been closed
    //must do checking to make sure that paper submissions have been closed
    for(int i = 0; i < paperNum; i++)
    {
        //checking is crucial
        while (check == false) //this checking is to make sure the user dont make wrong inputs, if he make wrong input in the middle, it'll mess up everything
        {
            researchPaper[i].display();

            cout << "What is your preference on this paper? Would you review this paper?" << endl;
            cout << "1. Yes " << endl;
            cout << "2. No" << endl;
            cout << "3. Maybe" << endl;
            cout << "4. Conflict of Interest" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    //push in preference for that paper
                    preference.addPreference(1);
                    check = true;
                }
                break;
                case 2:
                {
                    preference.addPreference(2);
                    check = true;
                }
                break;
                case 3:
                {
                    preference.addPreference(3);
                    check = true;
                }
                break;
                case 4:
                {
                    preference.addPreference(4);
                    check = true;
                }
                break;
                default:
                {
                    cout << "Invalid input!" << endl;
                    cout << "Please try again!" << endl << endl;
                    check = false;
                }
            }
        }
        check = false;
    }
    //at this point the user would had specified preference for all papers
    //before i write into the file i should check if the user has already specified preference before
    if(checkUser(currentlyLoggedInUser)) //if i get true means the user has already specified preference before, therefore i need to rewrite the preferene file
    {
        writeAll(preference);
    }
    else
    {
        //otherwise append to the end
        writeApp(preference);
    }
}

void PrefManagement::specifyMaybe(std::string userID)
{
    Preference preference;

    preference.setUsername(userID);

    int paperNum = countPaper();

    for(int i = 0; i < paperNum; i++)
    {
        preference.addPreference(3);
    }

    writeApp(preference);
}

bool PrefManagement::checkUser(std::string currentlyLoggedIn)
{
    vector<string> listOfUsers; //who have gave their preferece
    //get the list of preference first
    int preferenceNum = countPreference();

    Preference preference[preferenceNum];

    ifstream infile;
    infile.open("System/Preference.txt");
    for (int i = 0; i < preferenceNum; i++)
    {
        infile >> preference[i];
    }
    infile.close();

    //get the list of users who have submitted preference into a vector
    for(int i = 0; i < preferenceNum; i++)
    {
        listOfUsers.push_back(preference[i].getUsername());
    }

    //find the username inside the vector
    if(std::find(listOfUsers.begin(), listOfUsers.end(), currentlyLoggedIn) != listOfUsers.end()) //we found the username in the list of specified preference
    {
        //this means we need to rewrite the line, ie rewirte the whole file
        return true;
    }
    else
    {
        return false;
    }

}

void PrefManagement::writeApp(Preference preference)
{
    ofstream outfile;
    outfile.open("System/Preference.txt", ios::app);

    outfile << preference;

    outfile.close();
}

void PrefManagement::writeAll(Preference preference)
{
    int preferenceNum = countPreference();

    Preference listPreference[preferenceNum];

    ifstream infile;
    infile.open("System/Preference.txt");
    for(int i = 0; i < preferenceNum; i++)
    {
        infile >> listPreference[i];
    }
    infile.close();
    //at this point i got all the preferences already by every user and ready for rewriting

    ofstream outfile;
    outfile.open("System/Preference.txt");
    for(int i = 0; i < preferenceNum; i++)
    {
        if(listPreference[i].getUsername() == preference.getUsername())
        {
            //if they are equal, i need to update with the one the user just entered
            outfile << preference;
        }
        else
        {
            outfile << listPreference[i];
        }
    }
    outfile.close();
}

int PrefManagement::countUser()
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

int PrefManagement::countPreference()
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

int PrefManagement::countPaper()
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
