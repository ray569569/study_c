#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// 生成一个 8x16 的随机矩阵
void generateRandomMatrix(vector<vector<int>>& matrix) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            matrix[i][j] = rand() % 10;  // 随机数范围 0-9
        }
    }
}

// 生成一个 8x1 的随机矩阵
void generateRandomVector(vector<int>& vec) {
    for (int i = 0; i < 8; ++i) {
        vec[i] = rand() % 10;  // 随机数范围 0-9
    }
}

// 计算矩阵的转置
void transposeMatrix(const vector<vector<int>>& matrix, vector<vector<int>>& transpose) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }
}

// 计算两个矩阵的乘积
void multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& result) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 16; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// 输出矩阵
void printMatrix(const vector<vector<int>>& matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// 输出向量
void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

// 对矩阵进行操作：计算每行的平均值，将小于平均值的元素设为0
void processMatrix(vector<vector<int>>& matrix) {
    for (int i = 0; i < 8; ++i) {
        int sum = 0;
        for (int j = 0; j < 8; ++j) {
            sum += matrix[i][j];
        }
        int avg = sum / 8;  // 使用整数除法实现向下取整
        for (int j = 0; j < 8; ++j) {
            if (matrix[i][j] < avg) {
                matrix[i][j] = 0;
            }
        }
    }
}

// 计算 8x8 矩阵与 8x1 向量的乘积
void multiplyMatrixVector(const vector<vector<int>>& matrix, const vector<int>& vec, vector<int>& result) {
    for (int i = 0; i < 8; ++i) {
        result[i] = 0;
        for (int j = 0; j < 8; ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
}

int main() {
     //srand(time(0));  // 设定随机数种子
    ofstream in;
    ofstream out;
    in.open("in.txt");
    out.open("out.txt");
    vector<vector<int>> matrix(8, vector<int>(16));
    vector<vector<int>> transpose(16, vector<int>(8));
    vector<vector<int>> result(8, vector<int>(8));
    vector<int> vec(8);
    vector<int> finalResult(8);
    int num = 1;
    for (int k = 0; k < num; k++) {
        generateRandomMatrix(matrix);
        
        //cout << "Original 8x16 Matrix:" << endl;
        printMatrix(matrix, 8, 16);
        cout<<endl;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 16; ++j) {
                in << matrix[i][j] << " ";
            }
            in << endl;
        }
        transposeMatrix(matrix, transpose);

        //cout << "\nTransposed 16x8 Matrix:" << endl;
        //printMatrix(transpose, 16, 8);

        multiplyMatrices(matrix, transpose, result);

         //cout << "\nResultant 8x8 Matrix:" << endl;
        printMatrix(result, 8, 8);

        // 对结果矩阵进行行平均值计算并处理
        processMatrix(result);

         //cout << "\nProcessed 8x8 Matrix:" << endl;
       printMatrix(result, 8, 8);
   // cout<<endl;
        // 生成随机的 8x1 向量
        generateRandomVector(vec);

        // cout << "\nRandom 8x1 Vector:" << endl;
        // printVector(vec);
        for (int j = 0; j < 8; ++j) {
            in << vec[j] << " ";
        }
        in << endl;
        // 计算 8x8 矩阵与 8x1 向量的乘积
        multiplyMatrixVector(result, vec, finalResult);

        // cout << "\nFinal 8x1 Resultant Vector:" << endl;
        // printVector(finalResult);

        for (int j = 0; j < 8; ++j) {
            out << finalResult[j] << " ";
        }
        out << endl;
    }
    return 0;
}
