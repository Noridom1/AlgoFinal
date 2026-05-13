#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Edge {
    int to, id;
};

int n, m;

vector<vector<Edge>> graph;

vector<int> tin, low, subtree;
vector<ll> ans;

int timer = 0;

void dfs(int u, int parentEdge = -1) {
    tin[u] = low[u] = ++timer;
    subtree[u] = 1;

    for (auto e : graph[u]) {
        int v = e.to;
        int id = e.id;

        if (id == parentEdge) continue;

        // Back edge
        if (tin[v]) {
            low[u] = min(low[u], tin[v]);
        }
        else {
            dfs(v, id);

            subtree[u] += subtree[v];

            low[u] = min(low[u], low[v]);

            // Bridge
            if (low[v] > tin[u]) {
                ll s = subtree[v];
                ans[id] = s * (n - s);
            }
        }
    }
}

int main() {

    cin >> n >> m;

    graph.assign(n, {});
    tin.assign(n, 0);
    low.assign(n, 0);
    subtree.assign(n, 0);
    ans.assign(m, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
    }

    // Graph may be disconnected
    for (int i = 0; i < n; ++i) {
        if (!tin[i]) {
            dfs(i);
        }
    }

    for (ll x : ans) {
        cout << x << '\n';
    }

    return 0;
}