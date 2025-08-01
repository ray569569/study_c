#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;

double uniformrRV() {
    return 1.0 * rand() / RAND_MAX;
}

class c {
    public:
    double r;
    double y;
    c() {
        r = uniformrRV() * 1.25;
        y = uniformrRV() * 20;
    }
};

int main() {
    ofstream out;
    out.open("probability1.txt");
    double sum = 0.0;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
        c samples;
        if ((int((samples.r + samples.y) / 5) - int(samples.y / 5) != 0) || (floor((samples.y - samples.r) / 5) - int(samples.y / 5) != 0)) {
            // cout << int((samples.r + samples.y) / 5) - int(samples.y / 5)<< " " << int((samples.y - samples.r) / 5) - int(samples.y / 5) << endl;
            sum++;
        }
        out << sum / (i + 1) << endl;
    }
    out.close();
    return 0;
}