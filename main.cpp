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
        cout << "5. Iesire" << endl;
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
    }

    void showCreateWorkflow()
    {
        cout << "Sa incepem!" << endl;
        cout << "Ce tip de workflow doriti sa creati?" << endl;
        cout << "1. Workflow tip reteta" << endl;
        cout << "2. Workflow tip lista de cumparaturi" << endl;
        cout << "3. Workflow tip organizare eveniment" << endl;
        cout << "4. Workflow custom" << endl;
        cout << "5. Inapoi" << endl;
    }

    void showRecipeWorkflow()
    {
        cout << "Workflow ales este de tip reteta" << endl;
        cout << "1. Adaugare nume " << endl;
        cout << "2. Adaugare ingrediente " << endl;
        cout << "3. Adaugare pasi " << endl;
        cout << "4. Adaugare timp de preparare " << endl;
    }

    void showShoppingListWorkflow()
    {
        cout << "Workflow tip lista de cumparaturi" << endl;
    }

    void showEventWorkflow()
    {
        cout << "Workflow tip organizare eveniment" << endl;
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
            cout << "Optiunea ta: ";
            cin >> option;

            switch (option)
            {
            case 1:
                cout << "Inregistrare" << endl;
                break;
            case 2:
                cout << "Logare" << endl;
                break;
            case 3:
                cout << "Rulare workflow" << endl;
                break;
            case 4:
                cout << "Creare workflow" << endl;
                break;
            case 5:
                cout << "Iesire" << endl;
                break;
            default:
                cout << "Optiune invalida" << endl;
                break;
            }
        } while (option != 5);
    }

private:
    Menu menu;
};

int main()
{
    App app;

    return 0;
}
