/*Write a program that fills an integer array of size 16 with random integers. The
program should use a random number generator to fill the array with integers in the
range -10 to 10 and display the generated random numbers first.The output should
consist of two parts:
• Random Generation Result: Directly display the 16 randomly generated
integers in the order they were generated.
• Statistics Table: Display a two-column table where the first column lists the
unique elements in the array, and the second column shows the count of
occurrences for each element. The elements in the list should be sorted in
descending order based on their values in the first column.
For example, if the randomly generated numbers are -12, 3, -12, 4, 1, 1, -12, 1, -
1, 1, 2, 3, 4, 2, 3, -12, the output should be:
N Count
4 2
3 3
2 2
1 4
−1 1
−12 4*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

void display(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[16];
    srand(time(0));
    for (int i = 0; i < 16; i++) {
        arr[i] = (rand() % 21) - 10;
    }
    cout << "Random Generation Result:" << endl;
    display(arr, 16);
    cout << "Statistics Table:" << endl;
    sort(arr, arr + 16, greater<int>());
    
    int count = 1;
    for (int i = 1; i < 16; i++) {
        if (arr[i] == arr[i - 1]) {
            count++;
        } else {
            cout << arr[i - 1] << " " << count << endl;
            count = 1;
        }
    }
    cout << arr[15] << " " << count << endl;
    return 0;
}
