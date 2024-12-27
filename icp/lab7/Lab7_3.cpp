#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in;
    in.open("./lab3_test/t8.txt");
    string line;
    stringstream ss1;

    vector<vector<int>> v;
    vector<int> v1;
    getline(in, line);
    while (!in.eof()) {
        getline(in, line);
        ss1 << line;
        int temp;
        while (ss1 >> temp) {
            v1.push_back(temp);
        }
        ss1.clear();
        v.push_back(v1);
        v1.clear();
    }
    int min_move[v.size()][v[0].size()];
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[0].size(); j++) {
            min_move[i][j] = 0;
        }
    }

    min_move[0][0] = v[0][0];
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[0].size(); j++) {
            if (j > 0) {
                min_move[i][j] = min_move[i][j - 1] + v[i][j];
            }
            if (i > 0) {
                if (j == 0) {
                    min_move[i][j] = min_move[i - 1][j] + v[i][j];
                } else
                    min_move[i][j] = min(min_move[i][j], min_move[i - 1][j] + v[i][j]);
            }
        }
    }
    cout << "Minimum moves: " << min_move[v.size() - 1][v[0].size() - 1] << endl;
    return 0;
}