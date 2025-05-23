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
    ll a, b;

    line() : a(0), b(0) {}
    line (ll a, ll b) : a(a), b(b) {}

    ll calc (ll x) { return a * x + b; }
    ll slope() { return a; }
};

struct lichao {
    int n;
    vector<line> tr;

    lichao () {}
    lichao (int sz) : tr(sz + 1, line(0, LLONG_MAX)), n(sz) {}

    void update(line f, int l, int r) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        if (l == r) {
            tr[mid] = (f.calc(l) < tr[mid].calc(l) ? f : tr[mid]);
            return;
        }

        if (f.calc(mid) < tr[mid].calc(mid)) swap(tr[mid], f);
        if (f.slope() > tr[mid].slope()) update(f, l, mid - 1);
        if (f.slope() < tr[mid].slope()) update(f, mid + 1, r);
    }

    ll query (int p, int l, int r) {
        int mid = (l + r) >> 1;
        ll cur = tr[mid].calc(p);
        if (p == mid) return cur;
        if (p < mid) return min(query(p, l, mid - 1), cur);
        if (p > mid) return min(query(p, mid + 1, r), cur);
    }

    void update(line f) {
        update(f, 1, n);
    }
    
    ll query(int pos) {
        return query(pos, 1, n);
    }
};

int main() {
}