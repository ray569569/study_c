#include<iostream>
using namespace std;

void CelsiusToFahrenheit(float &celsius)
{
    float fahrenheit = (celsius * 9.0) / 5.0 + 32;
    cout << "Temperature in Fahrenheit is: " << fahrenheit << endl;
}
void FahrenheitToCelsius(float &fahrenheit)
{
    float celsius = (fahrenheit - 32) * 5.0 / 9.0;
    cout << "Temperature in Celsius is: " << celsius << endl;
}
int main()
{
    float input;
    for(int i=0;i<5;i++)
    {
        cout << "Enter temperature in Fahrenheit: ";
        cin >> input;
        FahrenheitToCelsius(input);
        cout<<input<<"°C "<<endl;
        cout << "Enter temperature in Celsius: ";
        cin >> input;
        CelsiusToFahrenheit(input);
        cout<<input<<"°F "<<endl;
    }
    return 0;
}