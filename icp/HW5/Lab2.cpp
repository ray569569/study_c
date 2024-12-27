#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void display(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void smallest(double arr[], int size) {
    double min = arr[0];
    int index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
            index = i;
        }
    }
    cout << "The smallest number is " << min << " at index " << index << endl;
}

int main() {
    double arr[10];
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        arr[i] = (rand() % 100) / 10.0;
    }
    display(arr, 10);
    smallest(arr, 10);
    return 0;
}