#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream file("./Q1/Q1_T10.txt");
    if (!file) {
        cout << "Error: Could not open file example.txt" << endl;
        return 1;
    }
    int n, m;
    file >> n >> m;

    char **arr = new char *[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new char[m];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file >> arr[i][j];
        }
    }
    file.close();
    // To do list

    char ans[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[i][j] = '/';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int sum = 0;
            if (i - 1 >= 0 && arr[i - 1][j] == '*')
                sum++;
            if (i + 1 < n && arr[i + 1][j] == '*')
                sum++;
            if (j - 1 >= 0 && arr[i][j - 1] == '*')
                sum++;
            if (j + 1 < m && arr[i][j + 1] == '*')
                sum++;
            if (i - 1 >= 0 && j - 1 >= 0 && arr[i - 1][j - 1] == '*')
                sum++;
            if (i + 1 < n && j - 1 >= 0 && arr[i + 1][j - 1] == '*')
                sum++;
            if (i - 1 >= 0 && j + 1 < m && arr[i - 1][j + 1] == '*')
                sum++;
            if (i + 1 < n && j + 1 < m && arr[i + 1][j + 1] == '*')
                sum++;

            if (arr[i][j] != '*')
                ans[i][j] = (sum + '0');
            else if (arr[i][j] == '*')
                ans[i][j] = '*';
            // cout << ans[i][j] << endl;
        }
    }
    cout << "Output map:" << endl;
    ;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j];
        }
        cout << endl;
    }

    //
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
