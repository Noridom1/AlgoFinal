#include <bits/stdc++.h>
using namespace std;

void computeTreeSize(vector<vector<int>> &tree,
                     vector<int> &tree_size,
                     int node,
                     int parent) {

    tree_size[node] = 1;

    for (auto child : tree[node]) {
        if (child == parent) continue;

        computeTreeSize(tree, tree_size, child, node);

        tree_size[node] += tree_size[child];
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> tree(n);

    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;

        --x;
        --y;

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<int> tree_size(n);

    computeTreeSize(tree, tree_size, 0, -1);

    long long res = 0;

    for (int node = 0; node < n; ++node) {
        for (auto child : tree[node]) {

            // only process child direction
            if (tree_size[child] < tree_size[node]) {
                res += 1LL * tree_size[child] *
                       (n - tree_size[child]);
            }
        }
    }

    cout << res << endl;
}





// #include <bits/stdc++.h>
// using namespace std;

// void computeTreeSize(vector<vector<int>> &tree, vector<int> &tree_size, int node) {
//     if (tree[node].size() == 0) {
//         tree_size[node] = 1;
//         return;
//     }
//     for (auto &child : tree[node]) {
//         computeTreeSize(tree, tree_size, child);
//         tree_size[node] += tree_size[child];
//         // cout << "Child:" << child << ": " << tree_size[child];
//     }
// }
// int main() {
//     int n;
//     cin >> n;
//     vector<vector<int>> tree(n, vector<int>{});
//     for (int i = 0; i < n - 1; ++i) {
//         int x, y;
//         cin >> x >> y;
//         tree[x - 1].push_back(y - 1);
//     }

//     vector<int> tree_size(n, 1);

//     computeTreeSize(tree, tree_size, 0);

//     // for (int i = 0; i < n; ++i) {
//     //     cout << i + 1 << " " << tree_size[i] << endl;
//     // }

//     int res = 0;
//     for (int i = 0; i < n; ++i) {
//         for (auto &child : tree[i]) {
//             res += tree_size[child] * (n - tree_size[child]);
//         }
//     }
//     cout << res << endl;
    
// }











/*
Time Complexity: O(n)
Explanation:
DFS visits each node and edge once
contribution of each edge is computed once
Space Complexity: O(n)
Explanation:
adjacency list stores O(n) edges
recursion stack and subtree array use O(n) space

*/