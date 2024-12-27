#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    double inflationRate;
    cout << "Enter the annual rate of inflation between 1 and 10 percent: ";
    cin >> inflationRate;
    if (inflationRate < 1 || inflationRate > 10)
    {
        cout << "Invalid rate of inflation." << endl;
        return 1;
    }
    cout << "Year" << setw(20) << "Value" << endl;
    cout << "-------------------------" << endl;
    double value = 1000;
    for (int i = 0; i < 10; i++)
    {
        value = value / (1 + inflationRate / 100);
        cout << i + 1 << setw(20) << value << endl;
    }
    return 0;
}