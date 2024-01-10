#ifndef STEP_H
#define STEP_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>

#include "flow.h"
#include "observer.h"

using namespace std;

class Step
{
public:
    Step();

    string getNume();

    string getDescription();

    string getType();

    void setNume(string nume);

    void setDescription(string description);

    void setType(string type);

    void writeToFile(int index, string file_name);

    void deleteStep(string step_name);

    void showAllSteps();

    void runSteps(string file);

    void update(string file_name, string step_name, string value);

    string getValue(string file_name, string step_name, string type);

    string nume;
    string description;
    string type;
    Flow flow;
    Analytics analytics;
};

class CalculusStep : public Step
{
public:
    string operation;
    float result;

    void setOperation(string operation);

    bool decideOperation(string operation);

    vector<string> getStepsFromOperation(string operation);

    string getOperation(string operation);

    string getOperationType(string operation);

    void executeOperation(string operation, string file_name, string step);

    void setResult(float result);
};

template <typename T>
class InputStep : public Step
{
public:
    T input;
    T value;

    void setInput(T input);

    T getInput();
};

class OutputStep : public Step
{
public:
    string title;
    string file;
    string description;
    int number_step;

    void setFile(string file);

    string getFile();

    void setStepTitle(string title);

    string getStepTitle();

    void setNumber(int number_step);

    int getNumber();

    void setFileDescription(string description);

    string getFileDescription();

    string getInfoAboutStep(string title);

    void writeToFile(string file_to_open, string file_to_get_from, string description, string title, string number_step);
};

class FileStep : public Step
{
public:
    string file;

    void setFile(string file);
    string getFile();
    void getFromFile(string file);
};

class DisplayStep : public Step
{
public:
    string step_title;

    void setStepTitle(string step_title);

    void displayFile(string file);
};

class EndStep : public Step
{
public:
    void endProgram();
};

#endif // !STEP_H
