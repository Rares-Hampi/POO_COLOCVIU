#include <iostream>
#include "user.h"
#include "criptare_si_validare.h"
#include "flow.h"
#include "step.h"

using namespace std;

class Menu
{
public:
    Menu()
    {
        cout << "Menu constructor" << endl;
    }

    ~Menu()
    {
        cout << "Menu destructor" << endl;
    }

    string getOption()
    {
        string option;

        cout << "Introduceti optiunea: ";
        cin >> option;
        system("clear");
        return option;
    }

    void showStart()
    {
        cout << "Salutare. Bine ai venit pe aplicatia noastra. Cu ce te putem ajuta?" << endl;
        cout << "1. Inregistrare" << endl;
        cout << "2. Logare" << endl;
        cout << "3. Rulare workflow" << endl;
        cout << "4. Creare workflow" << endl;
        cout << "5. Sterge workflow" << endl;
        cout << "6. Iesire" << endl;
    }

    void showRegister()
    {
        cout << "Incepem procesul de inregistrare" << endl;
        cout << "1. Introduceti numele: " << endl;
        cout << "2. Introduceti emailul: " << endl;
        cout << "3. Introduceti numarul de telefon: " << endl;
        cout << "4. Introduceti parola: " << endl;
        cout << "5. Inregistrare" << endl;
        cout << "6. Inapoi" << endl;
    }

    void showLogin()
    {
        cout << "Incepem procesul de logare" << endl;
        cout << "1. Introduceti emailul: ";
        cout << "2. Introduceti parola: ";
        cout << "3. Logare" << endl;
        cout << "4. Inapoi" << endl;
    }

    void showRunWorkflow()
    {
        cout << "Rulare workflow" << endl;
        cout << "1. Afisare workflows" << endl;
        cout << "2. Alege workflow" << endl;
        cout << "3. Inapoi" << endl;
    }

    void showCreateWorkflow()
    {
        cout << "Sa incepem!" << endl;
        cout << "1. Ce nume doriti sa aiba workflowul?" << endl;
        cout << "2. Cate taskuri doriti sa aiba acest workflow? :" << endl;
        cout << "3. Adaugare task" << endl;
        cout << "4. Sterege task" << endl;
        cout << "5. Afisare taskuri" << endl;
        cout << "6. Inapoi" << endl;
    }

    void showAddTask()
    {
        cout << "Adaugare task" << endl;
        cout << "1. Introduceti numele taskului: ";
        cout << "2. Introduceti descrierea taskului: ";
        cout << "3. Taskul are nevoie de un input? (y/n): ";
        cout << "4. Adaugare task" << endl;
        cout << "5. Inapoi" << endl;
    }

    void showDeleteWorkflow()
    {
        cout << "Sterge workflow" << endl;
        cout << "1. Afisare workflows" << endl;
        cout << "2. Sterge workflow" << endl;
        cout << "3. Inapoi" << endl;
    }

    void showExit()
    {
        cout << "Iesire" << endl;
    }
};

class App
{
public:
    App()
    {
        cout << "App constructor" << endl;
    }

    ~App()
    {
        cout << "App destructor" << endl;
    }

    void run()
    {
        string option;

        do
        {
            menu.showStart();
            option = menu.getOption();
            // register
            if (option == "1")
            {
                string optionRegister;
                do
                {
                    menu.showRegister();
                    optionRegister = menu.getOption();
                    if (optionRegister == "1")
                    {
                        string nume;
                        string error;
                        do
                        {

                            cout << "Introduceti numele: ";
                            getline(cin, nume);

                            try
                            {
                                user.setNume(nume);
                                error = "";
                            }
                            catch (const char *e)
                            {
                                error = e;
                                cout << e << '\n';
                            };
                            fflush(stdin);
                        } while (error.length() > 0);
                    }
                    else if (optionRegister == "2")
                    {
                        string email;
                        string error;
                        do
                        {
                            cout << "Introduceti email: ";
                            cin >> email;
                            try
                            {
                                if (email.empty())
                                {
                                    throw "Emailul nu poate fi gol";
                                }

                                user.setEmail(email);
                                error = "";
                            }
                            catch (const char *e)
                            {
                                error = e;
                                cout << e << '\n';
                            }

                        } while (error.length() > 0);
                    }
                    else if (optionRegister == "3")
                    {
                        string parola;
                        string error;
                        do
                        {
                            cout << "Introduceti parola: ";
                            cin >> parola;
                            try
                            {
                                if (parola.empty())
                                {
                                    throw "Parola nu poate fi goala";
                                }
                                user.setParola(parola);
                                error = "";
                            }
                            catch (const char *e)
                            {
                                error = e;
                                cerr << e << '\n';
                            }
                            catch (const string &e)
                            {
                                error = e;
                                cerr << e << '\n';
                            }
                        } while (error.length() > 0);
                    }
                    else if (optionRegister == "4")
                    {
                        string phone;
                        string error;
                        do
                        {
                            cout << "Introduceti telefon: ";

                            cin >> phone;
                            try
                            {
                                if (phone.empty())
                                {
                                    throw "Telefonul nu poate fi gol";
                                }

                                user.setPhone(phone);
                                error = "";
                            }
                            catch (const char *e)
                            {
                                error = e;
                                cerr << e << '\n';
                            }
                        } while (error.length() > 0);
                    }
                    else if (optionRegister == "5")
                    {
                        try
                        {

                            user.Register(user.getNume(), user.getEmail(), user.getParola(), user.getPhone());
                            cout << "Inregistrare cu succes" << endl;
                        }
                        catch (const char *e)
                        {
                            cout << e << '\n';
                        }
                    }

                } while (optionRegister != "6");
            }
            // Login
            else if (option == "2")
            {
                string optionLogin;
                do
                {
                    menu.showLogin();
                    optionLogin = menu.getOption();
                    if (optionLogin == "1")
                    {
                        string email;
                        string error;

                        do
                        {
                            cout << "Introduceti email: ";
                            cin >> email;
                            try
                            {
                                if (email.empty())
                                {
                                    throw "Emailul nu poate fi gol";
                                }

                                user.setEmail(email);
                            }
                            catch (const char *e)
                            {
                                cerr << e << '\n';
                                error = e;
                            }
                        } while (error.length() > 0);
                    }
                    else if (optionLogin == "2")
                    {
                        string parola;
                        string error;
                        cout << "Introduceti parola: ";

                        cin >> parola;
                        do
                        {
                            try
                            {
                                if (parola.empty())
                                {
                                    throw "Parola nu poate fi goala";
                                }
                                user.setParola(parola);
                                cout << "Parola setata cu succes" << endl;
                                error = "";
                            }
                            catch (const char *e)
                            {
                                cerr << e << '\n';
                                error = e;
                            }
                        } while (error.length() > 0);
                    }
                    else if (optionLogin == "3")
                    {
                        try
                        {
                            user.Login(user.getEmail(), user.getParola());
                            cout << "Logare cu succes" << endl;
                        }
                        catch (const char *e)
                        {
                            cerr << e << '\n';
                        }
                        catch (const string &e)
                        {
                            cerr << e << '\n';
                        }
                    }
                    else if (optionLogin == "4")
                    {
                        cout << "Inapoi" << endl;
                    }
                } while (optionLogin != "4");
            }
            // run workflow
            else if (option == "3")
            {
                menu.showRunWorkflow();
                string option2;
                do
                {
                    option2 = menu.getOption();
                    if (option2 == "1")
                    {
                        cout << "Afisare workflows" << endl;
                    }
                    else if (option2 == "2")
                    {
                        cout << "Alege workflow" << endl;
                    }
                    else if (option2 == "3")
                    {
                        cout << "Inapoi" << endl;
                    }
                    else
                    {
                        cout << "Optiune invalida" << endl;
                    }
                } while (option2 != "3");
            }
            // create workflow
            else if (option == "4")
            {
                menu.showCreateWorkflow();
                string option2;
                do
                {
                    option2 = menu.getOption();
                    // ! set workflow name
                    if (option2 == "1")
                    {
                        try
                        {
                            cout << "Ce nume doriti sa aiba workflowul?" << endl;
                            string name;
                            cin >> name;
                            flow.setName(name);
                            flow.createFile(name);
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }
                    //! set workflow steps

                    else if (option2 == "2")
                    {
                        try
                        {
                            cout << "Stiti cate taskuri doriti sa aiba acest workflow? (y/n): ";
                            string option4;
                            cin >> option4;

                            // ! set the step number to 0 if the user doesn't know how many steps he wants
                            if (option4 == "n")
                            {
                                cout << "Nu este nicio problema, puteti aduga taskuri pe parcurs" << endl;
                                flow.setStepNumber(0);
                                flow.addFlow(flow.getName(), "user");
                            }

                            //! set the step number if the user knows how many steps he wants and add the steps
                            else
                            {
                                cout << "Cate taskuri doriti sa aiba acest workflow? :" << endl;
                                int number_of_tasks;
                                cin >> number_of_tasks;
                                if (number_of_tasks < 0)
                                {
                                    throw "Numarul de taskuri nu poate fi negativ";
                                }
                                else if (number_of_tasks == 0)
                                {
                                    throw "Nu ati introdus niciun task";
                                }

                                flow.setStepNumber(number_of_tasks);

                                cout << "Ati ales sa aveti " << number_of_tasks << " taskuri" << endl;
                                // ! set the steps
                                for (int i = 0; i < number_of_tasks; i++)
                                {
                                    int err = 0;
                                    cout << "Taskul " << i + 1 << endl;

                                    // set the name of the task
                                    do
                                    {
                                        cout << "Numele taskului este: ";
                                        string name;
                                        cin >> name;
                                        if (name.empty())
                                        {
                                            cout << "Numele nu poate fi gol" << endl;
                                            err = 1;
                                        }
                                        else
                                        {
                                            step.setNume(name);
                                            err = 0;
                                        }

                                    } while (err == 1);

                                    // set the description of the task
                                    do
                                    {
                                        cout << "Descrierea taskului este: ";
                                        string description;
                                        cin >> description;
                                        if (description.empty())
                                        {
                                            cout << "Descrierea nu poate fi goala" << endl;
                                            err = 1;
                                        }
                                        else
                                        {
                                            step.setDescription(description);
                                            err = 0;
                                        }

                                    } while (err == 1);

                                    // set the type of the task
                                    do
                                    {
                                        cout << "Ce tip de task doresti sa fie? (simple/calculus/input/file): ";
                                        string type;
                                        cin >> type;
                                        if (type.empty())
                                        {
                                            cout << "Tipul nu poate fi gol" << endl;
                                            err = 1;
                                        }
                                        else
                                        {
                                            step.setType(type);
                                            err = 0;
                                        }

                                    } while (err == 1);

                                    step.writeToFile();
                                }
                            }
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }

                    // ! add steps manual, one by one
                    else if (option2 == "3")
                    {

                        int err = 0;
                        int index = flow.getStepNumber() + 1;
                        cout << "Taskul " << index << endl;

                        // set the name of the task
                        do
                        {
                            cout << "Numele taskului este: ";
                            string name;
                            cin >> name;
                            if (name.empty())
                            {
                                cout << "Numele nu poate fi gol" << endl;
                                err = 1;
                            }
                            else
                            {
                                step.setNume(name);
                                err = 0;
                            }

                        } while (err == 1);

                        // set the description of the task
                        do
                        {
                            cout << "Descrierea taskului este: ";
                            string description;
                            cin >> description;
                            if (description.empty())
                            {
                                cout << "Descrierea nu poate fi goala" << endl;
                                err = 1;
                            }
                            else
                            {
                                step.setDescription(description);
                                err = 0;
                            }

                        } while (err == 1);

                        // set the type of the task
                        do
                        {
                            cout << "Ce tip de task doresti sa fie? (simple/calculus/input/file): ";
                            string type;
                            cin >> type;
                            if (type.empty())
                            {
                                cout << "Tipul nu poate fi gol" << endl;
                                err = 1;
                            }
                            else
                            {
                                step.setType(type);
                                err = 0;
                            }

                        } while (err == 1);

                        step.writeToFile();
                    }

                    // ! delete a step
                    else if (option2 == "4")
                    {
                        try
                        {
                            string step_name;
                            cout << "Ce task doriti sa stergeti?" << endl;
                            cin >> step_name;
                            step.deleteStep(step_name, flow.getName());
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }

                    // ! show all steps
                    else if (option2 == "5")
                    {
                        try
                        {
                            step.showAllSteps(flow.getName());
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }

                    else if (option2 == "6")
                    {
                        cout << "Inapoi" << endl;
                    }
                } while (option2 != "6");
            }
            // delete workflow
            else if (option == "5")
            {
                menu.showDeleteWorkflow();
                string option2;
                do
                {
                    option2 = menu.getOption();

                    // ! show all flows
                    if (option2 == "1")
                    {
                        try
                        {
                            flow.showAllFlows();
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }

                    // ! delete a flow
                    else if (option2 == "2")
                    {
                        try
                        {
                            string name;
                            cout << "Ce flow doriti sa stergeti?" << endl;
                            cin >> name;
                            flow.deleteFlow(name);
                        }
                        catch (const std::exception &e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }

                    else if (option2 == "3")
                    {
                        cout << "Inapoi" << endl;
                    }
                } while (option2 != "3");
            }

            else if (option == "6")
            {
                menu.showExit();
            }

        } while (option != "6");
    }

private:
    Menu menu;
    User user;
    Flow flow;
    CalculusStep calculusStep;
    InputStep<string> inputStep;
    InputStep<int> inputStepInt;
    FileStep fileStep;
    Step step;
};

int main()
{
    App app;
    app.run();
    return 0;
}
