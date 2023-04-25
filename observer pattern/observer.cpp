#include <iostream>
#include <vector>

using namespace std;

//Weather Station
class Observer {    //TV, Phone, Display, ...
    public:
        virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject {     //Weather
    public:
        //Observer register/remove
        virtual void registerObserver(Observer* o) = 0;
        virtual void removeObserver(Observer* o) = 0;
        
        //Notify observers when the subject's state changes
        virtual void notifyObservers() = 0;   
};

class DisplayElement {  //This function is for displaying only
    public:
        virtual void display() = 0;
};

//Subject interface in weatherdata
class WeatherData : public Subject {    //
    private:
        vector<Observer*> observers; //Dynamic array
        float temperature;
        float humidity;
        float pressure;

    public:
        //Create dynamic array to hold the observers
        WeatherData() {
            observers = vector<Observer*>();
        }

        //push_back() adds new element at the then of the vector and increase vector's size by 1
        void registerObserver(Observer* o) {
            observers.push_back(o);
        }

        //Remove targeted observers from register array
        void removeObserver(Observer* o) {
            for (int i = 0; i < observers.size(); i++) {
                if (observers[i] == o) {
                    observers.erase(observers.begin() + i);
                }
            }
        }

        //Notify and update information for the observers
        void notifyObservers() {
            for (int i = 0; i < observers.size(); i++) {
                //CurrentConditionDisplay.update
                observers[i]->update(temperature, humidity, pressure);
            }
        }
        void measurementsChanged() {
            notifyObservers();
        }


        //Set data (for testing code only)
        void setMeasurements(float temperature, float humidity, float pressure) {
            this->temperature = temperature;
            this->humidity = humidity;
            this->pressure = pressure;
            measurementsChanged();
        }
};

//Display
class CurrentConditionsDisplay : public Observer, public DisplayElement { //
    private:
        float temperature;
        float humidity;
        Subject* weatherData;

    public:
        //Register the display as an observer using the imformation from subject
        CurrentConditionsDisplay(Subject* weatherData) {
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
        }

        //Save temperature, humidity and call display()
        void update(float temperature, float humidity, float pressure) {
            this->temperature = temperature;
            this->humidity = humidity;
            display();
        }
        void display() {
            cout << "Current conditions: " << temperature << "F degrees and " << humidity << "% humidity" << endl;
        }
};

class StatisticsDisplay : public Observer, public DisplayElement {
    private:
        float maxTemp;
        float minTemp;
        float tempSum;
        int numReadings;
        Subject* weatherData;
    public:
        StatisticsDisplay(Subject* weatherData) {
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
            maxTemp = 0.0f;
            minTemp = 200.0f;
            tempSum = 0.0f;
            numReadings = 0;
        }
        void update(float temperature, float humidity, float pressure) {
            tempSum += temperature;
            numReadings++;
            if (temperature > maxTemp) {
                maxTemp = temperature;
            }
            if (temperature < minTemp) {
                minTemp = temperature;
            }
            display();
        }
        void display() {
            cout << "Avg/Max/Min temperature = " << (tempSum / numReadings)
                << "/" << maxTemp << "/" << minTemp << endl;
        }
};
class ForecastDisplay : public Observer, public DisplayElement {
    private:
        float currentPressure = 29.92f;
        float lastPressure;
        Subject* weatherData;
    public:
        ForecastDisplay(Subject* weatherData) {
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
            currentPressure;
            lastPressure = 0.0f;
        }
        void update(float temperature, float humidity, float pressure) {
            lastPressure = currentPressure;
            currentPressure = pressure;
            display();
        }
        void display() {
            cout << "Forecast: ";
            if (currentPressure > lastPressure) {
                cout << "Better weather" << endl;
            } else if (currentPressure == lastPressure) {
                cout << "Same" << endl;
            } else if (currentPressure < lastPressure) {
                cout << "Rainy weather" << endl;
            }
            cout << endl;
        }
};

int main() {
    WeatherData* weatherData = new WeatherData();
    CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);
    StatisticsDisplay* statisticsDisplay = new StatisticsDisplay(weatherData);
    ForecastDisplay* forecastDisplay = new ForecastDisplay(weatherData);

    //temp, humidity, pressure
    weatherData->setMeasurements(80, 65, 30.4f);
    weatherData->setMeasurements(82, 70, 29.2f);
    weatherData->setMeasurements(78, 90, 29.2f);

    delete weatherData;
    delete currentDisplay;
    delete statisticsDisplay;
    delete forecastDisplay;

    return 0;
}
