#include <iostream>
#include "SystemMain.h"
#include "PCChair.h"
#include "PaperManagement.h"

using namespace std;

int main()
{
    SystemMain systemMain;
    //systemMain.mainPage();

    PaperManagement temp;
    temp.submitPaper();

    return 0;
}
