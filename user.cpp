#include "user.h"
#include "criptare_si_validare.h"

User::User()
{
    nume = "";
    phone = "";
    email = "";
    parola = "";
}

void User::setNume(string nume)
{
    try
    {
        if (nume.length() < 4)
        {
            throw "Numele trebuie să aibă cel puțin 3 caractere.";
        }
        this->nume = nume;
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::setEmail(string email)
{

    CriptareAndValidare validare;
    try
    {
        validare.validareMail(email);
        this->email = email;
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::setPhone(string phone)
{

    CriptareAndValidare validare;
    try
    {
        validare.validareTelefon(phone);
        this->phone = phone;
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::setParola(string parola)
{

    vector<int> keys;
    CriptareAndValidare validareSiCriptare;
    try
    {
        validareSiCriptare.validareParola(parola);
        keys = validareSiCriptare.menu();
        try
        {
            try
            {
                if (keys.size() != 2)
                {
                    throw "Nu s-au putut genera cheile";
                }
                validareSiCriptare.criptare(parola, keys[0], keys[1]);
                parola = validareSiCriptare.criptare(parola, keys[0], keys[1]);
            }
            catch (const char *e)
            {
                throw e;
            }

            this->parola = parola;
        }
        catch (const char *e)
        {
            throw e;
        }
    }
    catch (const char *e)
    {
        throw e;
    }
}

string User::getNume()
{
    return this->nume;
}

string User::getPhone()
{
    return this->phone;
}

string User::getEmail()
{
    return this->email;
}

string User::getParola()
{
    return this->parola;
}

void User::checkData()
{
    try
    {
        if (nume.empty())
        {

            throw "Numele nu este setat";
        }
        if (email.empty())
        {
            throw "Emailul nu este setat";
        }
        if (parola.empty())
        {
            throw "Parola nu este setata";
        }
        if (phone.empty())
        {
            throw "Telefonul nu este setat";
        }
    }
    catch (const char *e)
    {

        throw e;
    }
}

void User::deleteData()
{
    nume = "";
    email = "";
    parola = "";
    phone = "";
}

void User::Register(string nume, string email, string parola, string phone)
{

    try
    {

        checkData();
        ofstream file;
        file.open("./csv/conturi.csv", ios::app);
        if (file.is_open())
        {
            file << email << "," << nume << "," << parola << "," << phone << ","
                 << "inregistrat"
                 << ","
                 << "user" << endl;
            file.close();

            deleteData();
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::Login(string email, string parola)
{

    try
    {
        if (email.empty() || parola.empty())
        {
            throw "Nu s-au introdus datele";
        }

        ifstream file;
        file.open("./csv/conturi.csv");
        if (file.is_open())
        {
            string errorMessage;
            string line;
            while (getline(file, line))
            {

                stringstream ss(line);
                string storedEmail;
                string storedPassword;
                string storedStatus;

                getline(ss, storedEmail, ',');

                for (int i = 0; i < 2; i++)
                {
                    getline(ss, storedPassword, ',');
                }

                for (int i = 0; i < 2; i++)
                {
                    getline(ss, storedStatus, ',');
                }

                if (storedEmail == email)
                {
                    errorMessage = "";

                    if (storedPassword == parola)
                    {
                        errorMessage = "";

                        if (storedStatus == "inregistrat")
                        {

                            errorMessage = "";
                            Edit("./csv/conturi.csv", "inregistrat", "logat", email);
                            break;
                            return;
                        }
                        else
                        {

                            errorMessage = "Cont deja logat";
                        }
                    }
                    else
                    {

                        errorMessage = "Parola incorecta";
                    }
                }
                else
                {
                    errorMessage = "Nu exista un cont inregistrat cu acest email";
                }
            }
            if (errorMessage.length() > 0)
            {
                throw errorMessage;
            }

            file.close();
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::getData(string email)
{
    try
    {
        ifstream file;
        file.open("./csv/conturi.csv");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string storedEmail;
                string storedName;
                string storedPassword;
                string storedPhone;
                string storedStatus;
                string storedType;

                getline(ss, storedEmail, ',');
                getline(ss, storedName, ',');
                getline(ss, storedPassword, ',');
                getline(ss, storedPhone, ',');

                if (storedEmail == email)
                {
                    this->email = storedEmail;
                    this->nume = storedName;
                    this->parola = storedPassword;
                    this->phone = storedPhone;
                    break;
                }
            }
            file.close();
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::Logout()
{

    try
    {

        Edit("./csv/conturi.csv", "logat", "inregistrat", this->email);
        deleteData();
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::Edit(string filePath, string oldValue, string newValue, string email)
{
    try
    {
        ifstream file(filePath);
        ofstream tempFile("./csv/temp.csv");
        string line;

        if (file.is_open() && tempFile.is_open())
        {
            while (getline(file, line))
            {
                size_t pos = line.find(oldValue);
                size_t posEmail = line.find(email);
                if (pos != string::npos && posEmail != string::npos)
                {
                    line.replace(pos, oldValue.length(), newValue);
                }
                tempFile << line << endl;
            }
            file.close();
            tempFile.close();
            remove(filePath.c_str());
            rename("./csv/temp.csv", filePath.c_str());
            getData(email);
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::EditEmail(string email, string newEmail)
{

    try
    {

        Edit("./csv/conturi.csv", email, newEmail, email);
        this->email = newEmail;
    }
    catch (const char *e)
    {
        throw e;
    }
}

void User::EditPhone(string email, string newPhone)
{

    try
    {

        Edit("./csv/conturi.csv", this->phone, newPhone, email);
        this->phone = newPhone;
    }
    catch (const char *e)
    {
        throw e;
    }
}
