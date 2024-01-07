
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

void Step::writeToFile(int index)
{
    string directory = "./workflows/";
    ofstream file;
    file.open(directory + flow.getName(), ios::app);
    if (file.is_open())
    {
        file << "step" + to_string(index) << "," << nume << "," << description << "," << type << endl;
    }
}

void Step::deleteStep(string step_name)
{
    string directory = "./workflows/";
    try
    {
        ifstream file(directory + flow.getName() + ".csv");
        ofstream temp("./workflows/temp.csv");

        if (!file.good())
        {
            throw runtime_error("Nu s-a putut deschide fisierul");
        }
        if (file.is_open() && temp.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string name;
                getline(ss, name, ',');
                cout << name << endl;
                if (name != step_name)
                {
                    temp << line << endl;
                }
            }
        }

        file.close();
        temp.close();
        remove((directory + flow.getName() + ".csv").c_str());
        rename("./workflows/temp.csv", (directory + flow.getName() + ".csv").c_str());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Step::showAllSteps()
{
    string directory = "./workflows/";
    fstream file;
    file.open(directory + flow.getName() + ".csv", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
    }
}

void Step::update(string file_name, string step_name, string new_value)
{
    cout << "step_name" << step_name << "gigel" << endl;

    string directory = "./workflows/";
    try
    {
        if (file_name.empty())
        {
            throw runtime_error("Nu s-a putut gasi fisierul. Fisierul trebuie sa fie de forma: fisier.csv.");
        }

        ifstream file(directory + file_name + ".csv");
        ofstream temp(directory + "temp.csv");

        if (file.is_open() && temp.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string step;
                string name;
                string description;
                string type;
                string value;

                getline(ss, step, ',');
                getline(ss, name, ',');
                getline(ss, description, ',');
                getline(ss, type, ',');
                getline(ss, value, ',');

                if (step != step_name)
                {
                    cout << "plm"
                         << "step" << step << endl;
                    temp << line << endl;
                }
                else
                {
                    cout << "step" << step << endl;
                    temp << step << "," << name << "," << description << "," << type << "," << new_value << endl;
                }
            }
            temp.close();
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }

        file.close();

        remove((directory + file_name + ".csv").c_str());
        rename((directory + "temp.csv").c_str(), (directory + file_name + ".csv").c_str());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

string Step::getValue(string file_name, string step_name, string type)

{

    string directory = "./workflows/";
    try
    {

        if (file_name.empty())
        {
            throw runtime_error("Nu s-a putut gasi fisierul. Fisierul trebuie sa fie de forma: fisier.csv.");
        }

        ifstream file(directory + file_name + ".csv");

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                // skip the first line
                if (line == "step_name,title,descriprion,type,value")
                {
                    continue;
                }
                stringstream ss(line);
                string step;
                string name;
                string description;
                string type;
                string value;

                getline(ss, step, ',');
                getline(ss, name, ',');
                getline(ss, description, ',');
                getline(ss, type, ',');
                getline(ss, value, ',');

                if (step == step_name)
                {
                    return value;
                }
            }
        }
        else
        {
            return "";
            throw runtime_error("Nu s-a putut deschide fisierul");
        }

        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
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
        // string  = step1 + step2, make a regex to check if the operation is valid
        regex operation_regex("(step[0-9]+)(\\s+)(\\+|-|\\*|/|min|max)(\\s+)(step[0-9]+)");

        if (regex_match(operation, operation_regex))
        {
            cout << "Operatia este valida" << endl;
            setOperation(operation);
            return true;
        }
        else
        {

            throw runtime_error("Nu s-a putut executa operatia");
            return false;
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
}

vector<string> CalculusStep::getStepsFromOperation(string operation)
{
    vector<string> steps;
    try
    {
        if (operation.empty())
        {
            throw runtime_error("Nu s-a putut executa operatia. Operatia trebuie sa fie de forma: step1 + step2 sau step1 - step2 sau step1 * step2 sau step1 / step2 sau step1 min step2 sau step1 max step2.");
        }

        //  operation = step1 + step2 and I want to extract step1 and step2
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

string CalculusStep::getOperationType(string operation)
{
    string operation_type;
    try
    {
        if (operation.empty())
        {
            throw runtime_error("Nu s-a putut executa operatia. Operatia trebuie sa fie de forma: step1 + step2 sau step1 - step2 sau step1 * step2 sau step1 / step2 sau step1 min step2 sau step1 max step2.");
        }

        //  operation = step1 + step2 and I want to extract step1 and step2
        regex operation_regex("(\\+|-|\\*|/|min|max)");
        sregex_iterator iter(operation.begin(), operation.end(), operation_regex);
        sregex_iterator end;
        while (iter != end)
        {
            smatch match = *iter;
            operation_type = match.str();
            ++iter;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return operation_type;
}

void CalculusStep::executeOperation(string operation, string file_name)
{
    vector<float> numbers;
    vector<string> steps = getStepsFromOperation(operation);

    try
    {

        string operation_type = getOperationType(operation);

        cout << "operation_type" << operation_type << endl;

        numbers.push_back(stof(getValue(file_name, steps[0], "float")));
        numbers.push_back(stof(getValue(file_name, steps[1], "float")));

        float result;

        if (operation_type == "+")
        {
            cout << numbers[0] + numbers[1] << endl;
            result = numbers[0] + numbers[1];
            setResult(result);
        }
        else if (operation_type == "-")
        {
            cout << numbers[0] - numbers[1] << endl;
            result = numbers[0] - numbers[1];
            setResult(result);
        }
        else if (operation_type == "*")
        {
            cout << numbers[0] * numbers[1] << endl;
        }
        else if (operation_type == "/")
        {
            cout << numbers[0] / numbers[1] << endl;
            result = numbers[0] / numbers[1];
            setResult(result);
        }
        else if (operation_type == "min")
        {
            cout << min(numbers[0], numbers[1]) << endl;
            result = min(numbers[0], numbers[1]);
            setResult(result);
        }
        else if (operation_type == "max")
        {
            cout << max(numbers[0], numbers[1]) << endl;
            result = max(numbers[0], numbers[1]);
            setResult(result);
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

void CalculusStep::setResult(float number)
{
    result = number;
}

template <>
void InputStep<float>::setInput(float number)
{
    input = number;
}

template <>
float InputStep<float>::getInput()
{

    return input;
}

template <>
void InputStep<string>::setInput(string input)
{

    input = input;
}

template <>
string InputStep<string>::getInput()
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
    string info = "";
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
                    info = line;
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
    return info;
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

void DisplayStep::setStepTitle(string step_title)
{
    step_title = step_title;
}

void DisplayStep::displayFile(string file_name)
{
    string directory = "./workflows/";
    try
    {

        fstream file;
        file.open(directory + file_name + ".csv", ios::in);
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

void EndStep::endProgram()
{
    cout << "Programul s-a terminat!" << endl;
}

void Step::runSteps(string file_name)
{
    Step step;
    string directory = "./workflows/";
    try
    {
        ifstream file;

        file.open(directory + file_name + ".csv", ios::in);
        if (!file.good())
        {
            throw runtime_error("Nu exista niciun flow cu acest nume!");
        }

        if (file.is_open())
        {
            string line;
            string step_name;
            string step_description;
            string step_type;
            string step_number;
            string value;

            while (getline(file, line))
            {
                // skip the first line
                if (line == "step_name,title,descriprion,type,value")
                {
                    continue;
                }
                stringstream ss(line);
                getline(ss, step_number, ',');
                getline(ss, step_name, ',');
                getline(ss, step_description, ',');
                getline(ss, step_type, ',');

                if (step_type == "text" || step_type == "title")
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
                            fflush(stdin);
                            fflush(stdin);
                            do
                            {
                                cout << "Introduceti operatia dorita: ";

                                getline(cin, op);
                                cout << op << endl;
                                if (op.empty())
                                {
                                    cout << "Nu ati introdus nicio operatie!" << endl;
                                    err = 1;
                                }
                                else
                                {
                                    err = 0;
                                    cout << op << endl;
                                }
                            } while (err == 1);

                            CalculusStep calculusStep;
                            calculusStep.decideOperation(op);
                            calculusStep.executeOperation(op, file_name);

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
                            else if (value_type == "float")
                            {
                                float value;
                                cout << "Introduceti valoarea: ";
                                cin >> value;
                                InputStep<float> inputFloatStep;
                                inputFloatStep.setInput(value);
                                step.update(file_name, step_number, to_string(value));
                                err = 0;
                            }

                            else if (value_type == "string")
                            {
                                string value;
                                cout << "Introduceti valoarea: ";
                                cin >> value;
                                InputStep<string> inputStringStep;
                                inputStringStep.setInput(value);
                                step.update(file_name, step_name, inputStringStep.getInput());
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
                                OutputStep outputStep;
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
                                OutputStep outputStep;
                                outputStep.setStepTitle(step_title);
                                err = 0;
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
                                FileStep fileStep;
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
                else if (step_type == "display")
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
                                DisplayStep displayStep;
                                displayStep.displayFile(file_name);
                                err = 0;
                            }
                        } while (err == 1);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else if (step_type == "end")
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
                                EndStep endStep;
                                endStep.endProgram();
                                err = 0;
                            }
                        } while (err == 1);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }

                else
                {
                    throw runtime_error("Nu ati introdus un tip valid!");
                }
            }
            file.close();
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

//