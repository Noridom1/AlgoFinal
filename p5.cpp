#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to build the Longest Prefix Suffix (LPS) array
vector<int> computeLPS(const string& pat) {
    int m = pat.length();
    vector<int> lps(m, 0);
    
    int len = 0; // Length of the previous longest prefix suffix
    int i = 1;
    
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // Mismatch, but we have a previous match. 
                // Fall back to the previous LPS value.
                len = lps[len - 1];
            } else {
                // No previous match, LPS is 0.
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Function to find all occurrences using KMP
void KMP(const string& text, const string& pat) {
    int n = text.length();
    int m = pat.length();
    
    // Edge case: if pattern is empty or larger than text
    if (m == 0 || m > n) return;

    vector<int> lps = computeLPS(pat);
    
    int i = 0; // index for text
    int j = 0; // index for pattern
    
    bool found = false;

    while (i < n) {
        if (pat[j] == text[i]) {
            j++;
            i++;
        }
        
        // Full match found
        if (j == m) {
            // Calculate 1-based starting index
            cout << (i - m + 1) << " ";
            found = true;
            
            // Critical Step for Overlapping Matches:
            // Fall back using LPS to catch overlaps (e.g., "aaaaa" and "aa")
            j = lps[j - 1];
        } 
        // Mismatch after j matches
        else if (i < n && pat[j] != text[i]) {
            if (j != 0) {
                // Do not match lps[0..lps[j-1]] characters, 
                // they will match anyway
                j = lps[j - 1];
            } else {
                // First character mismatch, just move text pointer
                i++;
            }
        }
    }
    
    if (found) cout << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (cin >> a >> b) {
        KMP(a, b);
    }

    return 0;
}