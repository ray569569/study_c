#include<iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    cout<< n;
    if(n == 1)
        return 0;
    else
    {
        cout<<n%2 == 0? n/2:3*n+1;
        return 0;
    }

}