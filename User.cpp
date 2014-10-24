#include "User.h"
#include <cstring>
#include <iostream>

using namespace std;

ostream& operator<< (ostream& out, const User& user)
{
    out << user.type << "," << user.userName << "," << user.firstName  << "," << user.lastName << "," << user.email << "," << user.university << "," << user.expertise << "," << user.password << endl;
    return out;
}

istream& operator>> (istream& in, User& user)
{
    getline(in, user.type, ',');
    getline(in, user.userName, ',');
    getline(in, user.firstName, ',');
    getline(in, user.lastName, ',');
    getline(in, user.email, ',');
    getline(in, user.university, ',');
    getline(in, user.expertise, ',');
    getline(in, user.password, '\n');
    return in;
}

User::~User()
{
    userName = "";
    firstName = "";
    lastName = "";
    email = "";
    university = "";
}

void User::display()
{
    cout << "First Name: " <<  firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Email: " << email << endl;
    cout << "University: " << university << endl;
    cout << "Expertise: " << expertise<< endl;
}


void User::setAll(string tempUN, string tempFN, string tempLN, string tempEmail, string tempUni, string tempExp, string tempPassword)
{
    userName = tempUN;
    firstName = tempFN;
    lastName = tempLN;
    email = tempEmail;
    university = tempUni;
    expertise = tempExp;
    password = tempPassword;
}

void User::setUserName (string tempUN)
{
    userName = tempUN;
}
void User::setFirstName(string tempFN)
{
    firstName = tempFN;
}
void User::setLastName (string tempLN)
{
    lastName = tempLN;
}
void User::setEmail (string tempEmail)
{
    email = tempEmail;
}
void User::setUniversity (string tempUni)
{
    university = tempUni;
}
void User::setExpertise (string tempExp)
{
    expertise = tempExp;
}

void User::setPassword (string tempPassword)
{
    password = tempPassword;
}

void User::setType(string tempType)
{
    type = tempType;
}

string User::getUsername()
{
    return userName;
}

string User::getPassword()
{
    return password;
}

string User::getType()
{
    return type;
}
