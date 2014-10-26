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

void PaperReview::display()
{
    cout << "Strengths of the paper: " << strengths << endl;
    cout << "Weakness of the paper: " << weakness << endl;
    cout << "Comments on the paper: " << comments << endl;
    cout << "Suitability of the paper: ";
    if (suitability == 1)
    {
        cout << "Yes " << endl;
    }
    else
    {
        cout << "No " << endl;
    }
    cout << "PC remarks: " << pcRemarks << endl;
    cout << "Overall evaluation: ";
    switch (overall)
    {
        case 3:
        {
            cout << "3 (strong accept)"  << endl;
        }
        break;
        case 2:
        {
            cout << "2 (accept) " << endl;
        }
        break;
        case 1:
        {
            cout << "1 (weak accept)" << endl;
        }
        break;
        case 0:
        {
            cout << "0 (borderline paper)" << endl;
        }
        break;
        case -1:
        {
            cout << "-1 (weak reject)" << endl;
        }
        break;
        case -2:
        {
            cout << "-2 (reject)" << endl;
        }
        break;
        case -3:
        {
            cout << "-3 (strong reject)" << endl;
        }
        break;
    }

    cout << "Reviewer's Confidence: ";
    switch (reviewerConfidence)
    {
        case 4:
        {
            cout << "4 (expert)"  << endl;
        }
        break;
        case 3:
        {
            cout << "3 (high)" << endl;
        }
        break;
        case 2:
        {
            cout << "2 (medium)" << endl;
        }
        break;
        case 1:
        {
            cout << "1 (low)" << endl;
        }
        break;
        case 0:
        {
            cout << "0 (null)" << endl;
        }
        break;
    }

    cout << "Relevance: ";
    switch (relevance)
    {
        case 5:
        {
            cout << "5 (Highly Relevant) "  << endl;
        }
        break;
        case 4:
        {
            cout << "4 (Very Relevant)" << endl;
        }
        break;
        case 3:
        {
            cout << "3 (Moderately Relevant)" << endl;
        }
        break;
        case 2:
        {
            cout << "2 (Marginally Relevant)" << endl;
        }
        break;
        case 1:
        {
            cout << "1 (Not Relevant)" << endl;
        }
        break;
    }

    cout << "Originality: ";
    switch (originality)
    {
        case 5:
        {
            cout <<"5 (Highly Original) " << endl;
        }
        break;
        case 4:
        {
            cout <<"4 (Very Original) " << endl;
        }
        break;
        case 3:
        {
            cout << "3 (Moderately Original) "<< endl;
        }
        break;
        case 2:
        {
            cout << "2 (Little Originality) "<< endl;
        }
        break;
        case 1:
        {
            cout <<"1 (Not Original)"  << endl;
        }
        break;
    }

    cout << "Significance: ";
    switch (significance)
    {
        case 5:
        {
            cout << "5 (Highly Significant)"<< endl;
        }
        break;
        case 4:
        {
            cout <<"4 (Very Significant) " << endl;
        }
        break;
        case 3:
        {
            cout <<"3 (Moderately Significant)" << endl;
        }
        break;
        case 2:
        {
            cout << "2 (Little Significance) "<< endl;
        }
        break;
        case 1:
        {
            cout <<"1 (Not Significant)" << endl;
        }
        break;
    }

    cout << "Presentation: ";
    switch (presentation)
    {
        case 5:
        {
            cout << "5 (Excellent)"<< endl;
        }
        break;
        case 4:
        {
            cout << "4 (Well Written) "<< endl;
        }
        break;
        case 3:
        {
            cout <<"3 (Acceptable)" << endl;
        }
        break;
        case 2:
        {
            cout << "2 (Poor) " << endl;
        }
        break;
        case 1:
        {
            cout << "1 (Unreadable)"<< endl;
        }
        break;
    }

    cout << "Technical Quality: ";
    switch (technicalQuality)
    {
        case 5:
        {
            cout <<"5 (Technically Sound)"  << endl;
        }
        break;
        case 4:
        {
            cout << "4 (Seems Sound)" << endl;
        }
        break;
        case 3:
        {
            cout <<  "3 (Minor Flaws)"<< endl;
        }
        break;
        case 2:
        {
            cout <<"2 (Major Flaws) " << endl;
        }
        break;
        case 1:
        {
            cout << "1 (Unsound)"<< endl;
        }
        break;
    }
    cout << "Evaluation: ";
    switch (evaluation)
    {
        case 5:
        {
            cout <<  "5 (Thorough Evaluation)"<< endl;
        }
        break;
        case 4:
        {
            cout <<"4 (Strong Evaluation)" << endl;
        }
        break;
        case 3:
        {
            cout << "3 (Sound Evaluation)" << endl;
        }
        break;
        case 2:
        {
            cout << "2 (Weak Evaluation) "<< endl;
        }
        break;
        case 1:
        {
            cout << "1 (No Evaluation)"<< endl;
        }
        break;
    }
}

void PaperReview::editReview()
{
    int choice = 9;
    string tempString;
    while (choice != 0)
    {
        cout << "What do you wish to modify? " << endl;
        cout << "1. Strengths" << endl;
        cout << "2. Weakness" << endl;
        cout << "3. Improvements" << endl;
        cout << "4. Suitability" << endl;
        cout << "5. Extra comments" << endl;
        cout << "6. Overall Evaluation" << endl;
        cout << "7. Reviewer's confidence" << endl;
        cout << "8. Relevance" << endl;
        cout << "9. Originality" << endl;
        cout << "10. Significance" << endl;
        cout << "11. Presentation" << endl;
        cout << "12. Technical Quality" << endl;
        cout << "13. Evaluation" << endl;
        cout << "0. Quit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {

                cout << "What are the strengths of the paper? " << endl;
                cout << "Strengths: ";
                getline(cin, tempString, '\n');
                strengths = tempString;
            }
            break;
            case 2:
            {
                cin.ignore();
                cout << "What are the weaknesses of the paper? " << endl;
                cout << "Weakness: ";
                getline(cin, tempString, '\n');
                weakness = tempString;

            }
            break;
            case 3:
            {
                cin.ignore();
                cout << "Ways to improve this paper? " << endl;
                cout << "Improvements: ";
                getline(cin, tempString, '\n');
                comments = tempString;
            }
            break;
            case 4:
            {
                cout << "Would this paper be suitable as a short paper? " << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Suitability: ";
                cin >> suitability;
            }
            break;
            case 5:
            {
                cin.ignore();
                cout << "Extra comments. . ." << endl;
                cout << "Reviewer remarks: ";
                getline(cin, tempString, '\n');
                pcRemarks = tempString;
            }
            break;
            case 6:
            {
                cout << "OVERALL EVALUATION: " << endl;
                cout << "3 (strong accept)" << endl;
                cout << "2 (accept)" << endl;
                cout << "1 (weak accept)" << endl;
                cout << "0 (borderline paper)" << endl;
                cout << "-1 (weak reject)" << endl;
                cout << "-2 (reject)" << endl;
                cout << "-3 (strong reject)" << endl;
                cout << "Overall evaluation: ";
                cin >> overall;
            }
            break;
            case 7:
            {
                cout << "REVIEWER'S CONFIDENCE: " << endl;
                cout << "4 (expert)" << endl;
                cout << "3 (high)" << endl;
                cout << "2 (medium)" << endl;
                cout << "1 (low)" << endl;
                cout << "0 (null)" << endl;
                cout << "Reviewer's confidence: ";
                cin >> reviewerConfidence;
            }
            break;
            case 8:
            {
                cout << "RELEVANCE: from 1 (lowest) to 5 (highest) " << endl;
                cout << "5 (Highly Relevant) " << endl;
                cout << "4 (Very Relevant) " << endl;
                cout << "3 (Moderately Relevant) " << endl;
                cout << "2 (Marginally Relevant) " << endl;
                cout << "1 (Not Relevant)" << endl;
                cout << "Relevance: ";
                cin >> relevance;
            }
            break;
            case 9:
            {
                cout << "ORIGINALITY: from 1 (lowest) to 5 (highest) " << endl;
                cout << "5 (Highly Original) " << endl;
                cout << "4 (Very Original) " << endl;
                cout << "3 (Moderately Original) " << endl;
                cout << "2 (Little Originality) " << endl;
                cout << "1 (Not Original)" << endl;
                cout << "Originality: ";
                cin >> originality;
            }
            break;
            case 10:
            {
                cout << "SIGNIFICANCE: from 1 (lowest) to 5 (highest) " << endl;
                cout << "5 (Highly Significant)" << endl;
                cout << "4 (Very Significant) " << endl;
                cout << "3 (Moderately Significant)" << endl;
                cout << "2 (Little Significance) " << endl;
                cout << "1 (Not Significant)" << endl;
                cout << "Significance: ";
                cin >> significance;
            }
            break;
            case 11:
            {
                cout << "PRESENTATION: from 1 (lowest) to 5 (highest) " << endl;
                cout << "5 (Excellent)" << endl;
                cout << "4 (Well Written) " << endl;
                cout << "3 (Acceptable)" << endl;
                cout << "2 (Poor) " << endl;
                cout << "1 (Unreadable)" << endl;
                cout << "Presentation: ";
                cin >> presentation;
            }
            break;
            case 12:
            {
                cout << "TECHNICAL QUALITY: from 1 (lowest) to 5 (highest) " << endl;
                cout << "5 (Technically Sound)" << endl;
                cout << "4 (Seems Sound)" << endl;
                cout << "3 (Minor Flaws)" << endl;
                cout << "2 (Major Flaws) " << endl;
                cout << "1 (Unsound)" << endl;
                cout << "Technical Quality: ";
                cin >> technicalQuality;
            }
            break;
            case 13:
            {
                cout << "EVALUATION: from 1 (lowest) to 5 (highest) " << endl;
                cout << "5 (Thorough Evaluation)" << endl;
                cout << "4 (Strong Evaluation)" << endl;
                cout << "3 (Sound Evaluation)" << endl;
                cout << "2 (Weak Evaluation) " << endl;
                cout << "1 (No Evaluation)" << endl;
                cout << "Evaluation:  ";
                cin >> evaluation;
            }
            break;
            case 0:
            {
                cout << "Exiting" << endl;
            }
            break;
            default:
            {
                cout << "Invalid Input" << endl;
                cout << "Please try again!" << endl;
            }
            break;
        }
    }
}
