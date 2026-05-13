#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Edge {
    int to, id;
};

class Graph {
private:
    int n, m;
    int timer;

    vector<vector<Edge>> adj;

    vector<int> tin; // time for a vertex to be first visited.
    vector<int> low; // Can this subtree climb back to an ancestor?
    vector<int> subtree; // number of vertices inside v’s DFS subtree

    vector<ll> ans;

    void dfs(int u, int parentEdge = -1) {
        tin[u] = low[u] = ++timer;
        subtree[u] = 1;

        for (const auto& e : adj[u]) {
            int v = e.to;
            int id = e.id;

            if (id == parentEdge)
                continue;

            // Back edge
            if (tin[v]) {
                low[u] = min(low[u], tin[v]); // node u can climb back to node v 
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

public:
    Graph(int vertices, int edges)
        : n(vertices),
          m(edges),
          timer(0),
          adj(n),
          tin(n, 0),
          low(n, 0),
          subtree(n, 0),
          ans(m, 0) {}

    void addEdge(int id, int u, int v) {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    vector<ll> solve() {
        for (int i = 0; i < n; ++i) {
            if (!tin[i]) {
                dfs(i);
            }
        }

        return ans;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n, m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        g.addEdge(i, u, v);
    }

    vector<ll> ans = g.solve();

    for (ll x : ans) {
        cout << x << '\n';
    }

    return 0;
}


























































/*
Idea
Use Tarjan DFS algorithm to find bridges.
For every DFS tree edge (u, v):
if low[v] > tin[u], then (u,v) is a bridge.
subtree[v] stores the number of vertices in v’s DFS subtree.
Removing a bridge splits the graph into:
one component of size subtree[v]
another of size n - subtree[v]
Therefore the number of disconnected vertex pairs is:
subtree[v]×(n−subtree[v])subtree[v] \times (n - subtree[v])subtree[v]×(n−subtree[v])
Non-bridge edges do not disconnect any vertices, so their answer is 0.
Important Definitions
tin[u]:
 discovery time of vertex u
low[u]:
 smallest discovery time reachable from the subtree of u
 using tree edges and at most one back edge
Bridge Condition
For DFS tree edge (u,v):
low[v]>tin[u]low[v] > tin[u]low[v]>tin[u]
means the subtree of v cannot reach u or any ancestor of u,
 so (u,v) is a bridge.
Time Complexity
O(N+M)
because DFS visits each vertex and edge once.
Space Complexity
O(N+M)
for adjacency list and DFS arrays.
*/