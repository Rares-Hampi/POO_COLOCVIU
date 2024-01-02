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

void CriptareAndValidare::validareData(string text)
{
    string text1 = text;
    text1.erase(std::remove(text1.begin(), text1.end(), '-'), text1.end());

    regex pattern("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$");
    if (!regex_match(text, pattern))
    {
        throw "Data invalida";
    }

    std::istringstream iss(text);
    int day, month, year;
    char delimiter;
    iss >> year >> delimiter >> month >> delimiter >> day;
    std::ostringstream oss;
    oss << year << "-" << month << "-" << day;
    text = oss.str();

    time_t t = time(0);
    struct tm *now = localtime(&t);
    int yearNow = now->tm_year + 1900;
    int monthNow = now->tm_mon + 1;
    int dayNow = now->tm_mday;

    if (year < yearNow)
    {
        throw "Data invalida, anul nu poate fi mai mic decat anul curent";
    }
    else if (year >= yearNow)
    {
        if (month < monthNow)
        {
            throw "Data invalida, luna nu poate fi mai mica decat luna curenta";
        }
        else if (month >= monthNow)
        {
            if (day < dayNow)
            {
                throw "Data invalida, ziua nu poate fi mai mica decat ziua curenta";
            }
        }
    }
}

string CriptareAndValidare::formatareData(string data)
{

    std::istringstream iss(data);
    int year, month, day;
    char delimiter;
    iss >> year >> delimiter >> month >> delimiter >> day;
    std::ostringstream oss;
    oss << year << "-" << month << "-" << day;
    data = oss.str();
    cout << data;
    return data;
}

void CriptareAndValidare::validareOra(string text)
{
    regex pattern("^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
    if (!regex_match(text, pattern))
    {
        throw "Ora invalida";
    }
}

void CriptareAndValidare::verificareOra(string ora1, string ora2)
{
    int ora1Int = stoi(ora1.substr(0, 2));
    int ora2Int = stoi(ora2.substr(0, 2));
    int minute1Int = stoi(ora1.substr(3, 2));
    int minute2Int = stoi(ora2.substr(3, 2));
    if (ora1Int > ora2Int)
    {
        throw "Ora de plecare trebuie sa fie mai mica decat ora de sosire. Te rugam sa modifici ora de sosire sau ora de plecare";
    }
    else if (ora1Int == ora2Int)
    {
        if (minute1Int > minute2Int)
        {
            throw "Ora de plecare trebuie sa fie mai mica decat ora de sosire. Te rugam sa modifici ora de sosire sau ora de plecare";
        }
    }
}