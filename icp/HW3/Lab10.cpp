#include <iostream>
using namespace std;

bool isLeap(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int main() {
    int year, holidays;
    cout << "Enter the year: ";
    cin >> year;
    cout << "Enter the number of national holidays: ";
    cin >> holidays;

    int totalDays = isLeap(year) ? 366 : 365;
    int workingDays = totalDays - holidays - 52;  

    cout << "Total days: " << totalDays << endl;
    cout << "National holidays: " << holidays << endl;
    cout << "Working days: " << workingDays << endl;

    return 0;
}
