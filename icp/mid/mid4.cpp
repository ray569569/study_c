#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "please input display range: ";
    cin >> n;
    for (int i = 0; i < n * 2 - 1; i++) {
        int count = n;
        for (int j = 0; j < 2 * n - 1; j++) {
            if (i < n) {
                if (j < i)
                    cout << count--;
                else if (j < 2 * n - 1 - i)
                    cout << count;
                else
                    cout << ++count;
            } else {
                if (j < 2 * n - 1 - i - 1)
                    cout << count--;
                else if (j <= i)
                    cout << count;
                else
                    cout << ++count;
            }
        }
        cout << endl;
    }
    return 0;
}