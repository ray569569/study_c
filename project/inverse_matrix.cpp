#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

const int N = 4; // 矩陣大小

// 打印矩陣
void printMatrix(const vector<vector<double>>& mat, const string& name) {
    cout << name << " Matrix:" << endl;
    for (const auto& row : mat) {
        for (double val : row) {
            cout <<setw(10)<< val << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// 計算 Givens Rotation 的 cos 和 sin
void computeGivens(double a, double b, double& c, double& s) {
    double r = sqrt(a * a + b * b);
    c = a / r;
    s = -b / r;
}

// 應用 Givens Rotation
void applyGivens(vector<vector<double>>& mat, int row1, int row2, int col, double c, double s) {
    //printMatrix(mat, "Rf");
    for (int j = col; j < N; j++) {
        double temp1 = c * mat[row1][j] - s * mat[row2][j];
        double temp2 = s * mat[row1][j] + c * mat[row2][j];
        mat[row1][j] = temp1;
        mat[row2][j] = temp2;
    }
    //printMatrix(mat, "Ra");
}

void qrDecomposition(const vector<vector<double>>& A, vector<vector<double>>& Q, vector<vector<double>>& R) {
    R = A; // 初始化 R 矩陣為輸入矩陣
    Q = vector<vector<double>>(N, vector<double>(N, 0));

    // 初始化 Q 為單位矩陣
    for (int i = 0; i < N; i++) {
        Q[i][i] = 1;
    }

    // Givens Rotation QR 分解
    for (int j = 0; j < N - 1; j++) { //column
        for (int i = j + 1; i < N; i++) { //row
            double c, s;
            //cout<<i<<" "<<j<<endl;
            computeGivens(R[j][j], R[i][j], c, s); // 計算 cos 和 sin

            // 應用旋轉到 R
            applyGivens(R, j, i, j, c, s); //R只需要乘一乘

            // 應用旋轉到 Q
            for (int k = 0; k < N; k++) {
                //cout<<i<<" "<<j<<" "<<k<<endl;
                double temp1 = c * Q[k][j] - s * Q[k][i];
                double temp2 = s * Q[k][j] + c * Q[k][i];
                Q[k][j] = temp1;
                Q[k][i] = temp2;
            }
        }
    }
}

int main() {
    // 輸入矩陣 A
    vector<vector<double>> A = {
        {-0.8851, -0.1831,  0.4278,  0.3780},
        { 0.4644, -0.4078,  0.7862,  0.8052},
        { 0.0305,  0.8945,  0.4459, -0.0443},
        { 0.5231, -0.9562,  0.3862,  -0.6674}
    };

    // 初始化 Q 和 R
    vector<vector<double>> Q(N, vector<double>(N, 0));
    vector<vector<double>> R(N, vector<double>(N, 0));

    // QR 分解
    qrDecomposition(A, Q, R);

    // 打印結果
    printMatrix(A, "Input");
    printMatrix(Q, "Q");
    printMatrix(R, "R");
    // 計算反矩陣
    vector<vector<double>> invA(N, vector<double>(N, 0));
    for (int i = 0; i < N; i++) {
        vector<double> e(N, 0);
        e[i] = 1;
        vector<double> x(N, 0);
        for (int j = N - 1; j >= 0; j--) {
            x[j] = e[j];
            for (int k = j + 1; k < N; k++) {
                x[j] -= R[j][k] * x[k];
            }
            x[j] /= R[j][j];
        }
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                invA[j][i] += Q[j][k] * x[k];
            }
        }
    }

    // 打印反矩陣
    printMatrix(invA, "Inverse");
    return 0;
}
