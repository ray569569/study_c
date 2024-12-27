#include <windows.h>

#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    int a, b;
    int Min, Max;
    cin >> a >> b;
    if (a < 0 || b < 0) {
        cout << "Please input positive number" << endl;
        return 0;
    }

    for (int i = 1; i < max(a, b); i++) {
        if (a % i == 0 && b % i == 0) {
            Max = i;
        }
    }
    Min = -1;
    int j = max(a, b);
    while (Min < 0) {
        if (j % a == 0 && j % b == 0) {
            Min = j;
        }
        j++;
    }
    cout << "A and B GCD is:" << Max << endl;
    cout << "A and B LCM is:" << Min << endl;
    return 0;
}