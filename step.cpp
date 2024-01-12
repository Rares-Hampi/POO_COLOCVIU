
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

        if (!(type != "text" || type != "title" || type != "calculus" || type != "input_string" || type != "input_number" || type != "file" || type != "output" || type != "display" || type != "end"))
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

void Step::writeToFile(int index, string file_name)
{
    string directory = "./workflows/";
    try
    {

        ofstream file;
        file.open(directory + file_name + ".csv", ios::app);

        if (!file.good())
        {
            throw runtime_error("Fisierul nu exista");
        }

        if (file.is_open())
        {
            file << "step" + to_string(index) << "," << getNume() << "," << getDescription() << "," << getType() << "," << endl;
            file.close();
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

void Step::deleteStep(string file_name, string step_name)
{
    string directory = "./workflows/";
    try
    {
        ifstream file(directory + file_name + ".csv");
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

void Step::showAllSteps(string file_name)
{
    string directory = "./workflows/";
    try
    {

        ifstream file(directory + file_name + ".csv");

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

void Step::showPreviousSteps(string break_step, string flow_name)
{
    string directory = "./workflows/";
    try
    {
        cout << "Flow name: " << flow_name << endl;

        ifstream file(directory + flow.getName() + ".csv");

        if (file.is_open())
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
                if (step == break_step)
                {
                    break;
                }
                else
                {
                    cout << name << " : " << value << endl;
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

                if (name != step_name)
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
            throw runtime_error("Nu s-a putut deschide fisierul");
        }

        file.close();

        remove((directory + file_name + ".csv").c_str());
        rename((directory + "temp.csv").c_str(), (directory + file_name + ".csv").c_str());
    }
    catch (const std::exception &e)
    {
        cout << e.what() << '\n';
        throw e;
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

float CalculusStep::executeOperation(string operation, string file_name, string step)
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
            result = numbers[0] + numbers[1];
            setResult(result);
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
        throw e;
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
        throw e;
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
        throw e;
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
        throw e;
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
        throw e;
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

void OutputStep::writeToFile(string file_to_open, string file_to_get_form, string description, string step, vector<string> steps, int size)
{
    try
    {
        vector<string> values;

        for (string i : steps)
        {
            values.push_back(getValue(file_to_get_form, i, "float"));
        }

        cout << file_to_open << endl;
        ofstream file(file_to_open + ".txt", ios::app);

        if (file.is_open())
        {

            file << step << endl;
            file << description << endl;
            for (int i = 0; i < size; i++)
            {
                file << steps[i] << " : " << values[i] << endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        throw e;
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
        throw e;
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
    Analytics analytics;
    string directory = "./workflows/";
    try
    {
        ifstream file;

        analytics.setName(file_name);
        analytics.start();

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
                    cout << "Step number: " << step_number << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        system("clear");
                        analytics.skip();
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
                                step.update(file_name, step_name, to_string(calculusStep.result));

                            } while (err == 1);
                        }
                        catch (const std::exception &e)
                        {
                            analytics.fail();
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
                else if (step_type == "input_string")
                {
                    cout << "Step number: " << step_number << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        analytics.skip();
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

                            string value;
                            cout << "Introduceti valoarea: ";
                            cin >> value;
                            InputStep<string> inputStringStep;
                            inputStringStep.setInput(value);
                            step.update(file_name, step_name, inputStringStep.getInput());
                        }
                        catch (const std::exception &e)
                        {
                            analytics.fail();
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
                else if (step_type == "input_number")
                {
                    cout << "Step number: " << step_number << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        analytics.skip();
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

                            float value;
                            cout << "Introduceti valoarea: ";
                            cin >> value;
                            InputStep<float> inputFloatStep;
                            inputFloatStep.setInput(value);
                            step.update(file_name, step_name, to_string(value));
                        }
                        catch (const std::exception &e)
                        {
                            analytics.fail();
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
                else if (step_type == "output")
                {
                    cout << "Step number: " << step_number << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        analytics.skip();
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
                            vector<string> steps;
                            int nr_steps;
                            do
                            {
                                do
                                {
                                    fflush(stdin);
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
                                    fflush(stdin);
                                    cout << "Introduceti titlul: ";
                                    getline(cin, step_title);

                                    if (step_title.empty())
                                    {
                                        cout << "Nu ati introdus niciun titlu!" << endl;
                                        err = 1;
                                    }
                                    else
                                    {
                                        err = 0;
                                    }

                                } while (err == 1);

                                do
                                {
                                    cout << "Introduceti o descriere pentru fisier: ";
                                    getline(cin, step_description);

                                    if (step_description.empty())
                                    {
                                        cout << "Nu ati introdus nicio descriere!" << endl;
                                        err = 1;
                                    }
                                    else
                                    {
                                        err = 0;
                                    }

                                } while (err == 1);

                                cout << "Introduceti numarul de pasi: ";
                                cin >> nr_steps;

                                for (int i = 0; i < nr_steps; i++)
                                {
                                    string step;
                                    cout << "Introduceti pasul de la care doriti sa luati outputul. Pasul trebuie sa fie de forma: step[nr] ";
                                    cin >> step;
                                    steps.push_back(step);
                                }

                                if (step_title.empty() && step_description.empty() && nr_steps == 0)
                                {
                                    throw runtime_error("Nu ati introdus datele necesare pentru a putea crea un fisier!");
                                }

                                else
                                {
                                    OutputStep outputStep;
                                    outputStep.setStepTitle(step_title);
                                    outputStep.writeToFile(file, file_name, step_description, step_title, steps, nr_steps);
                                    err = 0;
                                }
                            } while (err == 1);
                        }
                        catch (const std::exception &e)
                        {
                            analytics.fail();
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
                else if (step_type == "file")
                {
                    cout << "Step number: " << step_number << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        analytics.skip();
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
                            analytics.fail();
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
                else if (step_type == "display")
                {
                    cout << "Step number: " << step_number << endl;

                    cout << "Doresti sa  sari peste acest pas? (y/n)" << endl;
                    cin >> skip;

                    if (skip == "y")
                    {
                        analytics.skip();
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
                            analytics.fail();
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

        if (file.eof())
        {
            if (analytics.returnSkips() == 0)
            {
                analytics.complete();
            }

            analytics.averageFail();
            analytics.print();
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

//