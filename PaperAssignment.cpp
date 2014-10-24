#include <iostream>
#include <stdlib.h>
#include "PaperAssignment.h"

using namespace std;

istream& operator>>(istream& in, PaperAssignment& temp)
{
    string tempString;
    getline(in, temp.userName, ',');
    getline(in, tempString, ',');
    temp.numPaperAssigned = atoi(tempString.c_str());

    for(int i = 0; i < temp.numPaperAssigned; i++)
    {
        if (i == (temp.numPaperAssigned - 1))
        {
            getline(in, tempString, '\n');
            temp.paperAssigned.push_back(atoi(tempString.c_str()));
        }
        else
        {
            getline(in, tempString, ',');
            temp.paperAssigned.push_back(atoi(tempString.c_str()));
        }
    }
    return in;
}

ostream& operator<<(ostream& out, PaperAssignment& temp)
{
    out << temp.userName << ",";
    out << temp.numPaperAssigned << ",";
    for (int i = 0; i < temp.numPaperAssigned; i++)
    {
        if (i == (temp.numPaperAssigned - 1))
        {
            out << temp.paperAssigned[i] << endl;
        }
        else
        {
            out << temp.paperAssigned[i] << ",";
        }
    }
    return out;
}
