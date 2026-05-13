#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    if (!(cin >> m >> n)) return 0;

    // Read the binary matrix
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    // DP tables of size (m+1) x (n+1) initialized to 0.
    // Indexing from 1 prevents out-of-bounds errors when checking i-1 and j-1.
    vector<vector<int>> dp1(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> dp0(m + 1, vector<int>(n + 1, 0));

    int max_square_len = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            
            // The actual matrix is 0-indexed, so we map i, j to i-1, j-1
            int val = matrix[i - 1][j - 1];

            if (val == 1) {
                // If cell is 1, check top, left, and top-left in dp1
                dp1[i][j] = min({dp1[i - 1][j], dp1[i][j - 1], dp1[i - 1][j - 1]}) + 1;
                max_square_len = max(max_square_len, dp1[i][j]);
            } 
            else if (val == 0) {
                // If cell is 0, check top, left, and top-left in dp0
                dp0[i][j] = min({dp0[i - 1][j], dp0[i][j - 1], dp0[i - 1][j - 1]}) + 1;
                max_square_len = max(max_square_len, dp0[i][j]);
            }
        }
    }

    // Print the maximum side length found
    cout << max_square_len << "\n";

    return 0;
}