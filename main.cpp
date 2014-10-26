#include <iostream>
#include "SystemMain.h"
#include "PaperManagement.h"

using namespace std;

int main()
{
    SystemMain systemMain;
    //systemMain.mainPage();

    PaperManagement paperManagement;
    //paperManagement.reviewPaper("Admin");
    paperManagement.makeReview("Admin");

    return 0;
}
