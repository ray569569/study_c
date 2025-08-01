#include <fstream>
#include <iostream>
using namespace std;

void findTwoSum(int* nums, int n, int target, int* index1, int* index2) {
    // To do list
    for (int* i = nums; i < (nums + n); i++) {
        for (int* j = nums; j < (nums + n); j++) {
            if (((*i + *j) == target) && i != j) {
                cout << (i - nums) << "," << (j - nums) << endl;
                return;
            }
        }
    }
}

int main() {
    ifstream file("./Q3/Q3_T10.txt");
    if (!file) {
        cout << "Error: Could not open file example.txt" << endl;
        return 1;
    }

    int n, target;
    file >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; i++) {
        file >> nums[i];
    }
    file >> target;

    int index1 = 0, index2 = 0;

    findTwoSum(nums, n, target, &index1, &index2);

    delete[] nums;
    file.close();

    return 0;
}
