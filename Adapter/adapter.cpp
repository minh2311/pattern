#include <iostream>
using namespace std;

class Duck
{
public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class MallardDuck : public Duck
{
public:
    void quack() override
    {
        cout << "Quack\n";
    }

    void fly() override
    {
        cout << "I'm flying\n";
    }
};

class Turkey
{
public:
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

class WildTurkey : public Turkey
{
public:
    void gobble() override
    {
        cout << "Gobble gobble\n";
    }

    void fly() override
    {
        cout << "I'm flying a short distance\n";
    }
};

class TurkeyAdapter : public Duck, public WildTurkey
{
public:
    void quack() override
    {
        gobble();
    }

    void fly() override
    {
        for (int i = 0; i < 5; i++)
        {
            WildTurkey::fly();
        }
    }
};

int main()
{
    MallardDuck *duck = new MallardDuck();
    WildTurkey *turkey = new WildTurkey();
    Duck *turkeyAdapter = new TurkeyAdapter();

    cout << "The Turkey says...\n";
    turkey->gobble();
    turkey->fly();
    cout << "\nThe Duck says...\n";
    duck->quack();
    duck->fly();
    cout << "\nThe TurkeyAdapter says...\n";
    turkeyAdapter->quack();
    turkeyAdapter->fly();

    delete duck;
    delete turkey;
    delete turkeyAdapter;

    return 0;
}
