#include <iostream>
#include <cstdlib>  // 包含亂數生成所需的庫
#include <ctime> 
#include<fstream>
using namespace std;

// 定義結構來保存矩陣
struct Matrix {
    int rows;
    int cols;
    int** data;

    // 構造函數
    Matrix(int r, int c) : rows(r), cols(c) {
        // 分配記憶體
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
        }
    }

    // 解構函數
    ~Matrix() {
        // 釋放記憶體
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
};

// 函數用於生成指定大小的二維隨機陣列
void generateRandomArray(int rows, int cols, int** &arr) {
    // 使用動態分配記憶體來創建二維數組
    arr = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
    }

    // 生成隨機數填充二維數組
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand() % 256;  // 生成 0 到 99 之間的隨機數
        }
    }
}

// 函數用於生成全部初始化為0的指定大小的二維陣列
void generateZeroArray(int rows, int cols, int** &arr) {
    // 使用動態分配記憶體來創建二維數組
    arr = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols]();
    }
}

int main() {
    ofstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    int num = 10000;
    //in<<num<<endl;
    for(int w = 0;w<num;w++)
    {
        //srand(time(nullptr));
        // 定義和初始化 4x4、5x5 和 8x8 的矩陣
        bool flag =1;
        Matrix matrix4x4(4, 4);
        Matrix matrix5x5(5, 5);
        Matrix matrix8x8(8, 8);

        // 生成隨機矩陣
        generateRandomArray(matrix4x4.rows, matrix4x4.cols, matrix4x4.data);
        generateRandomArray(matrix8x8.rows, matrix8x8.cols, matrix8x8.data);

        // 生成全部初始化為0的矩陣
        generateZeroArray(matrix5x5.rows, matrix5x5.cols, matrix5x5.data);

        

        // 將生成的隨機矩陣輸出到控制台
        
        
        int temp=0;
        int x=0,y=0,min=4096;
        for (int i = 0; i < matrix5x5.rows; ++i) {
            for (int j = 0; j < matrix5x5.cols; ++j) {
                for(int k=0;k<4;k++)
                {
                    for(int l=0;l<4;l++)
                    {
                        temp += abs(matrix4x4.data[l][k] - matrix8x8.data[l+j][k+i]);
                    }
                }
                matrix5x5.data[j][i] =temp;
                temp=0;
            }
        }
        for (int i = 0; i < matrix5x5.rows; ++i) {
            for (int j = 0; j < matrix5x5.cols; ++j) {
                for(int k=0;k<5;k++)
                {
                    for(int l=0;l<5;l++)
                    {
                        if((i==k)&&(j==l))
                            continue;
                        else
                        {
                            if((matrix5x5.data[i][j] == matrix5x5.data[k][l]))
                                flag = 0;
                        }
                        
                    }
                }
            }
        }

        if(flag)
        {
            for (int i = 0; i < matrix4x4.rows; ++i) {
                for (int j = 0; j < matrix4x4.cols; ++j) {
                    in << matrix4x4.data[i][j] << " ";
                }
                in << endl;
            }

        
            for (int i = 0; i < matrix8x8.rows; ++i) {
                for (int j = 0; j < matrix8x8.cols; ++j) {
                    in << matrix8x8.data[i][j] << " ";
                }
                in << endl;
            }
            
        
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    if(min>matrix5x5.data[j][i])
                    {
                        min = matrix5x5.data[j][i];
                        x = i-2;
                        y = (4-j)-2;
                    }
                }
            }
            out<<x<<" "<<y;
            out << endl;
        }
    }
    // 設置隨機數種子
    
    return 0;
}
