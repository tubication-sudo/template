#include <bits/stdc++.h>
using namespace std;

#define vvi vector <vector <int>> 

int n, k, u, v;

struct lca {
    int root;
    vector<int> h;
    vvi adj, up;

    lca(int n, int r = 1) : adj(n + 1, vector<int>()) {
        root = r;
        h.resize(n + 1);
        up.resize(n + 1, vector<int>(20));
    }

    void insert(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u = -1, int p = -1) {
        if (u == -1) u = root;
        up[u][0] = (p == -1 ? u : p);

        for (int v : adj[u]) {
            if (v == p) continue;
            h[v] = h[u] + 1;

            up[v][0] = u;

            for (int j = 1; j < 20; ++j) 
                up[v][j] = up[up[v][j - 1]][j - 1];
            
            dfs(v, u);
        }
    }

    int query_lca(int u, int v) {
        if (h[u] != h[v]) {
            if (h[u] < h[v]) swap(u, v);

            int k = h[u] - h[v];
            for (int j = 0; (1 << j) <= k; ++j)
                if (k >> j & 1) u = up[u][j];
        }

        if (u == v) return u;

        int k = __lg(h[u]);
        for (int j = k; j >= 0; --j) 
            if (up[u][j] != up[v][j]) 
                u = up[u][j], v = up[v][j];
        
        return up[u][0];
    }

    int dist(int u, int v) {
        return h[u] + h[v] - 2 * h[query_lca(u, v)];
    }

    int ancestor_k(int u, int k) {
        for (int j = 0; (1 << j) <= k; ++j)
            if (k >> j & 1) u = up[u][j];
        return u;
    }
};

lca p(100000);

int circle() {
    int pos = 1, ans = 0;

    for (int i = 1; i <= n; i++) {
        if (p.dist(pos, i) > ans) {
            ans = p.dist(pos, i);
            pos = i;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (p.dist(pos, i) > ans) {
            ans = p.dist(pos, i);
            pos = i;
        }
    }

    return ans;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        p.insert(u, v);
    }

    p.dfs();

}
