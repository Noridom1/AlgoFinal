  #include <iostream>
#include <vector>
#include <string>

using namespace std;

// Store all valid board configurations
vector<vector<string>> results;

// Boolean arrays to track attacked zones in O(1) time
vector<bool> col_taken;
vector<bool> diag1_taken; // Major diagonal: row - col is constant
vector<bool> diag2_taken; // Minor diagonal: row + col is constant

void solve(int row, int n, vector<string>& board) {
    // Base Case: If we successfully placed a queen in every row
    if (row == n) {
        results.push_back(board);
        return;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < n; col++) {
        // Calculate diagonal indices
        int d1 = row - col + n; // Add n to avoid negative numbers
        int d2 = row + col;

        // Check if the current cell is safe
        if (!col_taken[col] && !diag1_taken[d1] && !diag2_taken[d2]) {
            
            // 1. PLACE THE QUEEN (Choose)
            board[row][col] = 'Q';
            col_taken[col] = true;
            diag1_taken[d1] = true;
            diag2_taken[d2] = true;

            // 2. RECURSE (Explore)
            solve(row + 1, n, board);

            // 3. BACKTRACK (Un-choose)
            board[row][col] = '.';
            col_taken[col] = false;
            diag1_taken[d1] = false;
            diag2_taken[d2] = false;
        }
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Initialize the board with '.'
    vector<string> board(n, string(n, '.'));

    // Initialize tracking arrays. Diagonals need size 2*N
    col_taken.assign(n, false);
    diag1_taken.assign(2 * n, false);
    diag2_taken.assign(2 * n, false);

    // Start backtracking from row 0
    solve(0, n, board);

    // Print total number of solutions
    cout << results.size() << "\n";

    // Print all board configurations
    for (int i = 0; i < results.size(); i++) {
        for (int r = 0; r < n; r++) {
            cout << results[i][r] << "\n";
        }
        // Print a blank line between configurations (but not after the last one)
        if (i < results.size() - 1) {
            cout << "\n";
        }
    }

    return 0;
}