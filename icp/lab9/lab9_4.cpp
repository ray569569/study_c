#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./test/lab4/text8.txt");

    int num;
    in >> num;
    int line[num];
    for (int i = 0; i < num; i++) {
        in >> line[i];
    }
    int* start = line;
    int* end = line + num - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    for (int i = 0; i < num; i++) {
        cout << line[i] << " ";
    }

    return 0;
}