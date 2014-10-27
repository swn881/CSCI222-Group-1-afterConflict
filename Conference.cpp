#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Conference.h"

using namespace std;

istream& operator>> (istream& in, Conference &temp)
{
    string tempString;
    getline(in, temp.conferenceName, ',');

    getline(in, tempString, ',');
    temp.numUser = atoi(tempString.c_str());

    if (temp.numUser != 0)
    {
        for(int i = 0; i < temp.numUser; i++ )
        {
            getline(in, tempString, ',');
            temp.userList.push_back(tempString);
        }
    }
    getline(in, temp.location, '\n');
}

ostream& operator<< (ostream& out, Conference &temp)
{
    out << temp.conferenceName << ",";
    out << temp.numUser << ",";
    if (temp.numUser != 0)
    {
        for(int i = 0; i < temp.numUser; i++ )
        {
            out << temp.userList[i] << ",";
        }
    }
    out << temp.location << endl;
}
