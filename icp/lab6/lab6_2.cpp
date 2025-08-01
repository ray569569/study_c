#include <iostream>
using namespace std;

int main() {
    int arr[4][4];
    int counter = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = counter++;
            ;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    int n;
    cout << "Enter the number of rotations: ";
    cin >> n;
    counter = 0;
    int temp[4][4];
    int type;
    while (counter < n) {
        cout << "Enter the type of rotation: ";
        cin >> type;
        if (type == 1) 
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    temp[3 - j][i] = arr[i][j];
                }
            }
        }
        else
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    temp[j][3 - i] = arr[i][j];
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << temp[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                arr[i][j] = temp[i][j];
                ;
            }
        }
        counter++;
    }
    return 0;
}