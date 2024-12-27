#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  // 用于生成随机数
#include <ctime>    // 用于设置随机数种子
#include <limits>   // 用于获取整型限制

using namespace std;

// 计算符合条件的子数组数量
int getCount(vector<int> arr, int n, int lower, int upper) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            if (sum >= lower && sum <= upper) {
                count++;
            }
        }
    }
    return count;
}

// 生成随机数组
vector<int> generateRandomArray(int size, int rangeStart, int rangeEnd) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rangeStart + rand() % (rangeEnd - rangeStart + 1);  // 生成随机数
    }
    return arr;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // 设置随机数种子

    ofstream outfile("test_data.txt");  // 打开输出文件
    if (!outfile.is_open()) {
        cout << "无法打开文件" << endl;
        return 1;
    }

    int testCases = 100;  // 生成 100 组测试数据

    for (int t = 0; t < testCases; t++) {
        // 生成随机数组的长度
        int n = rand() % 100000 + 1;  // 1 到 100000 的随机长度
        
        // 生成随机下界和上界
        int lower = (rand() % 200001) - 100000;  // -100000 到 100000
        int upper = lower + (rand() % (200001 - (lower + 100000))); // 确保 upper >= lower 并且在范围内
        
        // 生成随机数组的元素，范围是 [-2^31, 2^31 - 1]
        vector<int> input = generateRandomArray(n, numeric_limits<int>::min(), numeric_limits<int>::max());

        // 计算符合条件的子数组数量
        int answer = getCount(input, n, lower, upper);

        // 将输入和输出写入文件
        outfile << "Test case " << t + 1 << ":\n";
        outfile << "Array size: " << n << "\n";
        outfile << "Array: ";
        for (int num : input) {
            outfile << num << " ";
        }
        outfile << "\nLower: " << lower << "\nUpper: " << upper << "\n";
        outfile << "Result: " << answer << "\n";
        outfile << "-------------------------\n";
    }

    outfile.close();  // 关闭文件
    cout << "100 笔测试数据已生成并保存到 test_data.txt 文件中" << endl;

    return 0;
}
