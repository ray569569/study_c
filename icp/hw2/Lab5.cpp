#include <iostream>
using namespace std;

int main() {
    double input;
    cout << "please enter a number: ";
    cin >> input;
    cout << "There are " << input / 4.546 << " gallons" << endl;
    cout << "It cost " << (input / 4.546) * 1.99 << " dollars" << endl;
    return 0;
}