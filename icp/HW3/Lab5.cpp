#include <iostream>
using namespace std;

int main() {
    int side;
    cout << "Enter the side length of the square (greater than 2): ";
    cin >> side;

    for (int i = 0; i < side; ++i) {
        for (int j = 0; j < side; ++j) {
            if (i == 0 || i == side - 1 || j == 0 || j == side - 1) {
                cout << "X";
            } else {
                cout << "O";
            }
        }
        cout << endl;
    }

    return 0;
}
