#include "user.h"
#include "criptare_si_validare.h"

Utilizator::Utilizator()
{
    nume = "";
    phone = "";
    email = "";
    parola = "";
}

void Utilizator::setNume(string nume)
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

void Utilizator::setEmail(string email)
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

void Utilizator::setPhone(string phone)
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

void Utilizator::setParola(string parola)
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

string Utilizator::getNume()
{
    return this->nume;
}

string Utilizator::getPhone()
{
    return this->phone;
}

string Utilizator::getEmail()
{
    return this->email;
}

string Utilizator::getParola()
{
    return this->parola;
}

void Utilizator::checkData()
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

void Utilizator::deleteData()
{
    nume = "";
    email = "";
    parola = "";
    phone = "";
}

void Utilizator::Register(string nume, string email, string parola, string phone)
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

void Utilizator::Login(string email, string parola)
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

void Utilizator::getData(string email)
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

void Utilizator::Logout()
{
    Operator admin;
    try
    {
        admin.getStatus(this->email);
        Edit("./csv/conturi.csv", "logat", "inregistrat", this->email);
        deleteData();
    }
    catch (const char *e)
    {
        throw e;
    }
}

void Utilizator::Edit(string filePath, string oldValue, string newValue, string email)
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

void Utilizator::EditEmail(string email, string newEmail)
{
    Operator admin;
    try
    {

        admin.getExistenceMail(newEmail);
        Edit("./csv/conturi.csv", email, newEmail, email);
        this->email = newEmail;
    }
    catch (const char *e)
    {
        throw e;
    }
}

void Utilizator::EditPhone(string email, string newPhone)
{
    Operator admin;
    try
    {
        admin.getExistencePhone(newPhone);
        Edit("./csv/conturi.csv", this->phone, newPhone, email);
        this->phone = newPhone;
    }
    catch (const char *e)
    {
        throw e;
    }
}

void Utilizator::rezervareRuta(string nume, string email)
{
    Operator admin;

    try
    {

        if (stoi(admin.getRutaLocuri(nume)) < 1)
        {
            throw "Nu mai sunt locuri disponibile";
        }

        ifstream file;
        file.open("./csv/rute.csv");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);

                string storedLocuri;
                string storedName;
                getline(ss, storedName, ',');
                for (int i = 0; i < 6; i++)
                {
                    getline(ss, storedLocuri, ',');
                }

                if (storedName == nume)
                {
                    if (stoi(storedLocuri) > 0)
                    {
                        ofstream file1;
                        file1.open("./csv/rezervari.csv", ios::app);
                        if (file1.is_open())
                        {
                            file1 << nume << "," << email << endl;
                            file1.close();
                        }
                        else
                        {
                            throw "Nu s-a putut deschide fisierul";
                        }
                        admin.updateRuta(nume, "locuri", to_string(stoi(storedLocuri) - 1));

                        break;
                    }
                    else
                    {
                        throw "Nu mai sunt locuri disponibile";
                    }
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

void Utilizator::anulareRezervare(string name, string email)
{
    Operator admin;
    try
    {
        ifstream file("./csv/rezervari.csv");
        ofstream temp("./csv/temp2.csv", ios::app);
        if (file.is_open() && temp.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string storedName;
                string storedEmail;

                getline(ss, storedName, ',');
                getline(ss, storedEmail, ',');

                if (storedName == name && storedEmail == email)
                {
                    cout << "Rezervarea a fost anulata" << endl;
                    admin.updateRuta(name, "locuri", to_string(stoi(admin.getRutaLocuri(name)) + 1));
                }
                else
                {
                    temp << line << endl;
                }
            }
            file.close();
            temp.close();
        }
        else
        {
            throw "Nu s-a putut deschide fisierul";
        }
        remove("./csv/rezervari.csv");
        rename("./csv/temp2.csv", "./csv/rezervari.csv");
    }
    catch (const char *e)
    {
        throw e;
    }
}

void Utilizator::getRezervari(string email)
{
    Operator admin;

    try
    {
        ifstream file;
        file.open("./csv/rezervari.csv");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string storedName;
                string storedEmail;

                getline(ss, storedName, ',');
                getline(ss, storedEmail, ',');

                if (storedEmail == email)
                {
                    admin.getRuta(storedName);
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
