#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int totalSuites = 0;
    int totalOccupied = 0;
    for (int i = 10; i <= 16; i++)
    {
        if(i == 13)
        {
            continue;
        }
        for (int j = 0; j < 1; j++)
        {
            int suites;
            cout << "Enter the number of suites occupied on floor " << i << ": ";
            cin >> suites;
            if (suites < 0 || suites > 20)
            {
                cout << "Invalid number of suites." << endl;
                j--;
            }
            else
            {
                totalSuites += 20;
                totalOccupied += suites;
            }
        }
    }
    cout << "Total suites: " << totalSuites << endl;
    cout << "Total occupied: " << totalOccupied << endl;
    cout << "Occupancy rate: " << fixed << setprecision(2) << (double)totalOccupied / totalSuites * 100 << "%" << endl;
    return 0;
}