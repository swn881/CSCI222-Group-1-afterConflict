#include <iostream>
#include <stdlib.h>
#include <vector>
#include "PaperDiscussion.h"

using namespace std;

ostream& operator<<(ostream& out, PaperDiscussion& temp)
{
    out << temp.numReviewerResponse << ",";
    if (temp.numReviewerResponse != 0)
    {
        for (int i = 0; i < temp.numReviewerResponse; i++)
        {
            out << temp.reviewerDiscussion[i] << ",";
        }
    }
    out << temp.numUserResponse << ",";
    if (temp.numUserResponse != 0)
    {
        for(int i = 0; i < temp.numUserResponse; i++)
        {
            out << temp.userResponse[i] << ",";
        }
    }

    out << temp.paperID << endl;
}

istream& operator>>(istream& in, PaperDiscussion& temp)
{
    string tempString;
    getline(in, tempString, ',');
    temp.numReviewerResponse = atoi(tempString.c_str());

    if (temp.numReviewerResponse != 0)
    {
        for(int i = 0; i < temp.numReviewerResponse; i++)
        {
            getline(in, tempString, ',');
            temp.reviewerDiscussion.push_back(tempString);
        }
    }

    getline(in, tempString, ',');
    temp.numUserResponse = atoi(tempString.c_str());

    if (temp.numUserResponse != 0)
    {
        for(int i = 0; i < temp.numUserResponse; i++)
        {
            getline(in, tempString, ',');
            temp.userResponse.push_back(tempString);
        }
    }
    getline(in, tempString, '\n');
    temp.paperID = atoi(tempString.c_str());
}
