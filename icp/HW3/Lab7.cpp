#include <iostream>
using namespace std;

int main() {
    double cost;
    cout << "Enter the initial cost of the car: ";
    cin >> cost;

    for (int year = 1; year <= 10; ++year) {
        if (year == 1) 
            cost *= 0.8;  
        else if (year == 2) 
            cost *= 0.85;  
        else 
            cost *= 0.9;   
        cout << "Value of the car after year " << year << ": $" << cost << endl;
    }

    return 0;
}
