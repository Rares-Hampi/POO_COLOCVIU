#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Observer
{
public:
    virtual void start() = 0;
    virtual void complete() = 0;
    virtual void skip() = 0;
    virtual void fail() = 0;
    virtual void averageFail() = 0;

protected:
    string name;
    int started;
    int skipped;
    int failed;
    int completed;
    int averageFailed;
};

class Analytics : public Observer
{
public:
    Analytics()
    {
        this->name = "";
        this->started = 0;
        this->skipped = 0;
        this->failed = 0;
        this->completed = 0;
        this->averageFailed = 0;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void start()
    {
        this->started++;
    }

    void complete()
    {
        this->completed++;
    }

    void skip()
    {
        this->skipped++;
    }

    void fail()
    {
        this->failed++;
    }

    void averageFail()
    {
        this->averageFailed = this->failed / this->started;
    }

    int returnSkips()
    {
        return this->skipped;
    }

    void print()
    {
        ofstream file;
        file.open("analytics.csv", ios::app);
        file << this->name << "," << this->started << "," << this->completed << "," << this->skipped << "," << this->failed << "," << this->averageFailed << endl;
    }
};
