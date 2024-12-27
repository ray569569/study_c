#include <iostream>
using namespace std;

int count(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 50) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[10];
    for (int i = 0; i < 10; i++) {
        cout << "Enter percentage of student " << i + 1 << ": ";
        cin >> arr[i];
    }
    cout << count(arr, 10) << " students have obtained more than 50 percent." << endl;
    return 0;
}