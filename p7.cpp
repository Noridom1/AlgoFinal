#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    
    // Edge case: Need at least 3 blocks to trap any water
    if (n < 3) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    // Initialize pointers and tracking variables
    int left = 0;
    int right = n - 1;
    
    int max_left = 0;
    int max_right = 0;
    
    // CRITICAL: Use long long for total water to prevent overflow!
    long long total_water = 0;

    // Two Pointer Logic
    while (left < right) {
        // We always process the side with the smaller height.
        // This guarantees that the taller side acts as a secure boundary.
        if (h[left] < h[right]) {
            if (h[left] >= max_left) {
                // Update our left boundary
                max_left = h[left];
            } else {
                // Since h[left] < h[right] AND h[left] < max_left,
                // we are guaranteed to trap water here.
                total_water += (max_left - h[left]);
            }
            left++;
        } else {
            if (h[right] >= max_right) {
                // Update our right boundary
                max_right = h[right];
            } else {
                // Since h[right] <= h[left] AND h[right] < max_right,
                // we are guaranteed to trap water here.
                total_water += (max_right - h[right]);
            }
            right--;
        }
    }

    cout << total_water << "\n";

    return 0;
}