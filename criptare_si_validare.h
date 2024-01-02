#ifndef CRIPTAREANDVALIDARE_H
#define CRIPTAREANDVALIDARE_H
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <valarray>
#include <cmath>
using namespace std;

class CriptareAndValidare
{
public:
    string criptare(string text, int key1, int key2);

    vector<int> menu();

    void validareMail(string email);

    void validareParola(string text);

    void validareTelefon(string text);

    string formatareData(string data);

    void verificareOra(string ora1, string ora2);

    void validareData(string text);

    void validareOra(string text);
};

#endif