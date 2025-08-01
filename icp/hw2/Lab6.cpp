#include <iostream>
using namespace std;

int main() {
    double a, b, c;
    cout << "please enter the ticket sold for class A: ";
    cin >> a;
    cout << "please enter the ticket sold for class B: ";
    cin >> b;
    cout << "please enter the ticket sold for class C: ";
    cin >> c;
    cout << "The income generated from all class: " << (a * 15.00 + b * 12.00 + c * 9.00) << endl;
    return 0;
}