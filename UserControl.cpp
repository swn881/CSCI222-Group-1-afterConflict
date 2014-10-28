#include <iostream>
#include <fstream>
#include "UserControl.h"
#include "User.h"
#include <cstring>
#include "md5.h"

using namespace std;

UserControl::~UserControl()
{

}

void UserControl::registerUser(string tempUN, string tempFN, string tempLN, string tempEmail, string tempUni, string tempExp, string tempPw)
{
    ofstream outfile;
    outfile.open("System/UserList.txt", ios::app);

    if (!outfile.good())
    {
        cout << "Not found" << endl;
    }
    else
    {
        string encryptPassword;
        encryptPassword = md5(tempPw);

        User tempClass;
        tempClass.setAll(tempUN, tempFN, tempLN, tempEmail, tempUni, tempExp, encryptPassword); //remember to change tempPw
        tempClass.setType("A");
        outfile << tempClass;
        outfile.close();
    }
}

bool UserControl::login(string tempUN, string tempPw, string& userType)
{
    bool loginCheck = false;
    int numRecord = 0;
    string tempPassword;
    string tempUsername;
    ifstream infile;
    infile.open("System/UserList.txt");
    User tempClass;


    if (!infile.good())
    {
        return false;
    }
    else
    {
        numRecord = count();

        for(int i =0; i < numRecord && loginCheck == false; i++)
        {
            infile >> tempClass;
            tempUsername = tempClass.getUsername();
            tempPassword = tempClass.getPassword();

            if(tempUN == tempUsername)
            {
                if (md5(tempPw) == tempPassword)
                {
                    loginCheck = true;
                    userType = tempClass.getType();
                }
                else
                {
                    loginCheck = false;
                }
            }
            else
            {
                loginCheck = false;
            }

        }
    }
    return loginCheck;
}

bool UserControl::checkUN(string tempUN)
{
    //for user check
    ifstream infile;
    infile.open("System/UserList.txt");
    bool checkExist = false;

    if (tempUN.length() > 100 || tempUN.length() < 6)
    {
        checkExist = true;
    }

    if(!infile.good())
    {
        return checkExist;
    }
    else
    {
        string temp;
        while(!infile.eof() && checkExist == false)
        {
            infile.ignore(100, ',');
            getline(infile, temp, ',');
             if (tempUN == temp)
            {
                checkExist = true;
            }
            infile.ignore(100, '\n');

        }
    }
    infile.close();

    return checkExist;
}

bool UserControl::checkPW(string tempPW)
{
    bool checkLength = true;

    if (tempPW.length() < 6 || tempPW.length() > 100)
    {
        checkLength = false;
    }

    return checkLength;
}

void UserControl::changePassword(string tempUN , string tempPw , string newPassword )
{
    int recordNo = count();
    bool check = false;
    string tempUsername;
    string tempPassword;
    User userList [recordNo];
    ifstream infile;
    infile.open("System/UserList.txt");

    for (int i = 0; i < recordNo; i++)
    {
        infile >> userList[i];
    }
    infile.close();

    for(int i =0; i < recordNo && check == false ; i++)
    {
        tempUsername = userList[i].getUsername();
        tempPassword = userList[i].getPassword();

        if(tempUN == tempUsername)
        {
            if (md5(tempPw) == tempPassword)
            {
                check = true;
                userList[i].setPassword(md5(newPassword));
                cout << userList[i];
            }
            else
            {
                check = false;
            }
        }
        else
        {
            check = false;
        }

    }

    ofstream outfile;
    outfile.open("System/UserList.txt");

    for (int i =0; i < recordNo; i++)
    {
        outfile << userList[i];
    }
    outfile.close();
}

int UserControl::count()
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

void UserControl::updateEmail(string tempUN, string newEmail)
{
    int recordNo = count();
    ifstream infile;
    infile.open("System/UserList.txt");
    User userList [recordNo];

    for(int i = 0; i < recordNo; i++)
    {
        infile >> userList[i];
    }
    infile.close();

    bool found = false;
    for (int i = 0; i < recordNo && found == false; i++)
    {
        string tempUsername = userList[i].getUsername();
        if (tempUN == tempUsername)
        {
            userList[i].setEmail(newEmail);
            found = true;
        }
        else
        {
            found = false;
        }
    }

    ofstream outfile;
    outfile.open("System/UserList.txt");

    for (int i = 0; i < recordNo; i++)
    {
        outfile << userList[i];
    }

}


void UserControl::updateExpertise(string tempUN, string newExpertise)
{
    int recordNo = count();
    ifstream infile;
    infile.open("System/UserList.txt");
    User userList [recordNo];

    for(int i = 0; i < recordNo; i++)
    {
        infile >> userList[i];
    }
    infile.close();

    bool found = false;
    for (int i = 0; i < recordNo && found == false; i++)
    {
        string tempUsername = userList[i].getUsername();
        if (tempUN == tempUsername)
        {
            userList[i].setExpertise(newExpertise);
            found = true;
        }
        else
        {
            found = false;
        }
    }

    ofstream outfile;
    outfile.open("System/UserList.txt");

    for (int i = 0; i < recordNo; i++)
    {
        outfile << userList[i];
    }

}


void UserControl::updateUniversity(string tempUN, string newUniversity)
{
    int recordNo = count();
    ifstream infile;
    infile.open("System/UserList.txt");
    User userList [recordNo];

    for(int i = 0; i < recordNo; i++)
    {
        infile >> userList[i];
    }
    infile.close();

    bool found = false;
    for (int i = 0; i < recordNo && found == false; i++)
    {
        string tempUsername = userList[i].getUsername();
        if (tempUN == tempUsername)
        {
            userList[i].setUniversity(newUniversity);
            found = true;
        }
        else
        {
            found = false;
        }
    }

    ofstream outfile;
    outfile.open("System/UserList.txt");

    for (int i = 0; i < recordNo; i++)
    {
        outfile << userList[i];
    }

}
