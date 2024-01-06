#ifndef FLOW_H
#define FLOW_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

#include "step.h"
#include "user.h"

using namespace std;

class Flow
{

private:
    User user;
    Step step;
    CalculusStep calculusStep;
    InputStep<int> inputStepInt;
    InputStep<string> inputStepString;
    FileStep fileStep;
    OutputStep outputStep;

    string name;
    int step_number;

public:
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

    void runFlow(string name);
};

#endif // !     FLOW.H
