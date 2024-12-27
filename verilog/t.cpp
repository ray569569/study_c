#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ofstream fout("pat.txt");
    if (!fout) {
        cerr << "无法打开文件进行写入: " << "pat.txt" << endl;
        return 1;
    }
    ofstream fout2("patout.txt");
    if (!fout2) {
        cerr << "无法打开文件进行写入: " << "patout.txt" << endl;
        return 1;
    }
    srand(time(0));
    fout << 20000 << endl;
    for (int cou = 0; cou < 20000; cou++) {
        int matrix[8][16], matrix2[16][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 15; j++) {
                matrix[i][j] = rand() % 256;
                matrix2[j][i] = matrix[i][j];
                // cout << matrix[i][j] << ' ';
                fout << matrix[i][j] << ' ';
            }
            matrix[i][15] = rand() % 256;
            matrix2[15][i] = matrix[i][15];
            // cout << matrix[i][15] << endl;
            fout << matrix[i][15] << endl;
        }
        // cout << endl;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 8; j++) {
                // cout << matrix2[i][j] << ' ';
            }
            // cout << endl;
        }

        // cout << endl;
        int IIT[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                IIT[i][j] = 0;
            }
        }
        // cout << endl;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                for (int k = 0; k < 16; ++k) {
                    IIT[i][j] += matrix[i][k] * matrix2[k][j];
                }
                // cout << IIT[i][j] << ' ';
            }
            // cout << endl;
        }

        // cout << endl;
        int sum[8];
        for (int i = 0; i < 8; i++) {
            sum[i] = 0;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                sum[i] += IIT[i][j];
            }
        }

        for (int i = 0; i < 8; i++) {
            sum[i] /= 8;
            // cout << sum[i] << endl;
        }
        // cout << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (IIT[i][j] < sum[i]) {
                    IIT[i][j] = 0;
                }
                // cout << IIT[i][j] << ' ';
            }
            // cout << endl;
        }

        int w[8];
        // cout << endl;
        for (int i = 0; i < 7; i++) {
            w[i] = rand() % 256;
            // cout << w[i] << endl;
            fout << w[i] << ' ';
        }
        w[7] = rand() % 256;
        // cout << w[7] << endl;
        fout << w[7] << endl;

        int ans[8];
        for (int i = 0; i < 8; i++) {
            ans[i] = 0;
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                ans[i] += IIT[i][j] * w[j];
                // cout << IIT[i][j] << ' ';
                // cout << w[j] << endl;
            }
        }
        // cout << endl;
        for (int i = 0; i < 7; i++) {
            // cout << ans[i] << ' ';
            fout2 << ans[i] << ' ';
        }
        // cout << ans[7] << endl;
        fout2 << ans[7] << endl;
    }
}