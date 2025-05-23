#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define sz(a) (int)a.size()
#define fi first
#define se second

const ll nmax = 1e5 + 5;

int n;
ll u, v, res = 0;
int a[nmax];
vector<int> adj[nmax];

vector<int> ext(int n) {
    vector<int> res;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    return res;
}

void dfs(int u, int p, unordered_map<int, ll>& large) {
    // vector<int> div = ext(a[u]);

    for (auto v : adj[u]) {
        if (v == p) continue;
        unordered_map<int, ll> small;
        dfs(v, u, small);

        if (sz(small) > sz(large)) swap(large, small);
        
        for (auto &p : small) {
            if (a[u] % p.fi == 0) {
                res += p.se * large[a[u] / p.fi];
            }
        }

        for (auto &p : small) large[p.fi] += p.se;
    }
    
    res += large[1];
    large[a[u]]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) cin >> a[i];

    unordered_map<int, ll> large;
    dfs(1, 0, large);

    cout << res << '\n';
    return 0;
}
