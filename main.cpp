#include <iostream>

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
        cout << "1. Introduceti numele: ";
        cout << "2. Introduceti emailul: ";
        cout << "3. Introduceti numarul de telefon: ";
        cout << "4. Introduceti parola: ";
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
        cout << "Ce tip de workflow doriti sa creati?" << endl;
        cout << "1. Workflow tip lista de cumparaturi" << endl;
        cout << "2. Workflow tip organizare eveniment" << endl;
        cout << "3. Workflow custom" << endl;
        cout << "4. Inapoi" << endl;
    }

    void showShoppingListWorkflow()
    {
        cout << "Workflow tip lista de cumparaturi" << endl;
        cout << "1. Adaugare task" << endl;
        cout << "2. Inapoi" << endl;
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

    void showEventWorkflow()
    {
        cout << "Workflow tip organizare eveniment" << endl;
        cout << "1. Adaugare task" << endl;
        cout << "2. Inapoi" << endl;
    }

    void showCustomWorkflow()
    {
        cout << "Workflow custom" << endl;
        cout << "1. Cate taskuri doriti sa aiba acest workflow? :" << endl;
        cout << "2. Adaugare task" << endl;
        cout << "3. Inapoi" << endl;
    }

    void showDeleteWorkflow()
    {
        cout << "Sterge workflow" << endl;
        cout << "1. Afisare workflows" << endl;
        cout << "2. Alege workflow" << endl;
        cout << "3. Sterge workflow" << endl;
        cout << "4. Inapoi" << endl;
    }

    void showDeleteTask()
    {
        cout << "Sterge task" << endl;
        cout << "1. Afisare taskuri" << endl;
        cout << "2. Alege task" << endl;
        cout << "3. Sterge task" << endl;
        cout << "4. Inapoi" << endl;
    }

    void showWorkflow()
    {
        cout << "Afisare workflow" << endl;
        cout << "1. Afisare taskuri" << endl;
        cout << "2. Stergere task" << endl;
        cout << "3. Inapoi" << endl;
    }

    void customTask()
    {
        cout << "Task custom" << endl;
        cout << "1. Ce tip de input doriti sa aiba taskul?" << endl;
        cout << "5. Inapoi" << endl;
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

        int option = 0;
        do
        {
            menu.showStart();
            cout << "Optiunea aleasa: ";
            cin >> option;
            // register
            if (option == 1)
            {
                menu.showRegister();
                int option2 = 0;
                do
                {
                    cout << "Optiunea aleasa: ";
                    cin >> option2;
                    if (option2 == 1)
                    {
                        cout << "Numele este: ";
                    }
                    else if (option2 == 2)
                    {
                        cout << "Emailul este: ";
                    }
                    else if (option2 == 3)
                    {
                        cout << "Numarul de telefon este: ";
                    }
                    else if (option2 == 4)
                    {
                        cout << "Parola este: ";
                    }
                    else if (option2 == 5)
                    {
                        cout << "Inregistrare" << endl;
                    }
                    else if (option2 == 6)
                    {
                        cout << "Inapoi" << endl;
                    }
                    else
                    {
                        cout << "Optiune invalida" << endl;
                    }
                } while (option2 != 6);
            }
            // login
            else if (option == 2)
            {
                menu.showLogin();
                int option2 = 0;
                do
                {
                    cout << "Optiunea aleasa: ";
                    cin >> option2;
                    if (option2 == 1)
                    {
                        cout << "Emailul este: ";
                    }
                    else if (option2 == 2)
                    {
                        cout << "Parola este: ";
                    }
                    else if (option2 == 3)
                    {
                        cout << "Logare" << endl;
                    }
                    else if (option2 == 4)
                    {
                        cout << "Inapoi" << endl;
                    }
                    else
                    {
                        cout << "Optiune invalida" << endl;
                    }
                } while (option2 != 4);
            }
            // run workflow
            else if (option == 3)
            {
                menu.showRunWorkflow();
                int option2 = 0;
                do
                {
                    cout << "Optiunea aleasa: ";
                    cin >> option2;
                    if (option2 == 1)
                    {
                        cout << "Afisare workflows" << endl;
                    }
                    else if (option2 == 2)
                    {
                        cout << "Alege workflow" << endl;
                    }
                    else if (option2 == 3)
                    {
                        cout << "Inapoi" << endl;
                    }
                    else
                    {
                        cout << "Optiune invalida" << endl;
                    }
                } while (option2 != 3);
            }
            // create workflow
            else if (option == 4)
            {
                menu.showCreateWorkflow();
                int option2 = 0;
                do
                {
                    cout << "Optiunea aleasa: ";
                    cin >> option2;
                    if (option2 == 1)
                    {
                        menu.showShoppingListWorkflow();
                        int option3 = 0;
                        do
                        {
                            cout << "Optiunea aleasa: ";
                            cin >> option3;
                            if (option3 == 1)
                            {
                                menu.showAddTask();
                                int option4 = 0;
                                do
                                {
                                    cout << "Optiunea aleasa: ";
                                    cin >> option4;
                                    if (option4 == 1)
                                    {
                                        cout << "Numele taskului este: ";
                                    }
                                    else if (option4 == 2)
                                    {
                                        cout << "Descrierea taskului este: ";
                                    }
                                    else if (option4 == 3)
                                    {
                                        cout << "Taskul are nevoie de un input? (y/n): ";
                                    }
                                    else if (option4 == 4)
                                    {
                                        cout << "Adaugare task" << endl;
                                    }
                                    else if (option4 == 5)
                                    {
                                        cout << "Inapoi" << endl;
                                    }
                                } while (option4 != 5);
                            }
                            else if (option3 == 2)
                            {
                                cout << "Inapoi" << endl;
                            }
                        } while (option3 != 2);
                    }
                    else if (option2 == 2)
                    {
                        menu.showEventWorkflow();
                        int option3 = 0;
                        do
                        {
                            cout << "Optiunea aleasa: ";
                            cin >> option3;
                            if (option3 == 1)
                            {
                                menu.showAddTask();
                                int option4 = 0;
                                do
                                {
                                    cout << "Optiunea aleasa: ";
                                    cin >> option4;
                                    if (option4 == 1)
                                    {
                                        cout << "Numele taskului este: ";
                                    }
                                    else if (option4 == 2)
                                    {
                                        cout << "Descrierea taskului este: ";
                                    }
                                    else if (option4 == 3)
                                    {
                                        cout << "Taskul are nevoie de un input? (y/n): ";
                                    }
                                    else if (option4 == 4)
                                    {
                                        cout << "Adaugare task" << endl;
                                    }
                                    else if (option4 == 5)
                                    {
                                        cout << "Inapoi" << endl;
                                    }

                                } while (option4 != 5);
                            }

                        } while (option3 != 2);
                    }

                    else if (option == 3)
                    {
                        menu.showCustomWorkflow();
                        int option3 = 0;
                        do
                        {
                            if (option3 == 1)
                            {
                                cout << "Cate taskuri doriti sa aiba acest workflow? :" << endl;
                            }
                            else if (option3 == 2)
                            {
                                menu.showAddTask();
                                int option4 = 0;
                                do
                                {
                                    cout << "Optiunea aleasa: ";
                                    cin >> option4;
                                    if (option4 == 1)
                                    {
                                        cout << "Numele taskului este: ";
                                    }
                                    else if (option4 == 2)
                                    {
                                        cout << "Descrierea taskului este: ";
                                    }
                                    else if (option4 == 3)
                                    {
                                        cout << "Taskul are nevoie de un input? (y/n): ";
                                    }
                                    else if (option4 == 4)
                                    {
                                        cout << "Adaugare task" << endl;
                                    }
                                    else if (option4 == 5)
                                    {
                                        cout << "Inapoi" << endl;
                                    }

                                } while (option4 != 5);
                            }

                        } while (option3 != 2);
                    }

                } while (option != 6);
            }
            else if (option == 5)
            {
                menu.showDeleteWorkflow();
                int option2 = 0;
                do
                {
                    cout << "Optiunea aleasa: ";
                    cin >> option2;
                    if (option2 == 1)
                    {
                        cout << "Afisare workflows" << endl;
                    }
                    else if (option2 == 2)
                    {
                        cout << "Alege workflow" << endl;
                    }
                    else if (option2 == 3)
                    {
                        menu.showDeleteTask();
                        int option3 = 0;
                        do
                        {
                            cout << "Optiunea aleasa: ";
                            cin >> option3;
                            if (option3 == 1)
                            {
                                cout << "Afisare taskuri" << endl;
                            }
                            else if (option3 == 2)
                            {
                                cout << "Alege task" << endl;
                            }
                            else if (option3 == 3)
                            {
                                cout << "Sterge task" << endl;
                            }
                            else if (option3 == 4)
                            {
                                cout << "Inapoi" << endl;
                            }
                        } while (option3 != 4);
                    }
                    else if (option2 == 4)
                    {
                        cout << "Inapoi" << endl;
                    }
                } while (option2 != 4);
            }
            else if (option == 6)
            {
                menu.showExit();
            }
        } while (option != 6);
    };

private:
    Menu menu;
};

int main()
{
    App app;
    app.run();
    return 0;
}
