#include <ctime>
#include <iostream>
#include <random>

using namespace std;

double uniformrRV() {
    return 1.0 * rand() / RAND_MAX;
}
double exponenRV() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> exp_rand(0.4);

    double r = exp_rand(gen);
    return r;
}

class c {
public:
    double r;
    double y;
    c() {
        r = exponenRV() ;
        y = uniformrRV() * 20;
    }
};
int intersection(c t);
int main() {
    int n;
    double E=0.0;
    cin>>n;
    double sum = 0.0;
    srand(time(NULL));
    for (int i = 1; i <= n; i++) {
        c samples;
        if (intersection(samples)==1) {
            //cout << int((samples.r + samples.y) / 5) - int(samples.y / 5)<< " " << int((samples.y - samples.r) / 5) - int(samples.y / 5) << endl;
            sum++;
            
        }
        E = (E*(i-1)+intersection(samples))/(i);
        cout <<i<<" "<< sum / (i) <<" "<<E<<endl;
    }
    
    return 0;
}

int intersection(c t)
{
    int num=0;
    num +=int((t.r + t.y) / 5) - int(t.y / 5);
    num +=int(t.y / 5) - floor((t.y - t.r) / 5) ;
    return num;
}