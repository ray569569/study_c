#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    n /= 2;  // Convert from number of vertices to number of chords

    // Read chord endpoints
    vector<pair<int, int>> chords;
    int a, b;
    while (cin >> a && a != 0) {
        cin >> b;
        if (a > b) swap(a, b);  // Ensure a < b
        chords.push_back({a, b});
    }

    // Create a mapping from endpoint to chord index
    vector<int> endpoint_to_chord(2 * n, -1);
    for (int i = 0; i < chords.size(); i++) {
        endpoint_to_chord[chords[i].first] = i;
        endpoint_to_chord[chords[i].second] = i;
    }

    // DP table: dp[i][j] represents M(i,j)
    vector<vector<int>> dp(2 * n, vector<int>(2 * n, 0));

    // Fill the DP table
    for (int len = 1; len < 2 * n; len++) {
        for (int i = 0; i < 2 * n - len; i++) {
            int j = i + len;

            // Case 1: No chord ends at j
            dp[i][j] = dp[i][j - 1];

            // Case 2: There is a chord ending at j
            int chord_idx = endpoint_to_chord[j];
            if (chord_idx != -1) {
                int k = chords[chord_idx].first;  // Other endpoint of the chord
                if (k >= i) {
                    // The chord is in the current region
                    dp[i][j] = max(dp[i][j], 1 + dp[i][k - 1] + dp[k + 1][j - 1]);
                }
            }
        }
    }

    cout << dp[0][2 * n - 1] << endl;

    return 0;
}
