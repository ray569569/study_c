#include <bits/stdc++.h>

using namespace std;

double uniform_rv() {
    return 1.0 * rand() / RAND_MAX;
}

double exponen_rv() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> exp_rand(0.4);

    double ret = exp_rand(gen);
    return ret;
}
int main() {
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        cout << exponen_rv() << endl;
    }
    return 0;
}