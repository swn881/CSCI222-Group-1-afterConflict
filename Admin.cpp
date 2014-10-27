#include <fstream>
#include <iostream>
#include "Admin.h"
#include "User.h"
#include "Conference.h"

using namespace std;

void Admin::assignPCChair()
{
    User * user;
    int recordNum = count();
    user = new User[recordNum];
    loadFile(user, recordNum);

    int choice = 2;
    bool check = false;
    cout << endl;
    cout << "Authors who can be assigned the role PC Chair: " << endl;

    for(int i = 0; i < recordNum; i++)
    {
        if(user[i].getType() != "PCChair" && user[i].getType() != "Admin") //as long they are not admin or PCChair i can assign them as PC Chair
        {
            cout << ">>>> USers <<<< " << endl;
            user[i].display();

            cout << endl;
            cout << "Do you want to assign this user as a PC Chair?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choice: ";
            cin >> choice;
            check = true;
            if(choice == 1)
            {
                user[i].setType("PCChair");
                cout << endl << "User has been assigned the role of PC!" << endl;

                writeFile(user, recordNum);
            }
        }
    }
    if (check == false)
    {
        cout << endl;
        cout << ">> There are currently no records in the system! << " << endl;
    }


    cout << endl;
    cout << ">>> Going back to menu. . . <<<" << endl;

}

void Admin::generateConference()
{
    Conference newConf;
    string tempString;
    cin.ignore();
    cout << "Generating new conference. . ." << endl;
    cout << "Please input as stated." << endl;
    cout << "Name of the conference: ";
    getline(cin, tempString, '\n');
    newConf.setConferenceName(tempString);

    cout << "Location of the conference: ";
    getline(cin, tempString, '\n');
    newConf.setLocation(tempString);

    ofstream outfile;
    outfile.open("System/Conference.txt", ios::app);
    outfile << newConf;
    outfile.close();
}
