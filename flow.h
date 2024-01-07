#ifndef FLOW_H
#define FLOW_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

#include "user.h"

using namespace std;

class Flow
{

private:
    string name;
    int step_number;

public:
    User user;

    Flow();

    void setName(string name);

    void setStepNumber(int step_number);

    string getName();

    int getStepNumber();

    void addFlow(string name, string user, int number);

    void createFile(string name);

    void createStep(string name, string step_name, string step_description);

    void deleteFlow(string name);

    void showAllSteps(string file_name);

    void showAllFlows();
};

#endif // !     FLOW.H
