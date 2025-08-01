#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./lab2/t8.txt");
    string temp;
    in >> temp;
    int idx;
    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp.size(); j++) {
            if (temp[i] == temp[j] && i != j) {
                break;
            } else if (j == temp.size() - 1) {
                cout << i;
                return 0;
            }
        }
    }
    cout << "-1";
    return 0;
}