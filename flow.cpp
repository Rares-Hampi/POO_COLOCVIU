#include "flow.h"

Flow::Flow()
{
    this->name = "";
    this->step_number = 0;
}

void Flow::setName(string nume)
{
    try
    {
        if (nume == "")
        {
            throw runtime_error("Numele nu poate fi gol!");
        }

        this->name = nume;
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

void Flow::addFlow(string name, string user, int number)
{

    ofstream file;
    file.open("flows.csv", ios::app);
    file << name << "," << number << "," << user << "," << currentDateTime() << endl;
    file << endl;
    file.close();
}

void Flow::createFile(string name)
{
    try
    {
        if (name.empty())
        {
            throw runtime_error("Numele nu poate fi gol!");
        }

        string directory = "./workflows/";
        ofstream file;
        file.open(directory + name + ".csv");
        file << "step_name"
             << ","
             << "title"
             << ","
             << "descriprion"
             << ","
             << "type"
             << "\n";
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
    string directory = "./workflows/";
    string line;
    try
    {

        ifstream file;
        ofstream temp;
        file.open("flows.csv", ios::in);
        temp.open("temp.csv", ios::out);

        if (!file.good())
        {
            throw runtime_error("Nu s-a putut deschide fisierul");
        }

        if (file.is_open() && temp.is_open())
        {
            while (getline(file, line))
            {
                stringstream ss(line);
                string nume;
                getline(ss, nume, ',');
                cout << nume << endl;
                if (nume != name)
                {
                    temp << line << endl;
                }
            }
        }
        file.close();
        temp.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    remove("flows.csv");
    rename("temp.csv", "flows.csv");
    remove((directory + name + ".csv").c_str());
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
    file.open("flows.csv");
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
