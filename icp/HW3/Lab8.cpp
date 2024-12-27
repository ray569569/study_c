#include <iostream>
using namespace std;

double calculateRetail(double wholesaleCost, double markupPercentage) {
    return wholesaleCost + (wholesaleCost * markupPercentage / 100);
}

int main() {
    double wholesaleCost, markupPercentage;
    cout << "Enter wholesale cost: ";
    cin >> wholesaleCost;
    cout << "Enter markup percentage: ";
    cin >> markupPercentage;

    double retailPrice = calculateRetail(wholesaleCost, markupPercentage);
    cout << "The retail price is: $" << retailPrice << endl;

    return 0;
}
