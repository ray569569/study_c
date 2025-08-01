#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./lab3/t7.txt");
    int M, N, m, n;
    in >> M >> N >> m >> n;
    int** arr = new int*[M];
    for (int i = 0; i < M; i++) {
        arr[i] = new int[N];
        for (int j = 0; j < N; j++) {
            in >> arr[i][j];
        }
    }

    int** window = new int*[M - m + 1];
    for (int i = 0; i < M - m + 1; i++) {
        window[i] = new int[N - n + 1];
    }

    for (int i = 0; i < M - m + 1; i++) {
        for (int j = 0; j < N - n + 1; j++) {
            int sum = -100000;
            for (int k = 0; k < m; k++) {
                for (int l = 0; l < n; l++) {
                    sum = max(sum, arr[i + k][j + l]);
                }
            }
            window[i][j] = sum;
        }
    }
    for (int i = 0; i < M - m + 1; i++) {
        for (int j = 0; j < N - n + 1; j++) {
            cout << window[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}