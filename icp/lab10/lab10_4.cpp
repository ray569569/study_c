#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./lab4/t8.txt");
    int num;
    in >> num;
    int** arr = new int*[num];
    for (int i = 0; i < num; i++) {
        arr[i] = new int[num];
        for (int j = 0; j < num; j++) {
            in >> arr[i][j];
        }
    }

    int** transpose = new int*[num];
    for (int i = 0; i < num; i++) {
        transpose[i] = new int[num];
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            *(i + (*(transpose + j))) = *(j + (*(arr + i)));
        }
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            cout << transpose[i][j] << " ";
        }
        cout << endl;
    }
}