#include <iostream>
#include <vector>
using namespace std;

int main() {
    int total_vertices;
    cin >> total_vertices;
    
    vector<int> match(total_vertices, -1);
    int a, b;
    
    vector<int> inputs;
    int num;
    
    while (cin >> num) {
        inputs.push_back(num);
    }
    
    for (int i = 0; i < inputs.size() - 1; i += 2) {
        if (i + 1 < inputs.size()) {  
            a = inputs[i];
            b = inputs[i+1];
            
            match[a] = b;
            match[b] = a;
        }
    }
    
    
    vector<vector<int>> dp(total_vertices, vector<int>(total_vertices, 0));
    
    for (int len = 2; len <= total_vertices; len++) {
        for (int i = 0; i + len - 1 < total_vertices; i++) {
            int j = i + len - 1;
            
            // Option 1: Endpoint j is not used in the maximum subset
            dp[i][j] = dp[i][j-1];
            
            // Option 2: Endpoint j forms a chord with some point k
            int k = match[j];
            if (k >= i && k < j) {
                // We use chord (k,j) and combine with best solutions for [i,k-1] and [k+1,j-1]
                int left_region = (k > i) ? dp[i][k-1] : 0;
                int middle_region = (k + 1 < j) ? dp[k+1][j-1] : 0;
                
                dp[i][j] = max(dp[i][j], left_region + 1 + middle_region);
            }
        }
    }
    
    
    cout << dp[0][total_vertices-1] << endl;
    
    return 0;
}