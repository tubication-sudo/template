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

const int range = 1e9 + 5;

struct lichao {
    line tr;
    lichao *lpt, *rpt;

    lichao() : tr(0, LLONG_MAX), lpt(nullptr), rpt(nullptr) {}

    int divi (int a, int b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    void update(line f, int l = -range, int r = range) {
        if (l == r) {
            tr = (f.calc(l) < tr.calc(l) ? f : tr);
            return;
        }
        int mid = divi(l + r, 2);
        if (f.calc(mid) < tr.calc(mid)) swap(tr, f);
        if (f.slope() > tr.slope()) {
            if (lpt == nullptr) lpt = new lichao();
            lpt->update(f, l, mid);
        }
        if (f.slope() < tr.slope()) {
            if (rpt == nullptr) rpt = new lichao();
            rpt->update(f, mid + 1, r);
        }
    }

    ll query(int pos, int l = -range, int r = range) {
        ll cur = tr.calc(pos);
        int mid = divi(l + r, 2);
        if (l == r) return cur;

        if (pos <= mid) return min(cur, lpt == nullptr ? LLONG_MAX : lpt->query(pos, l, mid));
        else return min(cur, rpt == nullptr ? LLONG_MAX : rpt->query(pos, mid + 1, r));
    }
};

int main() {

}