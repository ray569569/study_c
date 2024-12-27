#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./lab1/t1.txt");
    int temp;
    in >> temp;
    int num = temp;
    int* arr = new int[temp];
    for (int i = 0; i < num; i++) {
        in >> temp;
        arr[i] = temp;
    }

    int max = 0;
    for (int i = 0; i < num; i++) {
        int t = arr[i];
        for (int j = i + 1; j < num; j++) {
            // cout<<arr[j]<<" "<<t<<endl;
            if (arr[j] * t >= max) {
                max = arr[j] * t;
                t = t * arr[j];
            } else {
                t = t * arr[j];
            }
        }
        if (t > max) {
            max = t;
        }
    }
    cout << max;
    return 0;
}