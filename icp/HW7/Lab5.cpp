#include <iostream>
#include <string>
using namespace std;

class Car
{
private:
    int year;
    string make;
    int speed;

public:
    Car(int y, string m)
    {
        year = y;
        make = m;
        speed = 0;
    }
    int getYear()
    {
        return year;
    }
    string getMake()
    {
        return make;
    }
    int getSpeed()
    {
        return speed;
    }
    void accelerate()
    {
        speed += 5;
    }
    void brake()
    {
        speed -= 5;
    }
};

int main()
{
    int y;
    string m;
    int initialSpeed;
    cout << "Enter the car's year, make, and initial speed separated by commas: ";
    char comma;
    cin >> y >> comma >> ws;
    getline(cin, m, ',');
    cin >> initialSpeed;

    Car c(y, m);
    
    for (int i = 0; i < (initialSpeed / 5); i++)
    {
        c.accelerate();
    }

    cout << "I'm in my " << c.getYear() << " " << c.getMake() << " hot rod." << endl;
    cout << "I'm accelerating ..." << endl;
    for (int i = 0; i < 5; i++)
    {
        c.accelerate();
        cout << "Current speed: " << c.getSpeed() << " mph." << endl;
    }
    cout << "Now I'm braking ..." << endl;
    for (int i = 0; i < 5; i++)
    {
        c.brake();
        cout << "Current speed: " << c.getSpeed() << " mph." << endl;
    }
    return 0;
}
