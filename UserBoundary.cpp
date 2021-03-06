#include <iostream>
#include <windows.h>
#include "UserBoundary.h"
#include <cstring>
#include <conio.h>
#include <fstream>

using namespace std;

UserBoundary::~UserBoundary()
{

}


void UserBoundary::registerUser()
{
    system("cls");
    string tempUN;
    string tempFN;
    string tempLN;
    string tempEmail;
    string tempUni;
    string tempExp;
    string tempPw;
    bool check = false;
    cout << "Please input as stated..." << endl << endl;

    //check if username exists
    while(check == false)
    {
        cin.ignore();
        cout << "There cannot be any spaces in your username." << endl;
        cout << "User name: ";
        getline(cin, tempUN, '\n');
        if (userControl.checkUN(tempUN))
        {
            check = false;
            cout << "\n>> You have entered an existing username or a username too short! <<" << endl;
            cout << ">> Please try again! <<" << endl;
        }
        else
        {
            check = true;
        }
    }
    check = false;
    cout << "First name: ";
    getline(cin, tempFN, '\n');
    cout << "Last name: ";
    getline(cin, tempLN, '\n');
    cout << "Email: ";
    getline(cin, tempEmail, '\n');
    cout << "University: ";
    getline(cin, tempUni, '\n');
    cout << "Expertise: ";
    getline(cin, tempExp, '\n');

    //Implementing password censor from user input

    while(check == false)
    {
        char c = ' ';
        bool checkpassword = false;
        system("cls");

        cout << "Please input as stated..." << endl << endl;
        cout << "User name: " << tempUN << endl;
        cout << "First name: " << tempFN << endl;
        cout << "Last name: " << tempLN << endl;
        cout << "Email: " << tempEmail << endl;
        cout << "University: " << tempUni << endl;
        cout << "Expertise: " << tempExp << endl;
        cout << "Password: ";

        do
        {
            c = ' ';
            c = getch();

            if(c == '\b')
            {
                tempPw = "";
                c = ' ';
                system("cls");
                cout << "Please input as stated..." << endl << endl;
                cout << "User name: " << tempUN << endl;
                cout << "First name: " << tempFN << endl;
                cout << "Last name: " << tempLN << endl;
                cout << "Email: " << tempEmail << endl;
                cout << "University: " << tempUni << endl;
                cout << "Expertise: " << tempExp << endl;
                cout << "Password: ";
            }

            else if(c != '\r')
            {
                tempPw+=c;
                cout << "*";
            }

            else if(c == '\r')
            {
                checkpassword = true;
            }

        }while(checkpassword != true);

        if(!userControl.checkPW(tempPw))
        {
            check = false;
            cout << "\n>> The password you have entered is not long enough or too long! <<" << endl;
            cout << ">> Please enter a longer password! << " << endl;
            system("pause");
            tempPw = "";
        }
        else
        {
            check = true;
        }
    }

    userControl.registerUser(tempUN, tempFN, tempLN, tempEmail, tempUni, tempExp, tempPw);

    //writing to events

    ofstream outfile;
    outfile.open("System/Events.txt", ios::app);

    outfile << tempUN << " registered a new account." << endl;

    outfile.close();
}

void UserBoundary::login(string& userID, string& userType)
{
    system("cls");
    bool loginCheck = false;
    string tempUN;
    string tempPw;

    //Implementing password censor from user input

    while (loginCheck == false)
    {
        char c = ' ';
        bool checkpassword = false;
        system("cls");

        cout << "Please key in your username and password. . ." << endl << endl;
        cout << "Username: ";
        cin >> tempUN;
        cout << "Password: ";

        do
        {
            c = ' ';
            c = getch();

            if(c == '\b')
            {
                tempPw = "";
                c = ' ';
                system("cls");

                cout << "Please key in your username and password. . ." << endl << endl;
                cout << "Username: " << tempUN << endl;
                cout << "Password: ";

            }

            else if(c != '\r')
            {
                tempPw+=c;
                cout << "*";
            }

            else if(c == '\r')
            {
                checkpassword = true;
            }

        }while(checkpassword != true);

        if(userControl.login(tempUN, tempPw, userType)) //login successful
        {
            loginCheck = true;
            cout << endl;
            cout << "Welcome " << tempUN << " to the system!" << endl;
            userID = tempUN;
        }
        else
        {
            loginCheck = false;
            cout << "\n>> Invalid username or password! <<" << endl;
            cout << ">> Please try again! <<" << endl;
            system("pause");
            tempPw = "";
            tempUN = "";
        }
    }
}

void UserBoundary::changePassword(std::string tempUsername)
{
    //user must be logged in to change password;
    bool loginCheck = false;
    string tempPassword;
    string userType;


    if (tempUsername == "")
    {
        cout << "No users are currently logged in" << endl;
        system("pause");
    }

    else
    {
        //Implementing password censor from user input
        system("cls");

        while (loginCheck == false)
        {
            char c = ' ';
            bool checkpassword = false;
            system("cls");

            cout << "For security reasons, " << tempUsername << " please input your password again!" << endl;
            cout << "Password: ";

            do
            {
                c = ' ';
                c = getch();

                if(c == '\b')
                {
                    tempPassword = "";
                    c = ' ';
                    system("cls");

                    cout << "For security reasons, " << tempUsername << " please input your password again!" << endl;
                    cout << "Password: ";

                }

                else if(c != '\r')
                {
                    tempPassword+=c;
                    cout << "*";
                }

                else if(c == '\r')
                {
                    checkpassword = true;
                }

            }while(checkpassword != true);


            if(userControl.login(tempUsername, tempPassword, userType)) //login successful
            {
                string newPassword;
                loginCheck = true;
                bool passwordCheck = false;

                //Implementing password censor from user input

                while (passwordCheck == false)
                {
                    char c = ' ';
                    bool checkpassword = false;
                    system("cls");

                    cout << "Please enter your new password! " << endl;
                    cout << "Password: ";

                    do
                    {
                        c = ' ';
                        c = getch();

                        if(c == '\b')
                        {
                            newPassword = "";
                            c = ' ';
                            system("cls");

                            cout << "Please enter your new password! " << endl;
                            cout << "Password: ";

                        }

                        else if(c != '\r')
                        {
                            newPassword+=c;
                            cout << "*";
                        }

                        else if(c == '\r')
                        {
                            checkpassword = true;
                        }

                    }while(checkpassword != true);

                    if (newPassword == tempPassword)
                    {
                        passwordCheck = false;
                        cout << "Your new password cannot be similar to your old password!" << endl;
                        cout << ">> Please try again! <<" << endl;
                    }

                    else if (!userControl.checkPW(newPassword))
                    {
                        passwordCheck = false;
                        cout << "\n>> The password you have entered is not long enough or too long! <<" << endl;
                        cout << ">> Please enter a longer password! << " << endl;
                        system("pause");
                        newPassword = "";
                    }

                    else
                    {
                        passwordCheck = true;
                    }
                }

                //change password function
                userControl.changePassword(tempUsername, tempPassword, newPassword);
            }

            else
            {
                loginCheck = false;
                cout << "\n>> Invalid username or password! <<" << endl;
                cout << ">> Please try again! <<" << endl;
                system("pause");
                tempPassword = "";
            }
        }
    }

    system("cls");
}

void UserBoundary::changeDetails(string currentLoggedIn)
{
    system("cls");

    if (currentLoggedIn == "")
    {
        cout << "No users are currently logged in" << endl;
    }
    else
    {
        cout << "Now currently modifying details for " << currentLoggedIn << endl;

        int choice = 9;
        while(choice != 0)
        {
            cout << "1. Update email" << endl;
            cout << "2. Update university" << endl;
            cout << "3. Update expertise" << endl;
            cout << "0. Quit updating" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    cin.ignore();
                    string tempEmail;
                    cout << "Updating email . . ." << endl;
                    cout << "\nPlease input your new email" << endl;
                    cout << "Email: " ;
                    getline(cin, tempEmail, '\n');
                    userControl.updateEmail(currentLoggedIn, tempEmail);
                    cout << "\nSuccessful!" << endl << endl;
                }
                break;
                case 2:
                {
                    cin.ignore();
                    string tempUniversity;
                    cout << "Updating university. . ." << endl;
                    cout << "\nPlease input your new university" << endl;
                    cout << "University: ";
                    getline(cin, tempUniversity, '\n');
                    userControl.updateUniversity(currentLoggedIn, tempUniversity);
                    cout << "\nSuccessful!" << endl << endl;
                }
                break;
                case 3:
                {
                    cin.ignore();
                    string tempExpertise;
                    cout << "Updating expertise. . ." << endl;
                    cout << "\nPlease input your new expertise" << endl;
                    cout << "Expertise: ";
                    getline(cin, tempExpertise, '\n');
                    userControl.updateExpertise(currentLoggedIn, tempExpertise);
                    cout << "\nSuccessful!" << endl << endl;
                }
                break;
                case 0:
                {
                    cout << "Going back to main menu. . ." << endl;
                }
                break;
                default:
                {
                    cout << "Option does not exist!" << endl;
                    cout << "Please try again!" << endl;
                }
            }
        }
    }

}
