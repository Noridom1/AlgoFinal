#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w, id;

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> p, sz;

    DSU(int n) {
        p.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);

        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

struct State {
    long long cost;
    vector<int> treeEdges;
    vector<int> forced;
    vector<int> banned;

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

const long long INF = (1LL << 60);

int N, M, K;
vector<Edge> edges;

bool buildMST(
    const vector<int>& forced,
    const vector<int>& banned,
    long long& totalCost,
    vector<int>& usedEdges
) {
    vector<bool> isForced(M, false);
    vector<bool> isBanned(M, false);

    for (int x : forced) isForced[x] = true;
    for (int x : banned) isBanned[x] = true;

    DSU dsu(N);

    totalCost = 0;
    usedEdges.clear();

    // Add forced edges first
    for (int i = 0; i < M; i++) {
        if (!isForced[i]) continue;

        auto& e = edges[i];

        if (!dsu.unite(e.u, e.v))
            return false;

        totalCost += e.w;
        usedEdges.push_back(i);
    }

    // Normal Kruskal
    for (int i = 0; i < M; i++) {
        if (isForced[i] || isBanned[i]) continue;

        auto& e = edges[i];

        if (dsu.unite(e.u, e.v)) {
            totalCost += e.w;
            usedEdges.push_back(i);
        }
    }

    if ((int)usedEdges.size() != N - 1)
        return false;

    return true;
}

int main() {
    cin >> N >> M >> K;

    edges.resize(M);

    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    sort(edges.begin(), edges.end());

    priority_queue<State, vector<State>, greater<State>> pq;

    // Initial MST
    {
        State init;

        if (!buildMST({}, {}, init.cost, init.treeEdges)) {
            return 0;
        }

        pq.push(init);
    }

    long long answer = -1;

    for (int kth = 1; kth <= K; kth++) {
        if (pq.empty()) break;

        State cur = pq.top();
        pq.pop();

        answer = cur.cost;

        int sz = cur.treeEdges.size();

        // Generate children states
        vector<int> prefixForced = cur.forced;

        for (int i = 0; i < sz; i++) {
            int bannedEdge = cur.treeEdges[i];

            State nxt;

            nxt.forced = prefixForced;
            nxt.banned = cur.banned;
            nxt.banned.push_back(bannedEdge);

            if (buildMST(nxt.forced, nxt.banned,
                         nxt.cost, nxt.treeEdges)) {
                pq.push(nxt);
            }

            prefixForced.push_back(bannedEdge);
        }
    }

    cout << answer << '\n';

    return 0;
}
























/*
Sort all edges by weight and compute the normal MST using Kruskal.
Use a priority queue to enumerate spanning trees in increasing total cost order.
Each state represents a subset of spanning trees defined by:
forced edges (must appear),
banned edges (cannot appear).
For each state, run a constrained Kruskal algorithm:
first add all forced edges,
then run normal Kruskal while skipping banned edges.
The resulting tree is the minimum spanning tree inside that state/region.
Suppose the current spanning tree contains edges:
e1, e2, e3, ..., e(n-1)
Generate child states:
forbid e1
force e1, forbid e2
force e1,e2, forbid e3
...
This partitions all remaining spanning trees into disjoint regions:
every spanning tree belongs to exactly one region,
no duplicates occur.
Push the minimum tree of every valid region into the priority queue.
Repeatedly pop the smallest-cost state from the heap.
The K-th popped spanning tree is the K-th minimum spanning tree.

Algorithms used:

Kruskal Minimum Spanning Tree
Disjoint Set Union (DSU / Union-Find)
Best-first search using priority queue
State partitioning / K-best enumeration

Time Complexity:

One constrained MST build:
O(M α(N))
Each extracted state may generate up to N−1 child states.
For K spanning trees:
O(K · N · M · α(N))
Often simplified as:
O(KNM)

Space Complexity:

DSU and graph storage:
O(N + M)
Priority queue may store up to O(KN) states in worst case.
Each state stores edge constraints.
Total:
O(KN + M)


*/