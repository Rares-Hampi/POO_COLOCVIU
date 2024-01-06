#include "flow.h"

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

void Flow::addFlow(string name, string user, int number)
{

    ofstream file;
    file.open("flows.csv", ios::app);
    file << name << "," << number << "," << user << "," << currentDateTime() << endl;
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
        file.open(directory + name + ".csv", ios::app);
        file << "name"
             << ","
             << "descriprion"
             << ","
             << "type" << endl;
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

void Flow::runFlow(string name)
{
    try
    {
        if (name == "")
        {
            throw runtime_error("Nu exista niciun flow cu acest nume!");
        }
        ifstream file;
        if (!file.good())
        {
            throw runtime_error("Nu exista niciun flow cu acest nume!");
        }
        file.open(name);
        if (file.is_open())
        {
            string line;
            string step_name;
            string step_description;
            string step_type;

            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, step_name, ',');
                getline(ss, step_description, ',');
                getline(ss, step_type, ',');

                if (step_type == "simple")
                {
                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;
                }
                else if (step_type == "calculus")
                {
                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;

                    try
                    {
                        string op;
                        int err = 0;

                        do
                        {
                            cout << "Introduceti operatia dorita: ";
                            cin >> op;

                            calculusStep.decideOperation(op);
                            calculusStep.setOperation(op);
                            calculusStep.executeOperation(op);

                        } while (err == 1);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else if (step_type == "input")
                {
                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;
                    try
                    {
                        string value_type;
                        int err = 0;

                        do
                        {
                            cout << "Introduceti tipul valorii: ";
                            cin >> value_type;
                            if (value_type.empty())
                            {
                                throw runtime_error("Nu ati introdus niciun tip!");
                            }
                            else if (value_type == "int")
                            {
                                int value;
                                cout << "Introduceti valoarea: ";
                                cin >> value;
                                inputStepInt.setInput(value);
                                err = 0;
                            }
                            else if (value_type == "string")
                            {
                                string value;
                                cout << "Introduceti valoarea: ";
                                cin >> value;
                                inputStepString.setInput(value);
                                err = 0;
                            }
                            else
                            {
                                throw runtime_error("Nu ati introdus un tip valid!");
                                err = 1;
                            }

                        } while (err == 1);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else if (step_type == "output")
                {
                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;
                    try
                    {
                        int err = 0;
                        string file_name;
                        string step_title;

                        do
                        {
                            cout << "Introduceti numele fisierului: ";
                            cin >> file_name;
                            if (file_name.empty())
                            {
                                throw runtime_error("Nu ati introdus niciun nume!");
                                err = 1;
                            }
                            else
                            {
                                outputStep.setFile(file_name);
                                err = 0;
                            }
                        } while (err == 1);

                        do
                        {
                            cout << "Introduceti titlul: ";
                            cin >> step_title;
                            if (step_title.empty())
                            {
                                throw runtime_error("Nu ati introdus niciun titlu!");
                            }
                            else
                            {
                                outputStep.setStepTitle(step_title);
                            }
                        } while (err == 1);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else if (step_type == "file")
                {
                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;

                    try
                    {
                        int err = 0;
                        string file_name;

                        do
                        {
                            cout << "Introduceti numele fisierului (cu tot cu extensie): ";
                            cin >> file_name;
                            if (file_name.empty())
                            {
                                throw runtime_error("Nu ati introdus niciun nume!");
                                err = 1;
                            }
                            else
                            {
                                fileStep.setFile(file_name);
                                err = 0;
                            }
                        } while (err == 1);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
            }
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}