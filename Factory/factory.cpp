#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base class for all pizza types
class Pizza {
public:
    string type;
    virtual void prepare() = 0;
    virtual void bake() = 0;
    virtual void cut() = 0;
    virtual void box() = 0;
};

// Concrete pizza types
class CheesePizza : public Pizza {
public:
    CheesePizza(){
        type="Cheese";
    }
    void prepare() {  cout << "Preparing cheese pizza...\n"; }
    void bake() {  cout << "Baking cheese pizza...\n"; }
    void cut() {  cout << "Cutting cheese pizza...\n"; }
    void box() {  cout << "Boxing cheese pizza...\n"; }
};

class PepperoniPizza : public Pizza {
public:
    PepperoniPizza(){
        type="Pepperoni";
    }
    void prepare() {  cout << "Preparing pepperoni pizza...\n"; }
    void bake() {  cout << "Baking pepperoni pizza...\n"; }
    void cut() {  cout << "Cutting pepperoni pizza...\n"; }
    void box() {  cout << "Boxing pepperoni pizza...\n"; }
};

// Pizza store class
class PizzaStore {
public:
    virtual Pizza* createPizza( string type) = 0;

    Pizza* orderPizza( string type) {
        Pizza* pizza = createPizza(type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};

// Concrete pizza store types
class NYStylePizzaStore : public PizzaStore {
public:
    Pizza* createPizza( string type) {
        if (type == "cheese") {
            return new CheesePizza();
        } else if (type == "pepperoni") {
            return new PepperoniPizza();
        } else {
            return nullptr;
        }
    }
};

class ChicagoStylePizzaStore : public PizzaStore {
public:
    Pizza* createPizza( string type) {
        if (type == "cheese") {
            return new CheesePizza();
        } else if (type == "pepperoni") {
            return new PepperoniPizza();
        } else {
            return nullptr;
        }
    }
};

// Main function
int main() {
    PizzaStore* nyStore = new NYStylePizzaStore();
    PizzaStore* chicagoStore = new ChicagoStylePizzaStore();

    Pizza* pizza = nyStore->orderPizza("cheese");
    cout << "First order: "<< pizza->type<< " pizza" << "\n\n";
    delete pizza;

    pizza = chicagoStore->orderPizza("pepperoni");
    cout << "Second order: "<< pizza->type<<" pizza" << "\n\n";
    delete pizza;

}
