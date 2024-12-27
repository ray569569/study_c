#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

int getCount(vector<int> arr, int n, int lower, int upper)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            if (sum >= lower and sum <= upper) {
                count++;
            }
        }
    }
    return count;
}

int main()
{
    int n = 4;
    vector<int> input ;
    int lower = -4, upper = 1;
    int temp;
    while(cin>>temp)
    {
        input.push_back(temp);
    }
    int a,b;
    upper = input[input.size()-1];
    lower = input[input.size()-2];
    input.pop_back();
    input.pop_back();
    n = input.size();
    int answer = getCount(input, n, lower, upper);
    cout << answer << endl;
    return 0;
}