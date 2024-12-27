#include <iostream>
using namespace std;

int main() {
    int seconds;
    cout << "Enter number of seconds: ";
    cin >> seconds;

    if (seconds >= 86400) 
        cout << "Days: " << seconds / 86400 << endl;
    else if (seconds >= 3600) 
        cout << "Hours: " << seconds / 3600 << endl;
    else if (seconds >= 60) 
        cout << "Minutes: " << seconds / 60 << endl;
    else 
        cout << "Seconds: " << seconds << endl;
    return 0;
}
