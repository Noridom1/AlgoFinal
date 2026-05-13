#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O is highly recommended for 10^5 inputs
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    if (!(cin >> m >> n)) return 0; 

    vector<pair<long long, int>> a(m); 
    vector<pair<long long, int>> b(n);  

    for (int i = 0; i < m; i++) {
        cin >> a[i].first; 
        a[i].second = i + 1; 
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i].first;
        b[i].second = i + 1;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int l = 0; 
    int r = n - 1; 
    
    long long min_abs_sum = 9e18; 
    int best_i = -1;
    int best_j = -1;
    /*
    Sum between the smallest element of a with the largest element of b
    Keep track of indexes and min sum 
    If sum == 0 -> optimal so break
    If sum < 0 then index l is too small so increment l
    If sum > 0 then index r is too large so decrement r
    */
    while (l < m && r >= 0) {
        long long raw_sum = a[l].first + b[r].first;
        long long current_abs_sum = abs(raw_sum);
        
        if (current_abs_sum < min_abs_sum) {
            min_abs_sum = current_abs_sum;
            best_i = a[l].second;
            best_j = b[r].second;
        }
        
        // Move pointers based on the RAW sum
        if (raw_sum == 0) {
            break;
        }
        else if (raw_sum < 0) {
            ++l;
        }
        else {
            --r;
        }
    }
    
    cout << best_i << " " << best_j << '\n';
    return 0;
}