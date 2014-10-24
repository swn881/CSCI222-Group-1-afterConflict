#include "Author.h"
#include <iostream>

using namespace std;

void Author::addPaper(int paperID)
{
    //save the id of the paper assigned
    paperAssigned.push_back(paperID);
}
