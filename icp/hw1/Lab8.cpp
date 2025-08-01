#include<iostream>
using namespace std;

int main()
{
    char input;
    do {
    cout << "Please enter 'Y' or 'N': ";
    cin >> input;
    if (input != 'Y' && input != 'N') {
        cout << "Invalid entry. Please try again." << endl;
    }
} while (input != 'Y' && input != 'N');
    return 0;
}