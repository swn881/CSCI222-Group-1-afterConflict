#include <iostream>
#include <stdlib.h>
#include "Functionalities.h"

using namespace std;

std::ostream& operator<< (std::ostream& out, Functionalities& temp)
{
    out << temp.reviewDiscussion << "," << temp.reviewSubmission << ",";
    out << temp.authorResponse << "," << temp.paperSubmission << ",";
    out << temp.paperReviewerReceive << "," << temp.reviewerPaperReceive << endl;
    return out;
}

std::istream& operator>> (std::istream& in , Functionalities& temp)
{
    string tempString;
    getline(in, tempString, ',');
    temp.reviewDiscussion = atoi(tempString.c_str());
    getline(in, tempString, ',');
    temp.reviewSubmission = atoi(tempString.c_str());
    getline(in, tempString, ',');
    temp.authorResponse = atoi(tempString.c_str());
    getline(in, tempString, ',');
    temp.paperSubmission = atoi(tempString.c_str());
    getline(in, tempString, ',');
    temp.paperReviewerReceive = atoi(tempString.c_str());
    getline(in, tempString, '\n');
    temp.reviewerPaperReceive = atoi(tempString.c_str());
    return in;
}

void Functionalities::setReviewDiscussion()
{
    if (reviewDiscussion == -1)
    {
        reviewDiscussion = 1;
    }
    else
    {
        reviewDiscussion = -1;
    }
}

void Functionalities::setReviewSubmission()
{
    if (reviewSubmission == -1)
    {
        reviewSubmission = 1;
    }
    else
    {
        reviewSubmission = -1;
    }
}

void Functionalities::setAuthorResponse()
{
    if (authorResponse == -1)
    {
        authorResponse = 1;
    }
    else
    {
        authorResponse = -1;
    }
}

void Functionalities::setPaperSubmission()
{
    if (paperSubmission == -1)
    {
        paperSubmission = 1;
    }
    else
    {
        paperSubmission = -1;
    }
}

void Functionalities::setPaperReviewerReceive(int temp)
{
    paperReviewerReceive = temp;
}

void Functionalities::setReviewerPaperReceive(int temp)
{
    reviewerPaperReceive = temp;
}
