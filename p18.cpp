#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // vector<int> a(n);
    // for (int i = 0; i < n; i++) cin >> a[i];

    // convert permutation to string state
    string start = "";
    for (int i = 0; i < n; ++i) {
        char x;
        cin >> x;
        start.push_back(x);
    }

    string target = "";
    for (int i = 1; i <= n; i++) {
        target.push_back(char(i + '0'));
    }

    queue<string> q;
    unordered_map<string, int> dist;

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        if (cur == target) {
            cout << dist[cur] << "\n";
            return 0;
        }

        int d = dist[cur];

        for (int i = 1; i < n; i++) { // prefix size i+1 (i from 1..n-1)
            string nxt = cur;

            // reverse prefix [0..i]
            reverse(nxt.begin(), nxt.begin() + i + 1);

            if (!dist.count(nxt)) {
                dist[nxt] = d + 1;
                q.push(nxt);
            }
        }
    }

    return 0;
}


/*
TimeO(n · n!) — instant for n ≤ 8
SpaceO(n · n!) for the queue + visited map
*/
