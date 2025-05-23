#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define synchronize {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for(long blockTime = 0; (blockTime == 0 ? (blockTime=clock()) != 0 : false); debug("%s time : %.4fs", d, (double)(clock() - blockTime) / CLOCKS_PER_SEC))

#define ll long long
#define ld long double

#define pii pair <int, int>
#define pli pair <ll, int>
#define pil pair <int, ll>
#define pll pair <ll, ll>

#define vvi vector <vector <int>>

#define fi first
#define se second

template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y) {
            x = y;
            return true;
        }
        else return false;
    }

template <class X, class Y>
    bool minimize(X &x, Y y) {
        if (x > y) {
            x = y;
            return true;
        }
        return false;
    }   

const int nmax = 3e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

struct line {
    long long a, b;
    mutable long long p;
    
    bool operator<(const line& o) const {
        return (o.a == LLONG_MAX) ? (p < o.p) : (a > o.a);
    }
};

struct line_container {
    multiset<line> hull;
    
    long long div(long long a, long long b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    
    bool isect(multiset<line>::iterator x, multiset<line>::iterator y) {
        if (y == hull.end()) return x->p = LLONG_MAX, false;
        if (x->a == y->a) x->p = (x->b < y->b) ? LLONG_MAX : -LLONG_MAX;
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    
    void add(long long a, long long b) {
        auto x = hull.insert({a, b, 0}), y = next(x);
        while (isect(x, y)) y = hull.erase(y);
        if ((y = x) != hull.begin() && isect(--y, x)) isect(y, hull.erase(x));
        while ((x = y) != hull.begin() && (--x)->p >= y->p)
            isect(x, hull.erase(y)), y = x;
    }
    
    long long query(long long x) {
        auto l = *hull.lower_bound({LLONG_MAX, LLONG_MAX, x});
        return l.a * x + l.b;
    }
    
    void merge(line_container& other) {
        for (const auto& line : other.hull) {
            add(line.a, line.b);
        }
    }
};

int n, u, v;
ll a[nmax], b[nmax], f[nmax]; 
vector <int> adj[nmax];

void dfs(int u, int p, line_container &large) {
    bool leaf = true;
    for (int v : adj[u]) {
        if (v == p) continue;
        line_container small;
        dfs(v, u, small);
        if (small.hull.size() > large.hull.size()) swap(small, large);
        large.merge(small);
        leaf = false;
    }

    if (!leaf) f[u] = large.query(a[u]); 
    large.add(b[u], f[u]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    for (int i = 1; i < n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    line_container large;
    dfs(1, -1, large);

    for (int i = 1; i <= n; ++i) cout << f[i] << ' ';
    return 0;
}