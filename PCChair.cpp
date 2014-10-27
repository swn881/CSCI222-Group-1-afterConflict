#include "PCChair.h"
#include "FunctionalitiesManagement.h"
#include "PaperManagement.h"
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
    PaperManagement paperManagement;
    paperManagement.monitorPC();
}

void PCChair::functionalityManagement()
{
    FuncManagement funcManagement;
    funcManagement.menu();
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

void PCChair::latestEvents()
{
    ifstream infile;
    infile.open("System/Events.txt");

    while (!infile.eof())
    {
        string line = " ";
        getline(infile, line, '\n');
        if (!line.empty())
            cout << line << endl;
    }
    cout << endl;
    infile.close();
}

void PCChair::approvePaper(string currentlyLoggedIn)
{
    PaperManagement paperManagement;
    paperManagement.approvePaper(currentlyLoggedIn);
}
