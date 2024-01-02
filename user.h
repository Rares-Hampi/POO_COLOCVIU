#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class User
{

private:
    string nume;
    string phone;
    string email;
    string parola;

public:
    User();

    void setNume(string nume);

    void setEmail(string email);

    void setParola(string parola);

    void setPhone(string phone);

    string getNume();

    string getPhone();

    string getEmail();

    string getParola();

    void checkData();

    void deleteData();

    void Register(string nume, string email, string parola, string phone);

    void Login(string email, string parola);

    void getData(string email);

    void Logout();

    void Edit(string filepath, string oldValue, string newValue, string email);

    void EditEmail(string email, string newEmail);

    void EditPhone(string email, string newPhone);

    void rezervareRuta(string name, string email);

    void anulareRezervare(string name, string email);

    void getRezervari(string email);
};

#endif
