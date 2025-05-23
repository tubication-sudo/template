#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair

typedef pair<int, int> pii;

const int nmax = 1e5 + 5;

int n, q, u, v;
pii ques[nmax];
int type;

class dsu_rollback {
  private:
    vector<int> par, sz;
    vector<pair<int &, int>> history;

  public:
    dsu_rollback(int n) : par(n + 1), sz(n + 1) {
        for (int i = 1; i <= n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    bool unite(int u, int v) {
        u = find(u); v = find(v);

        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);

        history.push_back({par[v], par[v]});
        history.push_back({sz[u], sz[u]});

        par[v] = u;
        sz[u] += sz[v];

        return true;
    }

    void rollback(int until) {
        while (snapshot() > until) {
            history.back().fi = history.back().se;
            history.pop_back();
        }
    }

    int find(int u) { return (u == par[u] ? u : find(par[u])); }
    int snapshot() { return history.size(); }
    bool check(int u, int v) { return find(u) == find(v); }
};

class query_tree {
private:
    int q;
    vector<vector<pii>> tr;
    vector<bool> ans;
    dsu_rollback dsu;

public:
    query_tree(int n, int _Q) : dsu(n) {
        this->q = _Q;
        ans.resize(_Q, 0);
        tr.resize(4 * _Q + 1);
    }

    void push(int id, int l, int r, int u, int v, pii que) {
        if (v < l || r < u || u > v) return;

        if (u <= l && r <= v) {
            tr[id].push_back(que);
            return;
        }

        int m = (l + r) / 2;
        push(2 * id, l, m, u, v, que);
        push(2 * id + 1, m + 1, r, u, v, que);
    }

    void add_query(int l, int r, pii que) {
        push(1, 0, q - 1, l, r, que);
    }

    void dfs(int id, int l, int r) {
        int snapshot = dsu.snapshot();

        for (pii& q : tr[id]) dsu.unite(q.fi, q.se);

        if (l == r) {
            if (ques[l].fi != -1) ans[l] = dsu.check(ques[l].fi, ques[l].se);
        } else {
            int m = (l + r) / 2;
            dfs(2 * id, l, m);
            dfs(2 * id + 1, m + 1, r);
        }

        dsu.rollback(snapshot);
    }

    vector<bool> compute() {
        dfs(1, 0, q - 1);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> q;
    if (q == 0) return 0;

    query_tree qt(n, q);
    map<pii, stack<int>> time;
    vector<int> ans;

    for (int i = 0; i < q; i++) {
        cin >> type >> u >> v;

        if (u > v) swap(u, v);
        ques[i] = {-1, -1};

        if (type == 1) {
            time[{u, v}].push(i);
        }

        if (type == 2) {
            if (time[{u, v}].empty()) continue;
            int start_time = time[{u, v}].top(); time[{u, v}].pop();

            qt.add_query(start_time, i - 1, {u, v});
        }

        if (type == 3) {
            ans.push_back(i);
            ques[i] = {u, v};
        }
    }

    for (auto &it : time) {
        while (!it.second.empty()) {
            int start_time = it.second.top();
            it.second.pop();
            qt.add_query(start_time, q - 1, it.first);
        }
    }

    vector<bool> res = qt.compute();

    for (int pos : ans) cout << res[pos];
}
