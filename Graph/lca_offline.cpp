#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int nmax = 2e5 + 5;

int n, q, u, v;
vector<int> adj[nmax];

int qx[nmax], qy[nmax];
vector<pii> queries[nmax];

int lca[nmax], ancestor[nmax];
bool visited[nmax];

struct DSU {
    vector<int> parent, sz;

    DSU(int n) : parent(n + 1), sz(n + 1) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
    }
} dsu(nmax);

void cal_lca(int u, int p) {
    visited[u] = true;
    ancestor[u] = u;

    for (int v : adj[u]) {
        if (v == p) continue;
        cal_lca(v, u);
        dsu.merge(u, v);
        ancestor[dsu.find(u)] = u;
    }

    for (auto [v, pos] : queries[u]) {
        if (visited[v]) {
            lca[pos] = ancestor[dsu.find(v)];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> q;

    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= q; i++) {
        cin >> qx[i] >> qy[i];
        queries[qx[i]].push_back({qy[i], i});
        queries[qy[i]].push_back({qx[i], i});
    }

    cal_lca(1, 0);

    for (int i = 1; i <= q; i++) {
        cout << lca[i] << '\n';
    }

    return 0;
}
