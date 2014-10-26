#include <iostream>
#include <windows.h>
#include "SystemMain.h"
#include "UserBoundary.h"
#include "Author.h"
#include "ProgramCommittee.h"
#include "PCChair.h"
#include "Admin.h"

using namespace std;

void SystemMain::mainPage()
{
    int choice = 9;
    UserBoundary userBoundary;

    while (choice != 0)
    {
        cout << "Welcome to the system" << endl;
        cout << ">>> Main Menu <<<" << endl;
        cout << "What would you like to do today?" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "You have selected register!" << endl;
                userBoundary.registerUser();
            }
            break;
            case 2:
            {
                cout << "You have selected login!" << endl;
                userBoundary.login(currentLoggedInUser, userType);

                //once user logged in
                homePage();
            }
            break;
            case 9:
            {
                cout << "Thanks for using the system!" << endl;
            }
            break;
            default:
            {
                cout << "Invalid input! Please try again!" << endl;
            }
        }
        cout << endl;
    }
    system("pause");
    exit(1);
}

void SystemMain::homePage()
{
    //this function directs to the correct page for each user
    if(userType == "A")
    {
        authorPage();
    }
    else if (userType == "PC")
    {
        PCpage();
    }
    else if (userType == "PCChair")
    {
        PCChairPage();
    }
    else if (userType == "Admin")
    {
        adminPage();
    }

}

void SystemMain::authorPage()
{
    int choice;
    Author author;
    while(choice != 0)
    {
        cout << "What do you wish to do?" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Modify personal details" << endl;
        cout << "3. Submit paper." << endl;
        cout << "4. Modify paper submission" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: //preferably to make it after user logged in
            {
                cout << "You have selected to change password" << endl;
                author.changePassword(currentLoggedInUser);

            }
            break;
            case 2: //preferably to amke it after user logged in
            {
                cout << "You have selected to modify details" << endl;
                author.changeDetails(currentLoggedInUser);
            }
            break;
            case 3:
            {
                cout << "You have selected to submit paper" << endl;
                author.submitPaper();

            }
            break;
            case 4:
            {
                cout << "You have selected to modify paper submission" << endl;
                author.modifyPaperSubmission(currentLoggedInUser);
            }
            break;
            case 0:
            {
                cout << "Exiting . . ." << endl;
            }
            break;
            default:
            {
                cout << endl;
                cout << ">> Invalid input! << " << endl;
                cout << ">> Please try again! << " << endl;
            }
        }
    }
}

void SystemMain::PCpage()
{
    int choice = 9;
    ProgramCommittee programCommittee;
    while(choice != 0)
    {
        cout << "What do you wish to do?" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Modify personal details" << endl;
        cout << "3. Submit paper. " << endl;
        cout << "4. Modify paper submission" << endl;
        cout << "5. Specify preference" << endl;
        cout << "6. Review paper    //nope" << endl;
        cout << "7. Modify review   //nope" << endl;
        cout << "8. Discuss review  //nope" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: //preferably to make it after user logged in
            {
                cout << "You have selected to change password" << endl;
                programCommittee.changePassword(currentLoggedInUser);

            }
            break;
            case 2: //preferably to amke it after user logged in
            {
                cout << "You have selected to modify details" << endl;
                programCommittee.changeDetails(currentLoggedInUser);
            }
            break;
            case 3:
            {
                cout << "You have selected to submit paper" << endl;
                programCommittee.submitPaper();
            }
            break;
            case 4:
            {
                cout << "You have selected to modify paper submission" << endl;
                programCommittee.modifyPaperSubmission(currentLoggedInUser);
            }
            break;
            case 5:
            {
                cout << "You have selected to specify preference" << endl;
                programCommittee.specifyPreference(currentLoggedInUser);

            }
            break;
            case 6:
            {
                cout << "You have selected to review paper //NOT IMPLEMENTED" << endl;
                programCommittee.reviewPaper(currentLoggedInUser);

            }
            break;
            case 7:
            {
                cout << "You have selected to modify review//NOT IMPLEMENTED" << endl;

            }
            break;
            case 8:
            {
                cout << "You have selected to discuss review//NOT IMPLEMENTED" << endl;
            }
            break;
            case 0:
            {
                cout << "You have selected exit!" << endl;
            }
            break;
            default:
            {
                cout << endl;
                cout << ">> Invalid input! << " << endl;
                cout << ">> Please try again! << " << endl;
            }
        }
    }
}



void SystemMain::PCChairPage()
{
    int choice = 9;
    PCChair pcChair;
    while(choice != 0)
    {
        cout << "What do you wish to do?" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Modify personal details" << endl;
        cout << "3. Submit paper. " << endl;
        cout << "4. Modify paper submission" << endl;
        cout << "5. Specify preference" << endl;
        cout << "6. Review paper    //nope" << endl;
        cout << "7. Modify review   //nope" << endl;
        cout << "8. Discuss review  //nope" << endl;
        cout << "9. Assign Program Committee" << endl;
        cout << "10. Monitor PC  //nope" << endl;
        cout << "11. Check latest events    //nope" << endl;
        cout << "12. Functionalities management" << endl;
        cout << "13. Approve papers //nope" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: //preferably to make it after user logged in
            {
                cout << "You have selected to change password" << endl;
                pcChair.changePassword(currentLoggedInUser);

            }
            break;
            case 2: //preferably to amke it after user logged in
            {
                cout << "You have selected to modify details" << endl;
                pcChair.changeDetails(currentLoggedInUser);
            }
            break;
            case 3:
            {
                cout << "You have selected to submit paper" << endl;
                pcChair.submitPaper();
            }
            break;
            case 4:
            {
                cout << "You have selected to modify paper submission" << endl;
                pcChair.modifyPaperSubmission(currentLoggedInUser);
            }
            break;
            case 5:
            {
                cout << "You have selected to specify preference" << endl;
                pcChair.specifyPreference(currentLoggedInUser);

            }
            break;
            case 6:
            {
                cout << "You have selected to review paper //NOT IMPLEMENTED" << endl;
                pcChair.reviewPaper(currentLoggedInUser);

            }
            break;
            case 7:
            {
                cout << "You have selected to modify review//NOT IMPLEMENTED" << endl;

            }
            break;
            case 8:
            {
                cout << "You have selected to discuss review//NOT IMPLEMENTED" << endl;
            }
            break;
            case 9:
            {
                cout << "You have selected to assign program committee" << endl;
                pcChair.assignPC();
            }
            break;
            case 10:
            {
                cout << "You have selected to monitor the program committee //incomplete" << endl;
                pcChair.monitorPC();
            }
            break;
            case 11:
            {
                cout << "You have selected to check on the latest events //not implemented" << endl;
            }
            break;
            case 12:
            {
                cout << "You have selected to go to the functionalities management page //not implemented" << endl;
                pcChair.functionalityManagement();
            }
            break;
            case 13:
            {
                cout << "You have selected to approve/reject papers //not implemented" << endl;
            }
            break;
            case 0:
            {
                cout << "You have selected exit!" << endl;
            }
            break;
            default:
            {
                cout << endl;
                cout << ">> Invalid input! << " << endl;
                cout << ">> Please try again! << " << endl;
            }
        }
    }
}


void SystemMain::adminPage()
{
        int choice = 9;
    Admin admin;
    while(choice != 0)
    {
        cout << "What do you wish to do?" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Modify personal details" << endl;
        cout << "3. Submit paper. " << endl;
        cout << "4. Modify paper submission" << endl;
        cout << "5. Specify preference" << endl;
        cout << "6. Review paper    //nope" << endl;
        cout << "7. Discuss review  //nope" << endl;
        cout << "8. Assign Program Committee" << endl;
        cout << "9. Monitor PC  //nope" << endl;
        cout << "10. Check latest events    //nope" << endl;
        cout << "11. Functionalities management" << endl;
        cout << "12. Approve papers //nope" << endl;
        cout << "13. Assign PC Chairs   //nope" << endl;
        cout << "14. Generate Conference    //nope" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: //preferably to make it after user logged in
            {
                cout << "You have selected to change password" << endl;
                admin.changePassword(currentLoggedInUser);

            }
            break;
            case 2: //preferably to amke it after user logged in
            {
                cout << "You have selected to modify details" << endl;
                admin.changeDetails(currentLoggedInUser);
            }
            break;
            case 3:
            {
                cout << "You have selected to submit paper" << endl;
                admin.submitPaper();
            }
            break;
            case 4:
            {
                cout << "You have selected to modify paper submission" << endl;
                admin.modifyPaperSubmission(currentLoggedInUser);
            }
            break;
            case 5:
            {
                cout << "You have selected to specify preference" << endl;
                admin.specifyPreference(currentLoggedInUser);

            }
            break;
            case 6:
            {
                cout << "You have selected to review paper //NOT IMPLEMENTED" << endl;

            }
            break;
            case 7:
            {
                cout << "You have selected to discuss review//NOT IMPLEMENTED" << endl;

            }
            break;
            case 8:
            {
                cout << "You have selected to assign program committee" << endl;
                admin.assignPC();
            }
            break;
            case 9:
            {
                cout << "You have selected to monitor the program committee //incomplete" << endl;
                admin.monitorPC();
            }
            break;
            case 10:
            {
                cout << "You have selected to check on the latest events //not implemented" << endl;
            }
            break;
            case 11:
            {
                cout << "You have selected to go to the functionalities management page //not implemented" << endl;
                admin.functionalityManagement();
            }
            break;
            case 12:
            {
                cout << "You have selected to approve/reject papers //not implemented" << endl;
            }
            break;
            case 13:
            {
                cout << "Assign PC Chairs" << endl;

            }
            break;
            case 14:
            {
                cout << "Generate conference" << endl;
            }
            break;
            case 0:
            {
                cout << "You have selected exit!" << endl;
            }
            break;
            default:
            {
                cout << endl;
                cout << ">> Invalid input! << " << endl;
                cout << ">> Please try again! << " << endl;
            }
        }
    }
}
