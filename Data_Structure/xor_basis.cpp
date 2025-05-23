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

struct xor_basis {
    vector<ll> basis;

    void insert(ll mask) {
        for (int i = 0; i < basis.size(); i++) mask = min(mask, mask ^ basis[i]);
        if (mask != 0) basis.push_back(mask);
    }

    void clear() { basis.clear(); }

    int size() const { return basis.size(); }

    void merge(const xor_basis &other) {
        for (int i = 0; i < other.size(); i++) insert(other.basis[i]);
    }

    ll get_max() const {
        ll res = 0;
        for (int i = 0; i < basis.size(); i++) res = max(res, res ^ basis[i]);
        return res;
    }

    bool can_represent(ll mask) const {
        for (int i = 0; i < basis.size(); i++) mask = min(mask, mask ^ basis[i]);
        return mask == 0;
    }
};


int tc, k, m;
int x[nmax];

int main() {
    synchronize;
    cin >> tc;
    while (tc--) {
        cin >> k >> m;
        xor_basis basis;
        int mask = (1 << k) - 1;
        for (int i = 1; i <= m; i++) {
            cin >> x[i];
            basis.insert(x[i]);
        }
        int d = (int)basis.size();

        cout << (1 << k) / (1 << d) << '\n';
    }
}