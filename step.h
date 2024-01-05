#ifndef STEP_H
#define STEP_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
using namespace std;

class Step
{
public:
    virtual ~Step() {}
    virtual void print() = 0;

    string getNume();

    string getDescription();

    string getType();

    void setNume(string nume);

    void setDescription(string description);

    void setType(string type);

    void writeToFile();

protected:
    string nume;
    string description;
    string type;
};

class CalculusStep : public Step
{
public:
    void print() override
    {
        cout << "Ai cerut sa se execute operatia: " << operation << endl;
    }

private:
    string operation;

    void setOperation(string operation);

    void decideOperation(string operation);

    vector<string> getStepsFromOperation(string operation);

    string getOperation(string operation);

    vector<int> getNumberFromStep();

    void executeOperation(string operation);
};

template <typename T>
class InputStep : public Step
{
public:
    void print() override;

private:
    T input;

    void setInput(T input);

    T getInput();
};

class OutputStep : public Step
{
public:
    void print() override
    {
        cout << "Ai cerut ca outputul sa fie: " << file << endl;
    }

private:
    string step_title;
    string file;
    string file_description;

    void setFile(string file);

    string getFile();

    void setStepTitle(string step_title);

    string getStepTitle();

    void setFileDescription(string file_description);

    string getFileDescription();

    string getInfoAboutStep(string step_title);

    void writeToFile();
};

class FileStep : public Step
{
public:
    void print()
    {
        cout << "Ai cerut ca fisierul sa fie: " << file << endl;
    }

private:
    string file;

    void setFile(string file);
    string getFile();
    void getFromFile(string file);
};

#endif // !STEP_H
