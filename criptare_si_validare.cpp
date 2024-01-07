#include "criptare_si_validare.h"

vector<int> CriptareAndValidare::menu()
{
    vector<int> keys;
    cout << "Care este sportul tau preferat?" << endl;
    cout << "1. Fotbal" << endl;
    cout << "2. Tenis" << endl;
    cout << "3. Baschet" << endl;
    cout << "4. Handbal" << endl;

    string error = "Optiune invalida";

    try
    {
        do
        {
            int option;
            cout << "Optiunea ta: ";
            cin >> option;

            if (option == 1)
            {
                keys.push_back(17);
                keys.push_back(31);
                error = "";
                return keys;
            }
            else if (option == 2)
            {
                keys.push_back(19);
                keys.push_back(37);
                error = "";
                return keys;
            }
            else if (option == 3)
            {
                keys.push_back(23);
                keys.push_back(41);
                error = "";
                return keys;
            }
            else if (option == 4)
            {
                keys.push_back(29);
                keys.push_back(43);
                error = "";
                return keys;
            }
            else
            {
                error = "Optiune invalida";
            }
        }

        while (error.length() > 0);
    }
    catch (const string &e)
    {
        throw e;
    }
    return keys;
}

bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

string CriptareAndValidare::criptare(string text, int key1, int key2)
{
    int n, e;
    n = key1 * key2;
    int phi = (key1 - 1) * (key2 - 1);
    e = 2;
    for (e = 2; e < phi; e++)
    {
        if (gcd(e, phi) == 1)
            break;
    }
    int d = 2;
    for (d = 2; d < phi; d++)
    {
        if ((d * e) % phi == 1)
            break;
    }

    string encryptedMessage = "";

    for (char c : text)
    {
        int m = c;
        int encryptedChar = pow(m, e);
        encryptedChar %= n;
        encryptedMessage += to_string(encryptedChar) + " ";
    }
    return encryptedMessage;
}

void CriptareAndValidare::validareMail(string email)
{
    regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if (!regex_match(email, pattern))
    {
        throw "Email invalid";
    }
}

void CriptareAndValidare::validareParola(string text)
{
    regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    if (!regex_match(text, pattern))
    {
        throw "Parola invalida. Aceasta trebuie sa contina minim 8 caractere, o litera din intervalul A-Z si un numar";
    }
}

void CriptareAndValidare::validareTelefon(string text)
{
    regex pattern("^(07[0-9]{8})$");
    if (!regex_match(text, pattern))
    {

        throw "Telefon invalid";
    }
}
