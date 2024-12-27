/*Write a program to write a two-dimensional array of doubles to a comma separated
(CSV) file. The CSV file should have each number separated by a comma. However,
there should be no comma after the last element in a row.( Use random to generate
values in a 5x5 array. Additionally, display each randomly generated result
immediately.)*/

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    double arr[5][5];
    ofstream file("output.csv");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            arr[i][j] = (rand() % 100) / 10.0;
            cout << arr[i][j] << " ";
            file << arr[i][j];
            if (j < 4) {
                cout << ",";
                file << ",";
            }
        }
        cout << endl;
        file << endl;
    }
    file.close();
    return 0;
}

