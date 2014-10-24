#include "PCChair.h"
#include <iostream>
#include <fstream>

using namespace std;

void PCChair::assignPC()
{
    User * user;
    int recordNum = count();
    user = new User[recordNum];
    loadFile(user, recordNum);

    int choice = 2;
    bool check = false;
    cout << endl;
    cout << "Authors who can be assigned the role PC: " << endl;

    for(int i = 0; i < recordNum; i++)
    {
        if(user[i].getType() == "A")
        {
            cout << ">>>> Authors <<<< " << endl;
            user[i].display();

            cout << endl;
            cout << "Do you want to assign this user as a PC?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choice: ";
            cin >> choice;
            check = true;
            if(choice == 1)
            {
                user[i].setType("PC");
                cout << endl << "User has been assigned the role of PC!" << endl;

                writeFile(user, recordNum);
            }
        }
    }
    if (check == false)
    {
        cout << endl;
        cout << ">> There are currently no Authors recorded in the system! << " << endl;
    }


    cout << endl;
    cout << ">>> Going back to menu. . . <<<" << endl;


}

void PCChair::loadFile(User* user, int recordNum)
{
    ifstream infile;
    infile.open("System/UserList.txt");


    for (int i = 0; i < recordNum; i++)
    {
        infile >> user[i];
    }
    infile.close();

}

void PCChair::monitorPC()
{
    User * user;
    int recordNum = count();
    user = new User[recordNum];
    loadFile(user, recordNum);

    int choice;
    bool check = false;
    cout << endl;
    cout << "Current Program Committees in the system" << endl;

    for(int i = 0; i < recordNum && choice == 2; i++)
    {
        if(user[i].getType() == "PC")
        {
            cout << ">>>> Program Committees <<<< " << endl;
            user[i].display();

            cout << endl;
            cout << "Do you want to view more details about this Program Committee?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choice: ";
            cin >> choice;
            check = true;
            if(choice == 1)
            {
                obtainMoreDetails(user[i]);
            }
        }
    }

    if(check == false)
    {
        cout << endl;
        cout << ">> There are no Program Committees recorded in the system! <<" << endl;
    }

    cout << endl;
    cout << ">> Going back to menu . . . <<" << endl;

}

void PCChair::obtainMoreDetails(User user)
{
    cout << user.getUsername();
}


int PCChair::count()
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

void PCChair::writeFile(User* user, int recordNum)
{
    ofstream outfile;
    outfile.open("System/UserList.txt");
    for(int i = 0; i < recordNum; i++)
    {
        outfile << user[i];
    }
    outfile.close();
}
