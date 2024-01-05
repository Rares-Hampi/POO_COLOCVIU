#ifndef FLOW.H
#define FLOW .H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "step.h"
#include "user.h"

using namespace std;

class Flow
{

private:
    User user;
    string name;
    int step_number;

public:
    Flow();

    void setName(string name);

    void setStepNumber(int step_number);

    string getName();

    int getStepNumber();

    void addFlow(string name, string user);

    void createFile(string name);
};

#endif // !     FLOW.H
