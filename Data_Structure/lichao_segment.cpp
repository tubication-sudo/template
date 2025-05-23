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

    lichao() {}
    lichao (int sz) : tr(4 * sz, line(0, LLONG_MAX)), n(sz) {}

    void addLine(line f, int id, int l, int r) {
        if (l == r) {
            tr[id] = (f.calc(l) < tr[id].calc(l) ? f : tr[id]);
            return;
        }
        
        int mid = (l + r) >> 1;
        if (f.calc(mid) < tr[id].calc(mid)) swap(tr[id], f);
        if (f.slope() > tr[id].slope()) addLine(f, 2 * id, l, mid);
        if (f.slope() < tr[id].slope()) addLine(f, 2 * id + 1, mid + 1, r);
    }

    void update(int a, int b, line f, int id, int l, int r) {
        if (b < l || r < a) return;
        if (a <= l && r <= b) return addLine(f, id, l, r), void();

        int mid = (l + r) >> 1;
        update(a, b, f, 2 * id, l, mid);
        update(a, b, f, 2 * id + 1, mid + 1, r);
    }

    ll query(int pos, int id, int l, int r) {
        ll cur = tr[id].calc(pos);
        
        int mid = (l + r) >> 1;
        if (l == r) return cur;
        if (pos <= mid) return min(cur, query(pos, 2 * id, l, mid));
        else return min(cur, query(pos, 2 * id + 1, mid + 1, r));
    }

    void update(line f, int l, int r) {
        update(l, r, f, 1, 1, n);
    }

    ll query (int pos) {
        return query(pos, 1, 1, n);
    }
};

int main() {
}