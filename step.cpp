#include "step.h"

template <typename T>
Step<T>::Step(string nume, string description, bool input, T type_input)
{
    this->nume = nume;
    this->description = description;
    this->input = input;
    this->type_input = type_input;
}

template <typename T>
string Step<T>::getNume()
{
    return this->nume;
}

template <typename T>
string Step<T>::getDescription()
{
    return this->description;
}

template <typename T>
bool Step<T>::getInput()
{
    return this->input;
}

template <typename T>
T Step<T>::getTypeInput()
{
    return this->type_input;
}

template <typename T>
void Step<T>::setNume(string nume)
{
    this->nume = nume;
}

template <typename T>
void Step<T>::setDescription(string description)
{
    this->description = description;
}

template <typename T>
void Step<T>::setInput(bool input)
{
    this->input = input;
}

template <typename T>
void Step<T>::setTypeInput(T type_input)
{
    this->type_input = type_input;
}

template <typename T>
void Step<T>::print()
{
    cout << "Nume: " << this->nume << endl;
    cout << "Descriere: " << this->description << endl;
    cout << "Input: " << this->input << endl;
    cout << "Tip input: " << type(type_input) << endl;
}

template <typename T>
void Step<T>::printInput()
{
    if (this->input == true)
    {
        cout << "Introduceti " << this->description << ": ";
        cin >> this->type_input;
    }
}

template <typename T>
void Step<T>::addStep(string nume, string description, bool input, T type_input)
{
    ofstream file;
    file.open("steps.txt", ios::app);
    file << nume << endl;
    file << description << endl;
    file << input << endl;
    if (input == true)
    {
        file << type_input << endl;
    }
    else
    {
        file << "0" << endl;
    }

    file.close();
}