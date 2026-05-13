#include <bits/stdc++.h>
using namespace std;

    int main() {

    vector<int> p;
    int x;

    // Read permutation from line 1
    string line;
    getline(cin, line);
    stringstream ss(line);

    while (ss >> x) {
        p.push_back(x);
    }

    int n = p.size();

    // Read rank y
    long long y;
    cin >> y;

    // Precompute factorials
    vector<long long> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }

    // ---------------------------------------------------
    // Part 1: Find rank x of permutation p
    // ---------------------------------------------------
    vector<int> nums;
    for (int i = 1; i <= n; i++) nums.push_back(i);

    long long rank = 1;

    // rank = sum(count_smaller * (remaining - 1)!)
    for (int i = 0; i < n; i++) {
        int smaller = 0;

        for (int j = 0; j < (int)nums.size(); j++) {
            if (nums[j] == p[i]) {
                smaller = j;
                nums.erase(nums.begin() + j);
                break;
            }
        }

        // cout << smaller << " " << fact[n-i-1] << endl;
        rank += smaller * fact[n - i - 1];
    }

    cout << rank << '\n';

    // ---------------------------------------------------
    // Part 2: Find permutation with rank y
    // ---------------------------------------------------
    y--; // convert to 0-based rank

    nums.clear();
    for (int i = 1; i <= n; i++) nums.push_back(i);

    vector<int> q;

    for (int i = n; i >= 1; i--) {
        long long block = fact[i - 1];

        int idx = y / block;
        y %= block;

        q.push_back(nums[idx]);
        nums.erase(nums.begin() + idx);
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << q[i];
    }
    cout << '\n';

    return 0;
}