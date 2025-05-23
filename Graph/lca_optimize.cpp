#include <bits/stdc++.h>
using namespace std;

#define vvi vector<vector<int>>
#define ll long long

int n, q, u, v, t;
ll ans;

struct lca {
    struct node {
        int depth, jump, par, subSize;
    };

    int root;
    vector<node> info;
    vector<vector<int>> adj;

    lca(int n, int root = 1) {
        adj.resize(n + 1);
        info.resize(n + 1);
        this->root = root;
        info[root] = {0, root, root, 1}; // Initialize root with depth 0, parent, and jump as itself
    }

    void insert(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int node = -1, int par = -1) {
        if (node == -1) node = root;   // Default DFS start at the rot
        if (par == -1) par = root;     // Root has no parent

        int par2 = info[par].jump;
        info[node] = {
            info[par].depth + 1,
            (info[par].depth - info[par2].depth == info[par2].depth - info[info[par2].jump].depth) ? info[par2].jump : par,
            par,
            1
        };

        for (int to : adj[node]) {
            if (to == par) continue;
            dfs(to, node);
            info[node].subSize += info[to].subSize;
        }
    }

    int ancestor_k(int node, int k) const {
        while (k > 0 && node > 0) {
            if (info[node].depth - k <= info[info[node].jump].depth) {
                k -= info[node].depth - info[info[node].jump].depth;
                node = info[node].jump;
            } else {
                k--;
                node = info[node].par;
            }
        }
        return node;
    }

    int query_lca(int x, int y) const {
        if (info[x].depth < info[y].depth) swap(x, y);
        x = ancestor_k(x, info[x].depth - info[y].depth);
        if (x == y) return x;

        while (x != y) {
            if (info[x].jump == info[y].jump) {
                x = info[x].par;
                y = info[y].par;
            } else {
                x = info[x].jump;
                y = info[y].jump;
            }
        }
        return x;
    }

    int dist(int x, int y) const {
        return info[x].depth + info[y].depth - 2 * info[query_lca(x, y)].depth;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    lca p(n);
    
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        p.insert(u, v);
    }

    p.dfs();
    
    cin >> q;
    int prev = 1;
    for (int i = 1; i <= q; i++) {
        cin >> t;
        ll cost = p.dist(pe, t);
        ans += cost;
        prev = t;
    } 

    cout << ans;
}
