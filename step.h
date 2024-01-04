#ifndef STEP_H
#define STEP_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template <typename T>
T input()
{
    T var;
    cin >> var;
    cout << type(var) << endl;
    return var;
}

template <typename T>
class Step
{

private:
    string type;
    string nume;
    string description;
    T type_input;

public:
    Step(string nume, string description, bool input, T type_input);

    string getNume();

    string getDescription();

    string getType();

    T getTypeInput();

    void setNume(string nume);

    void setDescription(string description);

    void setType(string type);

    void setTypeInput(T type_input);

    void print();

    void printInput();

    void decideStepType(string type);

    void addCalculusStep(string nume, string description);

    void addInputStep(string nume, string description, T type_input);

    void addOutputStep(string nume, string description);

    void addStep(string nume, string description);
};

#endif // !STEP_H
