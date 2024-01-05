#include "flow.h"
#include <chrono>
#include <ctime>

Flow::Flow()
{
    this->name = "";
    this->step_number = 0;
}

void Flow::setName(string name)
{
    this->name = name;
}

void Flow::setStepNumber(int step_number)
{
    this->step_number = step_number;
}

string Flow::getName()
{
    return this->name;
}

int Flow::getStepNumber()
{
    return this->step_number;
}

string currentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::string dateTime = std::ctime(&currentTime);
    dateTime.pop_back(); // Remove the trailing newline character
    return dateTime;
}

void Flow::addFlow(string name, string user)
{

    ofstream file;
    file.open("flows.txt", ios::app);
    file << name << endl;
    file << user << endl;
    file << currentDateTime() << endl;
    file << endl;
    file.close();
}

void Flow::createFile(string name)
{
    ofstream file;
    file.open(name + ".txt", ios::app);
    file.close();
}