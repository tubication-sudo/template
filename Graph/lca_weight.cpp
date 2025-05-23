#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <ll, ll>
#define vvi vector <vector <ll>> 
#define vvp vector <vector <pii>>

#define fi first
#define se second

ll n, q, u, v, w;

struct lca {
    ll root;
    vector<ll> h, f;
    vvi up;
    vvp adj;

    lca (ll n, ll r = 1) : adj(n + 1, vector<pii>()), f(n + 1) {
        root = r;
        h.resize(n + 1);
        up.resize(n + 1, vector<ll>(20));
    }

    void insert(int u, int v, ll w = 1) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dfs(int u = -1, int p = -1) {
        if (u == -1) u = root, f[u] = 0;
        up[u][0] = (p == -1 ? u : p);

        for (pii v : adj[u]) {
            if (v.fi == p) continue;
            up[v.fi][0] = u;
            h[v.fi] = h[u] + 1;
            f[v.fi] = f[u] + v.se;
            

            for (ll j = 1; j < 20; ++j) 
                up[v.fi][j] = up[up[v.fi][j - 1]][j - 1];
            
            dfs(v.fi, u);
        }
    }

    int query_lca(int u, int v) {
        if (h[u] != h[v]) {
            if (h[u] < h[v]) swap(u, v);

            ll k = h[u] - h[v];
            for (ll j = 0; (1 << j) <= k; ++j)
                if (k >> j & 1) u = up[u][j];
        }

        if (u == v) return u;

        ll k = __lg(h[u]);
        for (ll j = k; j >= 0; --j) 
            if (up[u][j] != up[v][j]) 
                u = up[u][j], v = up[v][j];
        
        return up[u][0];
    }

    ll dist(int u, int v) {
        return f[u] + f[v] - 2 * f[query_lca(u, v)];
    }
};

int main() {
    cin >> n >> q;
    lca p(n);
    for (ll i = 1; i < n; i++) {
        cin >> u >> v >> w;
        p.insert(u, v, w);
    }

    p.dfs(); 

    while (q--) {
        cin >> u >> v;
        cout << p.dist(u, v) << '\n';
    }
}
