#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Struct to store cluster data
struct Cluster {
    long long a, b;
    long long diff;
    
    // Sort descending by (a - b)
    bool operator<(const Cluster& other) const {
        return diff > other.diff; 
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n, m;
    if (!(cin >> k >> n >> m)) return 0;

    vector<Cluster> clusters(k);
    for (int i = 0; i < k; ++i) {
        cin >> clusters[i].a >> clusters[i].b;
        clusters[i].diff = clusters[i].a - clusters[i].b;
    }

    // Step 1: Sort descending by the difference
    sort(clusters.begin(), clusters.end());

    // Step 2: Calculate prefix_a
    // prefix_a[i] stores the sum of the TOP 'n' values of 'a' from indices 0 to i
    vector<long long> prefix_a(k, 0);
    // Min-Heap keeps the smallest of the top 'n' at the top, so we can quickly remove it
    priority_queue<long long, vector<long long>, greater<long long>> minHeapA;
    long long current_sum_a = 0;

    for (int i = 0; i < k; ++i) {
        minHeapA.push(clusters[i].a);
        current_sum_a += clusters[i].a;
        
        // If we have more than 'n' elements, remove the smallest one
        if (minHeapA.size() > n) {
            current_sum_a -= minHeapA.top();
            minHeapA.pop();
        }
        prefix_a[i] = current_sum_a;
    }

    // Step 3: Calculate suffix_b
    // suffix_b[i] stores the sum of the TOP 'm' values of 'b' from indices i to k-1
    vector<long long> suffix_b(k, 0);
    priority_queue<long long, vector<long long>, greater<long long>> minHeapB;
    long long current_sum_b = 0;

    for (int i = k - 1; i >= 0; --i) {
        minHeapB.push(clusters[i].b);
        current_sum_b += clusters[i].b;
        
        // If we have more than 'm' elements, remove the smallest one
        if (minHeapB.size() > m) {
            current_sum_b -= minHeapB.top();
            minHeapB.pop();
        }
        suffix_b[i] = current_sum_b;
    }

    // Step 4: Find the best split point
    long long max_total = 0;
    
    // The dividing line 'i' means the right side starts at index 'i'.
    // Left side is 0 to i-1.
    // Valid split points: Left side needs at least 'n' elements (i >= n).
    // Right side needs at least 'm' elements (i <= k - m).
    for (int i = n; i <= k - m; ++i) {
        long long current_total = prefix_a[i - 1] + suffix_b[i];
        if (current_total > max_total) {
            max_total = current_total;
        }
    }

    cout << max_total << "\n";

    return 0;
}