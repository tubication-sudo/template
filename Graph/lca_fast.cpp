#include <bits/stdc++.h>
using namespace std;

#define vvi vector<vector<int>>

int lg2(int n)  {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

struct lca {
    int n, ptr;
    vector<int> euler, depthArr, fai, h;
    vvi adj;
    vvi dp;

    lca(int n) : h(n + 1) {
        fai.resize(n + 1, -1);
        adj.resize(n + 1);
        this->n = n;
        ptr = 0;
    }

    void insert(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init() {
        dfs(1, -1, 0);
        build(euler.size());
    }

    void dfs(int cur, int prev, int dep) {
        if (fai[cur] == -1) fai[cur] = ptr;
        h[cur] = dep;
        euler.push_back(cur);
        ptr++;
        for (int x : adj[cur]) {
            if (x != prev) {
                dfs(x, cur, dep + 1);
                euler.push_back(cur);
                ptr++;
            }
        }
    }

    void build(int n) {
        depthArr.clear();
        for (int x : euler) depthArr.push_back(h[x]);
        int m = depthArr.size();
        dp.assign(m, vector<int>(20, -1));
        for (int i = 1; i < m; i++) dp[i - 1][0] = (depthArr[i] > depthArr[i - 1]) ? i - 1 : i;
        for (int j = 1; (1 << j) <= m; j++) {
            for (int i = 0; i + (1 << j) <= m; i++) {
                dp[i][j] = (depthArr[dp[i][j - 1]] > depthArr[dp[i + (1 << (j - 1))][j - 1]]) ? dp[i + (1 << (j - 1))][j - 1] : dp[i][j - 1];
            }
        }
    }

    int query(int l, int r) {
        int d = r - l;
        int dx = lg2(d);
        if (depthArr[dp[l][dx]] > depthArr[dp[r - (1 << dx)][dx]]) return dp[r - (1 << dx)][dx];
        else return dp[l][dx];
    }

    int query_lca(int u, int v) {
        if (u == v) return u;
        if (fai[u] > fai[v]) swap(u, v);
        return euler[query(fai[u], fai[v])];
    }
};

int main() {
    int n, q, u, v;
    cin >> n;
    lca tree(n);

    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        tree.insert(u, v);
    }

    tree.init();

    cin >> q;
    while (q--) {
        cin >> u >> v;
        cout << tree.query_lca(u, v) << "\n";
    }

    return 0;
}
