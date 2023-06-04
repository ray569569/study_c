#include <iostream>
using namespace std;
int main(){
    int num;
    cin >> num;
    int **arr = new int *[num];
    for(int i = 0; i < num; i++){
        arr[i] = new int[2];
    }
    for(int i = 0; i < num; i++){
        for(int j = 0; j < 2; j++){
            cin >> arr[i][j];
        }
    }
    
    return 0;
}