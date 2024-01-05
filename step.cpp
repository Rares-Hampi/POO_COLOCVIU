#include "step.h"

Step::Step()
{
    nume = "";
    description = "";
    type = "";
}

void Step::setNume(string name)
{
    nume = name;
}

void Step::setDescription(string description)
{
    description = description;
}

void Step::setType(string type)
{
    type = type;
}

string Step::getNume()
{
    return nume;
}

string Step::getDescription()
{
    return description;
}

string Step::getType()
{
    return type;
}

void Step::writeToFile()
{
    ofstream file;
    file.open("flows.txt", ios::app);
    if (file.is_open())
    {
        file << nume << description << type << endl;
    }
}

void Step::deleteStep(string step_name, string file_name)
{
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line == step_name)
            {
                file << "";
            }
        }
    }

    file.close();
}

void Step::showAllSteps(string file_name)
{
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
    }
}

void CalculusStep::setOperation(string operation)
{
    operation = operation;
}

string CalculusStep::getOperation(string operation)
{
    return operation;
}

bool CalculusStep::decideOperation(string operation)
{
    try
    {
        regex operation_regex("(step[0-9]+) ([\\+\\-\\*\\/\\min\\max]) (step[0-9]+)");

        if (regex_match(operation, operation_regex))
        {
            setOperation(operation);
            return true;
        }
        else
        {
            throw "Nu s-a putut executa operatia";
        }
    }
    catch (const char *e)
    {
        throw e;
    }
}

vector<string> CalculusStep::getStepsFromOperation(string operation)
{
    vector<string> steps;
    try
    {
        if (operation.empty())
        {
            throw "Nu s-a putut executa operatia. Operatia trebuie sa fie de forma: step1 + step2 sau step1 - step2 sau step1 * step2 sau step1 / step2 sau step1 min step2 sau step1 max step2.";
        }

        regex step_regex("(step[0-9]+)");
        sregex_iterator iter(operation.begin(), operation.end(), step_regex);
        sregex_iterator end;

        while (iter != end)
        {
            smatch match = *iter;
            steps.push_back(match.str());
            ++iter;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return steps;
}

vector<int> CalculusStep::getNumberFromStep()
{
    vector<int> numbers;
    try
    {
        vector<string> steps = getStepsFromOperation(operation);

        fstream file;
        file.open("flows.txt", ios::in);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line == steps[0])
                {

                    for (int i = 0; i < 2; i++)
                    {
                        getline(file, line);
                    }

                    regex number_regex("([0-9]+)");
                    sregex_iterator iter(line.begin(), line.end(), number_regex);
                    sregex_iterator end;
                    smatch match = *iter;
                    numbers.push_back(stoi(match.str()));
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void CalculusStep::executeOperation(string operation)
{
    try
    {
        vector<int> numbers = getNumberFromStep();
        string operation_type = getOperation(operation);

        if (operation_type == "+")
        {
            cout << numbers[0] + numbers[1] << endl;
        }
        else if (operation_type == "-")
        {
            cout << numbers[0] - numbers[1] << endl;
        }
        else if (operation_type == "*")
        {
            cout << numbers[0] * numbers[1] << endl;
        }
        else if (operation_type == "/")
        {
            cout << numbers[0] / numbers[1] << endl;
        }
        else if (operation_type == "min")
        {
            cout << min(numbers[0], numbers[1]) << endl;
        }
        else if (operation_type == "max")
        {
            cout << max(numbers[0], numbers[1]) << endl;
        }
        else
        {
            throw "Nu s-a putut executa operatia. Operatia trebuie sa fie de forma: step1 + step2 sau step1 - step2 sau step1 * step2 sau step1 / step2 sau step1 min step2 sau step1 max step2.";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <class T>
void InputStep<T>::setInput(T input)
{

    input = input;
}

template <class T>
T InputStep<T>::getInput()
{

    return input;
}

void OutputStep::setFile(string file)
{
    file = file;
}

string OutputStep::getFile()
{
    return file;
}

void OutputStep::setStepTitle(string step_title)
{
    step_title = step_title;
}

string OutputStep::getStepTitle()
{
    return step_title;
}

void OutputStep::setFileDescription(string file_description)
{
    file_description = file_description;
}

string OutputStep::getFileDescription()
{
    return file_description;
}

string OutputStep::getInfoAboutStep(string step_title)
{
    try
    {
        if (step_title.empty())
        {
            throw "Nu s-a putut gasi step-ul. Step-ul trebuie sa fie de forma: step1.";
        }
        fstream file;
        file.open("flows.txt", ios::in);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line == step_title)
                {
                    return line;
                }
            }
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void OutputStep::writeToFile()
{
    string step_info = getInfoAboutStep(step_title);
    fstream file;
    file.open("flows.txt", ios::app);
    if (file.is_open())
    {
        file << file_description << endl
             << endl;
        file << step_info << endl;
    }
}

void FileStep::setFile(string file)
{
    file = file;
}

string FileStep::getFile()
{
    return file;
}

void FileStep::getFromFile(string file)
{
    try
    {
        if (file.empty())
        {
            throw "Nu s-a putut gasi fisierul. Fisierul trebuie sa fie de forma: fisier.txt.";
        }
        fstream file;
        file.open("flows.txt", ios::in);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
