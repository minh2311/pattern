#include <iostream>
using namespace std;

// Base drink interface
class Drink {
public:
    virtual int getCost() = 0;
    virtual string getDescription() = 0;
};

// Concrete drink classes
class Espresso : public Drink {
public:
    int getCost() {
        return 100;
    }
    string getDescription() {
        return "Espresso";
    }
};

class Americano : public Drink {
public:
    int getCost() {
        return 120;
    }
    string getDescription() {
        return "Americano";
    }
};

// Decorator abstract class
class DrinkDecorator : public Drink {
public:
    Drink* drink;

    DrinkDecorator(Drink* drink) {
        this->drink = drink;
    }

    int getCost() {
        return drink->getCost();
    }

    string getDescription() {
        return drink->getDescription();
    }
};

// Concrete decorator classes
class Milk : public DrinkDecorator {
public:
    Milk(Drink* drink) : DrinkDecorator(drink) {}

    int getCost() {
        return drink->getCost() + 20;
    }

    string getDescription() {
        return drink->getDescription() + ", Milk";
    }
};

class Sugar : public DrinkDecorator {
public:
    Sugar(Drink* drink) : DrinkDecorator(drink) {}

    int getCost() {
        return drink->getCost() + 10;
    }

    string getDescription() {
        return drink->getDescription() + ", Sugar";
    }
};

class Cinnamon : public DrinkDecorator {
public:
    Cinnamon(Drink* drink) : DrinkDecorator(drink) {}

    int getCost() {
        return drink->getCost() + 15;
    }

    string getDescription() {
        return drink->getDescription() + ", Cinnamon";
    }
};

int main() {
    // Create base drinks
    Drink* espresso = new Espresso();
    Drink* americano = new Americano();

    // Add decorators
    espresso = new Milk(espresso);
    americano = new Sugar(new Cinnamon(americano));

    // Print cost and description
    cout << "Description: " << espresso->getDescription() << endl;
    cout << "Cost: " << espresso->getCost() << endl;
      
    cout << "Description: " << americano->getDescription() << endl;
    cout << "Cost: " << americano->getCost() << endl;
}
