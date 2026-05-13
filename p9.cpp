#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, p;
    getline(cin, s); 
    
    // Read the second line (Pattern P).
    getline(cin, p);

    int n = s.length();
    int m = p.length();

    // dp[i][j] will be true if s[0..i-1] matches p[0..j-1]
    // We add +1 to handle the "empty string" base cases at index 0.
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    // Base Case 1: Empty string matches empty pattern
    dp[0][0] = true;

    // Base Case 2: Empty string matching a pattern like "a*b*c*"
    // We only look at even indices because a '*' requires a preceding character.
    for (int j = 1; j <= m; j++) {
        if (p[j - 1] == '*') {
            // A '*' can eliminate itself and the character before it (j-2)
            dp[0][j] = dp[0][j - 2];
        }
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            
            // Rule 1: Exact match or '.' wildcard
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // the string from 0 to i-1 is the same as pattern from to to j-1 in this case
            } 
            // Rule 2: The '*' wildcard
            else if (p[j - 1] == '*') {
                
                // Option A: Zero occurrences of the preceding character
                // We drop the '*' and the character before it.
                bool zero_occurrences = dp[i][j - 2];
                
                // Option B: One or more occurrences
                // We check if the character BEFORE the '*' matches the current string char.
                bool one_or_more = false;
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    // If it matches, we rely on the result of the string MINUS this current char.
                    one_or_more = dp[i - 1][j]; //If the same char then it means it still matches from the char i-1 up to the char i
                    // Eg: aaa a* then dp[3][2] = dp[2][2] = 1 because dp[2][2] check aa and a* which is valid and 
                    // since p[j-2] = s[i-1] or p[0] = s[2] so dp[3][2] = 1 (i=3,j=2)
                }
                
                // If either option works, this state is valid.
                dp[i][j] = zero_occurrences || one_or_more;
            }
        }
    }

    // The answer for the full string and full pattern is at the bottom right of the table
    if (dp[n][m]) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }

    return 0;
}