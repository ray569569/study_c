#include<iostream>
#include<iomanip>
using namespace std;

int main()
{

    double population;
    cout << "Enter the starting number of organisms: ";
    cin >> population;
    if (population < 2)
    {
        cout << "Invalid starting number of organisms." << endl;
        return 1;
    }
    double dailyIncrease;
    cout << "Enter the average daily population increase as a percentage: ";
    cin >> dailyIncrease;
    if (dailyIncrease < 0)
    {
        cout << "Invalid daily population increase." << endl;
        return 1;
    }
    double days;
    cout << "Enter the number of days they will multiply: ";
    cin >> days;
    if (days < 1)
    {
        cout << "Invalid number of days." << endl;
        return 1;
    }
    cout << "Day" << setw(20) << "Population" << endl;
    cout << "-------------------------" << endl;
    for (int i = 0; i < days; i++)
    {
        population = population * (1 + dailyIncrease / 100);
        cout << i + 1 << setw(20) << population << endl;
    }
    return 0;
}