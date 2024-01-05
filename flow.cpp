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
    try
    {
        if (name == "")
        {
            throw runtime_error("Numele nu poate fi gol!");
        }
        this->name = name;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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
    try
    {
        if (name == "")
        {
            throw runtime_error("Numele nu poate fi gol!");
        }

        string directory = "./workflows/";
        ofstream file;
        file.open(directory + name + ".txt", ios::app);
        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Flow::createStep(string name, string step_name, string step_description)
{
    ofstream file;
    file.open(name + ".txt", ios::app);
    file << step_name << endl;
    file << step_description << endl;
    file << endl;
    file.close();
}

void Flow::deleteFlow(string name)

{
    string line;
    ifstream file;
    ofstream temp;
    file.open("flows.txt");
    temp.open("temp.txt");
    while (getline(file, line))
    {
        if (line != name)
        {
            temp << line << endl;
        }
        else
        {
            getline(file, line);
            getline(file, line);
            getline(file, line);
        }
    }
    file.close();
    temp.close();
    remove("flows.txt");
    rename("temp.txt", "flows.txt");
    remove((name + ".txt").c_str());
}

void Flow::showAllSteps(string file_name)
{
    try
    {

        if (file_name == "")
        {
            throw runtime_error("Nu exista niciun flow cu acest nume!");
        }
        ifstream file;
        if (!file.good())
        {
            throw runtime_error("Nu exista niciun flow cu acest nume!");
        }
        file.open(file_name);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
        }
        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Flow::showAllFlows()
{
    ifstream file;
    file.open("flows.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
    }
    file.close();
}