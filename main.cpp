#include <iostream>
#include "SystemMain.h"
#include "PaperManagement.h"

using namespace std;

int main()
{
    SystemMain systemMain;
    //systemMain.mainPage();

    PaperManagement paperManagement;
    paperManagement.modifyReview("Admin");

    return 0;
}
