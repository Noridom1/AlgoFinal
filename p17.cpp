#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<bool> visited(n, false);

    queue<pair<long long, int>> q; // {number, remainder}

    int rem1 = 1 % n;
    if (rem1 == 0) { cout << 1 << endl; return 0; }
    visited[rem1] = true;
    q.push({1LL, rem1});

    while (!q.empty()) {
        auto [num, rem] = q.front();
        q.pop();

        // Try appending '0' and '1'
        for (int d : {0, 1}) {
            long long nnum = num * 10 + d;
            int nrem = (int)((1LL * rem * 10 + d) % n);

            if (nnum > 111111111LL) continue; // exceeds 9 digits

            if (nrem == 0) {
                cout << nnum << endl;
                return 0;
            }

            if (!visited[nrem]) {
                visited[nrem] = true;
                q.push({nnum, nrem});
            }
        }
    }

    cout << -1 << endl; // no solution within 9 digits
    return 0;
}


// Time: O(n)
// Space: O(n)