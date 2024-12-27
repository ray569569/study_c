#include <iostream>
using namespace std;

int main() {
    double server[7][2];
    double total = 0;
    for (int i = 0; i < 7; i++) {
        cout << "Enter the number of hours worked on day " << i + 1 << ": ";
        cin >> server[i][0];
        server[i][1] = server[i][0] * 7.45;
        total += server[i][1];
    }
    cout << "Earnings report:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Day " << i + 1 << ": " << server[i][1] << endl;
    }
    cout << "Total earnings for the week: " << total << endl;
    cout << "Average earnings in a day: " << total / 7 << endl;
    cout << "Projected monthly income: " << total * 30 << endl;
    return 0;
}