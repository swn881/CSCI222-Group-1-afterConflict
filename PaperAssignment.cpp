#include <iostream>
#include <stdlib.h>
#include "PaperAssignment.h"
#include "PaperReview.h"

using namespace std;

istream& operator>>(istream& in, PaperAssignment& temp)
{
    string tempString;

    getline(in, tempString, ',');
    temp.numAssignedForReview = atoi(tempString.c_str());

    if (temp.numAssignedForReview != 0)
    {
        for(int i = 0; i < temp.numAssignedForReview; i++)
        {
            getline(in, tempString, ',');
            temp.userList.push_back(tempString);
        }
    }

    getline(in, tempString, ',');
    temp.numUserReviewed = atoi(tempString.c_str());

    //this part is a bit tricky, cause we actually store the review by the user on the line next to this

    if (temp.numUserReviewed != 0)
    {
        for(int i = 0; i < temp.numUserReviewed; i++)
        {
            PaperReview * tempReview = new PaperReview;
            in >> *tempReview;
            temp.userReview.push_back(tempReview);
        }
    }
    //assuming everything worked correctly, at this point we will have all the users ID who has been assigned this paper
    //the users review if they have actually done it all in one lool

    //store the paper id at the last
    getline(in, tempString, '\n');
    temp.paperID = atoi(tempString.c_str());

    return in;
}

ostream& operator<<(ostream& out, PaperAssignment& temp)
{
    out << temp.numAssignedForReview <<  ",";

    if (temp.numAssignedForReview != 0)
    {
        for(int i = 0; i < temp.numAssignedForReview; i++)
        {
            out << temp.userList[i] << ",";
        }
    }

    out << temp.numUserReviewed << ",";

    if (temp.numUserReviewed != 0)
    {
        for(int i = 0; i < temp.numUserReviewed; i++)
        {
            out <<  *(temp.userReview[i]); //comma is given by the overloaded output in the paperReview class
        }
    }

    out << temp.paperID << endl;


    return out;
}
