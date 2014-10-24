#include <iostream>
#include <vector>
#include "User.h"

#ifndef _AUTHOR_
#define _AUTHOR_

class Author : public User
{
    private:
        std::vector<int> paperAssigned;
    public:
        void addPaper(int);
};

#endif
