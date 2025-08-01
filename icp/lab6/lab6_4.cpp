#include <ctime>
#include <iostream>
using namespace std;

int main() {
    srand(0);
    int A[2][3];
    int B[3][2];
    int sum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = rand() % 6;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            B[i][j] = rand() % 6;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int k = 0; k < 3; k++) {
            sum += A[i][k] * B[k][i];
        }
    }
    cout << "First Matrix" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Second Matrix" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Sum of the product of the two matrices is: " << sum << endl;
    return 0;
}