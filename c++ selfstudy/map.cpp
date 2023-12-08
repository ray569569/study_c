#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
    int sum = 0;
    char arr[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    map<char, map<char, int>> a;
    vector<char> temp(arr, arr + 10);

    for (int i = 0; i < 10; i++) {
        a[temp[i]][temp[i]] = i;
    }

    for (auto i : a) {
        // cout << i.first << endl;
        for (auto j : i.second) {
            cout << j.first << endl;
        }
    }
    return 0;
}