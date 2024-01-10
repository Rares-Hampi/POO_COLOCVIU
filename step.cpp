
#include "step.h"

Step::Step()
{
    nume = "";
    description = "";
    type = "";
}

void Step::setNume(string name)
{
    try
    {
        if (name.empty())
        {
            throw runtime_error("Nu s-a putut seta numele. Numele nu poate fi gol.");
        }

        this->nume = name;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Step::setDescription(string description)
{
    try
    {

        if (description.empty())
        {
            throw runtime_error("Nu s-a putut seta descrierea. Descrierea nu poate fi goala.");
        }

        this->description = description;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Step::setType(string type)
{
    try
    {
        if (type.empty())
        {
            throw runtime_error("Nu s-a putut seta tipul. Tipul nu poate fi gol.");
        }

        if (!(type != "simple" || type != "calculus" || type != "input" || type != "file" || type != "output" || type != "display" || type != "end"))
        {

            throw runtime_error("Nu s-a putut seta tipul. Tipul trebuie sa fie de forma: simple sau calculus sau input sau file sau output sau display sau end.");
        }

        this->type = type;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

string Step::getNume()
{
    return this->nume;
}

string Step::getDescription()
{
    return this->description;
}

string Step::getType()
{
    return this->type;
}

void Step::writeToFile(int index)
{
    string directory = "./workflows/";
    try
    {

        ofstream file;
        file.open(directory + flow.getName() + ".csv");
        if (!file.good())
        {
            throw runtime_error("Fisierul nu exista");
        }

        if (file.is_open())
        {
            file << "step" + to_string(index) << "," << nume << "," << description << "," << type << endl;
        }
        else
        {
            throw runtime_error("Nu s-a putut deschide fisierul");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
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
            throw runtime_error("Fisierul nu exista");
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
        else
        {
            throw runtime_error("Nu s-a putut deschide fisierul");
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
    try
    {

        ifstream file(directory + flow.getName() + ".csv");

        if (file.good())
        {
            throw runtime_error("Fisierul nu exista");
        }

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
            throw runtime_error("Nu s-a putut deschide fisierul");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Step::update(string file_name, string step_name, string new_value)
{

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
                    temp << line << endl;
                }
                else
                {
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
                    if (value.empty())
                    {
                        throw runtime_error("Nu aveti nicio valoare pentru acest pas!");
                    }
                    else
                    {
                        return value;
                    }
                }
            }
        }
        else
        {
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
    try
    {
        if (operation.empty())
        {
            throw runtime_error("Nu s-a putut seta operatia. Operatia nu poate fi goala.");
        }

        this->operation = operation;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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
            setOperation(operation);
            return true;
        }
        else
        {

            throw runtime_error("Nu s-a putut executa operatia. Operatia trebuie sa fie de forma: step1 + step2 sau step1 - step2 sau step1 * step2 sau step1 / step2 sau step1 min step2 sau step1 max step2.");
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

void CalculusStep::executeOperation(string operation, string file_name, string step)
{
    vector<float> numbers;
    vector<string> steps = getStepsFromOperation(operation);

    try
    {

        string operation_type = getOperationType(operation);

        if (operation_type.empty())
        {
            throw runtime_error("Nu s-a putut executa operatia. Operatia trebuie sa fie de forma: step1 + step2 sau step1 - step2 sau step1 * step2 sau step1 / step2 sau step1 min step2 sau step1 max step2.");
        }

        if (steps[0][4] > step[4] || steps[1][4] > step[4])
        {
            throw runtime_error("Nu s-a putut executa operatia. Nu poti efectua o operatie cu un pas la care nu ai ajuns inainte.");
        }

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
            if (numbers[1] == 0)
            {
                throw runtime_error("Nu s-a putut executa operatia. Nu poti imparti la 0.");
            }

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
    try
    {
        this->result = number;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <>
void InputStep<float>::setInput(float number)
{
    try
    {
        this->input = number;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <>
float InputStep<float>::getInput()
{

    return input;
}

template <>
void InputStep<string>::setInput(string input_given)
{

    try
    {
        if (input_given.empty())
        {
            throw runtime_error("Nu s-a putut seta inputul. Inputul nu poate fi gol.");
        }

        this->input = input_given;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <>
string InputStep<string>::getInput()
{

    return input;
}

void OutputStep::setFile(string file_name)
{
    try
    {
        if (file_name.empty())
        {
            throw runtime_error("Nu s-a putut seta numele fisierului. Numele fisierului nu poate fi gol.");
        }

        this->file = file_name;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

string OutputStep::getFile()
{
    return file;
}

void OutputStep::setStepTitle(string step)
{
    try
    {
        if (step.empty())
        {
            throw runtime_error("Nu s-a putut seta titlul. Titlul nu poate fi gol.");
        }

        this->title = step;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

string OutputStep::getStepTitle()
{
    return title;
}

void OutputStep::setFileDescription(string file_description)
{
    try
    {
        if (file_description.empty())
        {
            throw runtime_error("Nu s-a putut seta descrierea. Descrierea nu poate fi goala.");
        }

        this->description = file_description;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

string OutputStep::getFileDescription()
{
    return description;
}

void OutputStep::setNumber(int number)
{
    try
    {
        this->number_step = number;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int OutputStep::getNumber()
{
    return number_step;
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

void OutputStep::writeToFile(string file_to_open, string file_to_get_form, string description, string step, string number_step)
{
    try
    {
        cout << "step" << number_step << endl;
        string value = getValue(file_to_get_form, number_step, "float");
        if (value.empty())
        {
            throw runtime_error("Pentru pasul precizat nu exista nicio valoare.");
        }

        cout << file_to_open << endl;
        ofstream file(file_to_open + ".txt");

        if (file.is_open())
        {

            file << step << endl;
            file << description << endl;
            file << value << endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void FileStep::setFile(string file_name)
{
    try
    {
        if (file_name.empty())
        {
            throw runtime_error("Nu s-a putut seta numele fisierului. Numele fisierului nu poate fi gol.");
        }

        this->file = file_name;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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

void DisplayStep::setStepTitle(string title)
{
    try
    {
        if (title.empty())
        {
            throw runtime_error("Nu s-a putut seta titlul. Titlul nu poate fi gol.");
        }

        this->step_title = title;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void DisplayStep::displayFile(string file_name)
{

    try
    {
        if (file_name.empty())
        {
            throw runtime_error("Nu s-a putut gasi fisierul. Fisierul trebuie sa fie de forma: fisier.txt sau fisier.csv.");
        }

        ifstream file(file_name);
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
            throw runtime_error("Nu s-a putut deschide fisierul");
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
            string skip;

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

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        system("clear");
                        continue;
                    }
                    else if (skip == "n")
                    {
                        system("clear");
                        cout << "Step name: " << step_name << endl;
                        cout << "Step description: " << step_description << endl;
                        try
                        {
                            string op;
                            int err = 0;

                            do
                            {
                                do
                                {
                                    fflush(stdin);
                                    cout << "Introduceti operatia dorita: ";
                                    getline(cin, op);

                                    if (op.empty())
                                    {
                                        cout << "Nu ati introdus nicio operatie!" << endl;
                                        err = 1;
                                    }
                                    else
                                    {
                                        err = 0;
                                    }
                                } while (err == 1);

                                CalculusStep calculusStep;
                                calculusStep.decideOperation(op);
                                calculusStep.executeOperation(op, file_name, step_number);
                                step.update(file_name, step_number, to_string(calculusStep.result));

                            } while (err == 1);
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
                else if (step_type == "input")
                {
                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        system("clear");
                        continue;
                    }
                    else if (skip == "n")
                    {
                        system("clear");
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
                }
                else if (step_type == "output")
                {

                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        system("clear");
                        continue;
                    }
                    else
                    {
                        system("clear");
                        cout << "Step name: " << step_name << endl;
                        cout << "Step description: " << step_description << endl;
                        try
                        {
                            int err = 0;
                            string file;
                            string step_title;
                            string step_description;
                            string step;

                            do
                            {
                                cout << "Introduceti numele fisierului: ";
                                cin >> file;
                                if (file.empty())
                                {
                                    throw runtime_error("Nu ati introdus niciun nume!");
                                    err = 1;
                                }
                                else
                                {
                                    OutputStep outputStep;
                                    outputStep.setFile(file);
                                    err = 0;
                                }
                            } while (err == 1);

                            do
                            {
                                cout << "Introduceti titlul: ";
                                cin >> step_title;

                                cout << "Introduceti o descriere pentru fisier: ";
                                getline(cin, step_description);

                                cout << "Introduceti pasul de la care doriti sa luati outputul. Pasul trebuie sa fie de forma: step[nr] ";
                                cin >> step;

                                if (step_title.empty() && step_description.empty() && step.empty())
                                {
                                    throw runtime_error("Nu ati introdus niciun titlu!");
                                }

                                else
                                {
                                    OutputStep outputStep;
                                    outputStep.setStepTitle(step_title);
                                    outputStep.writeToFile(file, file_name, step_description, step_title, step);
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
                else if (step_type == "file")
                {

                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        system("clear");
                        continue;
                    }
                    else if (skip == "n")
                    {
                        system("clear");
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
                }
                else if (step_type == "display")
                {
                    system("clear");
                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        system("clear");
                        continue;
                    }
                    else if (skip == "n")
                    {
                        system("clear");
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
                }
                else if (step_type == "end")
                {

                    cout << "Step name: " << step_name << endl;
                    cout << "Step description: " << step_description << endl;
                    try
                    {

                        EndStep endStep;
                        endStep.endProgram();
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