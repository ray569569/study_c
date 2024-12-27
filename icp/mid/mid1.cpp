#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int j = 0; j < 2 * n - 1; j++) {
        if (j < n) {
            for (int k = 0; k < j; k++) {
                cout << " ";
            }
            for (int k = j; k < n; k++) {
                cout << "*";
            }
        } 
        else {
            for (int k = 0; k < n-1; k++) {
                cout << " ";
            }
            for (int k = n; k < j+2; k++) {
                cout << "*";
            }
        }
        cout << endl;
    }

    return 0;
}