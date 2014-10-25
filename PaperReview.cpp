#include <iostream>
#include <stdlib.h>
#include "PaperReview.h"

using namespace std;

ostream& operator << (ostream& out, PaperReview& temp)
{
    //first add in the paper id and who reviewed it, then print all other details about the review
    out << temp.reviewedBy << ",";
    out << temp.strengths << "," << temp.weakness << ",";
    out << temp.comments << "," << temp.suitability << ",";
    out << temp.pcRemarks << "," << temp.overall << ",";
    out << temp.reviewerConfidence << "," << temp.relevance << ",";
    out << temp.originality << ",";
    out << temp.significance << "," << temp.presentation << ",",
    out << temp.technicalQuality << "," << temp.evaluation << ",";

    return out;
}


istream& operator >> (istream& in, PaperReview& temp)
{
    string tempString;

    getline(in, temp.reviewedBy, ',');
    getline(in, temp.strengths, ',');
    getline(in, temp.weakness, ',');
    getline(in, temp.comments, ',');

    getline(in, tempString, ',');
    temp.suitability = atoi(tempString.c_str());

    getline(in, temp.pcRemarks, ',');

    getline(in, tempString, ',');
    temp.overall = atoi(tempString.c_str());

    getline(in, tempString, ',');
    temp.reviewerConfidence = atoi(tempString.c_str());

    getline(in, tempString, ',');
    temp.relevance = atoi(tempString.c_str());

    getline(in, tempString, ',');
    temp.originality = atoi(tempString.c_str());

    getline(in, tempString, ',');
    temp.significance = atoi(tempString.c_str());

    getline(in, tempString, ',');
    temp.presentation = atoi(tempString.c_str());

    getline(in, tempString, ',');
    temp.technicalQuality = atoi(tempString.c_str());

    getline(in, tempString, ',');
    temp.evaluation = atoi(tempString.c_str());

    return in;
}
