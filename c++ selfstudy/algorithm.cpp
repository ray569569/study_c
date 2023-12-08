#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    vector<int>::iterator a;

    int k[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> b(k, k + 10);
    list<int> c(k + 5, k + 7);

    a = search(b.begin(), b.end(), c.begin(), c.end());

    if (a != b.end()) {
        cout << *a << endl;
    }

    return 0;
}
