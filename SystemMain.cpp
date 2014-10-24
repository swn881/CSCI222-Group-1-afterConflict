#include <iostream>
#include <windows.h>
#include "SystemMain.h"
#include "UserBoundary.h"
#include "Author.h"
#include "ProgramCommittee.h"
#include "PCChair.h"

using namespace std;

void SystemMain::mainPage()
{
    int choice = 0;
    UserBoundary userBoundary;

    while (choice != 9)
    {
        cout << "Welcome to the system" << endl;
        cout << ">>> Main Menu <<<" << endl;
        cout << "What would you like to do today?" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "9. Exit" << endl;
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

void SystemMain::PCChairPage()
{
    UserBoundary userBoundary;
    int choice;
    PCChair pcChair;
    while(choice != 9)
    {
        cout << "What do you wish to do?" << endl;
        cout << "1. Change password" << endl;
        cout << "2. Modify personal details" << endl;
        cout << "3. Submit paper. //not implemented" << endl;
        cout << "4. Modify paper submission // not implemented" << endl;
        cout << "5. Specify preference" << endl;
        cout << "6. Review paper" << endl;
        cout << "7. Discuss review" << endl;
        cout << "8. Assign Program Committee" << endl;
        cout << "9. Monitor PC" << endl;
        cout << "10. Check latest events" << endl;
        cout << "11. Auto-assign papers to reviewers" << endl;
        cout << "12. Auto-assign preferences to reviewer" << endl;
        cout << "13. Set the number of reviewers paper receive" << endl;
        cout << "14. Set the number of papers reviewers receive" << endl;
        cout << "15. Manually set the number of papers A reviewer receive" << endl;
        cout << "16. Generate conference proceeding" << endl;
        cout << "17. Group paper" << endl;
        cout << "18. Enable/Disable paper reviews" << endl;
        cout << "19. Approve papers" << endl;
        cout << "20. Enable/Disable user response to the reviews" << endl;
        cout << "21. Enable/Disable discussion among reviewers" <<  endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: //preferably to make it after user logged in
            {
                cout << "You have selected to change password" << endl;
                userBoundary.changePassword(currentLoggedInUser);

            }
            break;
            case 2: //preferably to amke it after user logged in
            {
                cout << "You have selected to modify details" << endl;
                userBoundary.changeDetails(currentLoggedInUser);
            }
            break;
            case 3:
            {
                cout << "You have selected to submit paper //not completed" << endl;

            }
            break;
            case 4:
            {
                cout << "You have selected to modify paper submission //not implemented" << endl;
            }
            break;
            case 5:
            {
                cout << "You have selected to assign program committee" << endl;
                pcChair.assignPC();
            }
            break;
            case 6:
            {
                cout << "You have selected to monitor the program committee //incomplete" << endl;
                pcChair.monitorPC();
            }
            break;
            case 9:
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

}

void SystemMain::authorPage()
{

}

void SystemMain::adminPage()
{

}
