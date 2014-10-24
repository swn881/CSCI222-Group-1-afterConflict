#include <iostream>
#include <windows.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include "PaperManagement.h"
#include "ResearchPaper.h"
#include "User.h"

using namespace std;

//To get the path of the folder...
string ExePath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of("\\/");
    return string(buffer).substr(0, pos);
}

void PaperManagement::modifyPaperSubmission(string currentLoggedInUser)
{
    int recordNum = countUser();
    User user[recordNum];

    //access the user text to get the user class and do comparison
    ifstream infile;
    infile.open("System/UserList.txt");
    for(int i = 0; i < recordNum; i++)
    {
        infile >> user[i];
    }
    infile.close();

    bool check = false;
    int position = 0;
    //now save the position where it matches
    for(int i = 0; i < recordNum && check == false; i++)
    {
        if (currentLoggedInUser == user[i].getUsername())
        {
            position = i;
            check = true;
        }
    }
    //at this point we have the all the details of the user currently logged in

    int numOfPapers = countPaper();
    ResearchPaper researchPaper[numOfPapers];

    infile.open("System/Papers/Papers.txt");

    for(int i = 0; i < numOfPapers; i++)
    {
        infile >> researchPaper[i];
    }
    infile.close();

    //at this point all paper has been read in
    bool hasPaper = false; //to check if the user has any paper submitted at all
    int choice, modifyChoice;
    //if this function returns true, the user has submitted this paper, display to him what paper he has submitted
    for(int i = 0; i < numOfPapers; i++)
    {
        //display the paper that he has submitted
        if(researchPaper[i].checkEmail(user[position].getEmail()))
        {
            researchPaper[i].display();
            hasPaper = true;
            //error checking
            check = false;

            while (check != true)
            {
                cout << "Do you want to modify this paper?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Choice: ";
                cin >> choice;

                if(choice != 1 && choice != 2)
                {
                    check = false;
                    cout << "Invalid Choice!" << endl;
                    cout << "Please try again!" << endl;
                    cout << endl;
                }

                else
                {
                    check = true;
                }
            }
            //user made decision
            //1 means yes, to modify the paper
            if (choice == 1)
            {
                cout << endl;
                cout << "What do you wish to modify?" << endl;
                cout << "1. Modify the title" << endl;
                cout << "2. Modify the abstract" << endl;
                cout << "3. Modify the keywords" << endl;
                cout << "4. Resubmit the paper" << endl;
                cout << "Choice: " << endl;
                cin >> modifyChoice;

                string tempString;
                switch (modifyChoice)
                {
                    case 1:
                    {
                        cout << "Please input the new title: ";
                        cin >> tempString;
                        researchPaper[i].setTitle(tempString);
                    }
                    break;
                    case 2:
                    {
                        cout << "Please input the new abstract: ";
                        cin >> tempString;
                        researchPaper[i].setAbstract(tempString);
                    }
                    break;
                    case 3:
                    {
                        cout << ">>> TO ENTER KEYWORDS FOR THE PAPER, PLEASE SEPERATE EACH KEYWORD BY '.' <<<" << endl;
                        cout << "Please input the new keywords: ";
                        cin >> tempString;
                        researchPaper[i].setKeywords(tempString);
                    }
                    break;
                    case 4:
                    {
                        transferFile(researchPaper[i]);
                    }
                    break;
                    default:
                    {
                        cout << "Invalid choice." << endl;
                    }
                }
            }
        }
    }
    if(hasPaper == false)
    {
        cout << "You have not submitted any paper!" << endl;
    }


    cout << endl;
    cout << "Going back to the menu. . ." << endl;
}

int PaperManagement::countUser()
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


void PaperManagement::submitPaper()
{
    ResearchPaper researchPaper;
    string tempString;
    int choice = 0;
    int userContributed = 0; //number of users who contributed

    researchPaper.setPaperID(generateID());

    //enter details about authors
    cout << "Please enter author details. . ." << endl << endl;
    while (choice != 2)
    {
        //UNI FIRST THEN EMAIL
        cout << "Please enter your first name: ";
        cin >> tempString;
        researchPaper.setContributedFirst(tempString);

        cout << "Please enter your last name: ";
        cin >> tempString;
        researchPaper.setContributedLast(tempString);

        cout << "Please enter your university: ";
        cin >> tempString;
        researchPaper.setContributedUni(tempString);

        cout << "Please enter your email: ";
        cin >> tempString;
        researchPaper.setContributedEmail(tempString);

        userContributed++;

        bool check = false;

        while (check != true)
        {
            cout << "Are there anymore authors who contributed to the paper?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choice: ";
            cin >> choice;

            if(choice != 1 && choice != 2)
            {
                check = false;
                cout << "Invalid Choice!" << endl;
                cout << "Please try again!" << endl;
                cout << endl;
            }

            else
            {
                check = true;
            }

        }
    }
    researchPaper.setNumContributors(userContributed);

    //enter details about paper
    cout << endl;
    cout << "Please enter details about paper.  . ." << endl;

    cout << "Please enter the title of the paper: ";
    cin >> tempString;
    researchPaper.setTitle(tempString);

    cout << "Please enter the abstract of the paper: ";
    cin >> tempString;
    researchPaper.setAbstract(tempString);

    cout << ">>> TO ENTER KEYWORDS FOR THE PAPER, PLEASE SEPERATE EACH KEYWORD BY '.' <<<" << endl;
    cout << "Please enter the keywords for the paper: ";
    cin >> tempString;
    researchPaper.setKeywords(tempString);

    writeFile(researchPaper);

    //enter the file directory now
    transferFile(researchPaper);

}

void PaperManagement::transferFile(ResearchPaper researchPaper)
{
    string fileName;

    DIR *dir = opendir(".");
    if(dir)
    {
        struct direct *ent;
    }

    else
    {
        cout << "Error opening directory" << endl;
    }
    string fileDir = ExePath();
    cout << "Please drop the file into ( " << fileDir << " )" << endl;
    cout << "Enter the file name including the extension (####.pdf)" << endl;
    cout << "File name: ";
    cin >> fileName;

    int ID = researchPaper.getPaperID();
    //this will give me the user pdf file with my own generated ID
    stringstream ss;
    ss << ID;
    string toTransferTo = "System/Papers/" + ss.str() + ".pdf";

    fileDir = fileDir + "/" + fileName;

    ifstream fin;
    fin.open(fileDir.c_str(), ios::binary);
    if(!fin.good())
    {
        cout << "File does not exist" << endl;
    }
    else
    {
        ofstream fout;
        fout.open(toTransferTo.c_str(), ios::binary);

        while (!fin.eof())
        {
            char buf[1000];
            fin.read(buf, sizeof(buf));
            fout.write(buf, sizeof(buf));
        }
        fout.close();

    }
    fin.close();


}

void PaperManagement::writeFile(const ResearchPaper& researchPaper)
{
    ofstream outfile;
    outfile.open("System/Papers/Papers.txt", ios::app);

    outfile << researchPaper;

    outfile.close();
}

int PaperManagement::generateID()
{
    int recordNum = countPaper();

    //there are no paper records yet, so just generate with 1000
    if (recordNum == 0)
    {
        return 1000;
    }
    ifstream infile;
    infile.open("System/Papers/Papers.txt");

    //read every record in
    ResearchPaper * researchPaper;
    researchPaper = new ResearchPaper[recordNum];

    for (int i = 0; i < recordNum; i++)
    {
        infile >> researchPaper[i];
    }

    //find the last record, get the ID , add it by 1
    int ID = (researchPaper[recordNum - 1].getPaperID()) + 1;

    infile.close();
    return ID;
}

int PaperManagement::countPaper()
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
