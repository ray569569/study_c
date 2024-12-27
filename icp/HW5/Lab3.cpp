#include <iostream>
using namespace std;

int identical(int arr1[], int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int size;
    cout << "Enter the size of the arrays: ";
    cin >> size;
    int arr1[size], arr2[size];
    cout << "Enter the elements of the first array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr1[i];
    }
    cout << "Enter the elements of the second array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr2[i];
    }
    if (identical(arr1, arr2, size)) {
        cout << "The arrays are identical." << endl;
    } else {
        cout << "The arrays are not identical." << endl;
    }
    return 0;
}