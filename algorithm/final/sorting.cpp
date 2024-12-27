#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;
class team
{
public:
    int idx;
    long long cnt;
    long long mem_sum;
};

int main()
{
    int n;
    cin >> n;

    vector<team> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].cnt >> vec[i].mem_sum;
        vec[i].idx = i;
    }

    sort (vec.begin(), vec.end(), [] (team &a, team &b) {
        if (a.cnt != b.cnt) return a.cnt > b.cnt;
        return a.mem_sum < b.mem_sum;
    });
    

    for (auto k: vec) {
        cout << "team " << k.idx << ": " << k.cnt << ", " << k.mem_sum << endl;
    }

    return 0;

}