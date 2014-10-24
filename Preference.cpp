#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Preference.h"

using namespace std;

istream& operator >> (istream& in, Preference& temp)
{
    int paperNum = temp.countPaper();
    string tempString;

    getline(in, temp.userName, ',');
    for (int i = 0; i < paperNum; i++)
    {
        if (i == (paperNum - 1))
        {
            getline(in, tempString, '\n');
            temp.addPreference(atoi(tempString.c_str()));
        }
        else
        {
            getline(in, tempString, ',');
            temp.addPreference(atoi(tempString.c_str()));
        }
    }
    return in;
}

ostream& operator << (ostream& out, Preference& temp)
{
    out << temp.userName << ",";
    for (unsigned int i = 0; i < temp.preference.size(); i++)
    {
        if (i == (temp.preference.size() - 1)) //means its the last one
        {
            out << temp.preference[i] << endl;
        }
        else
        {
            out << temp.preference[i] << ",";
        }
    }
    return out;
}

void Preference::addPreference(int temp)
{
    preference.push_back(temp);
}

void Preference::setUsername(string temp)
{
    userName = temp;
}

string Preference::getUsername()
{
    return userName;
}

int Preference::countPaper()
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


