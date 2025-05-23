#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define synchronize {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

#define ll long long
#define pii pair <int, int>
#define pll pair <ll, ll>

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

template <class type>
struct fenwick_tree {
    int n;
    vector<type> tree;

    fenwick_tree() : n(0), tree() {}
    fenwick_tree(int n) : n(n), tree(n + 1, 0) {}

    void set(int n) {
        this->n = n;
        tree.assign(n + 1, 0);
    }

    void update(int u, type v) {
        for (int idx = u; idx <= n; idx += idx & -idx) {
            tree[idx] += v;
        }
    }

    type get(int u) const {
        type ans = 0;
        for (int idx = u; idx > 0; idx -= idx & -idx) {
            ans += tree[idx];
        }
        return ans;
    }

    type query(int L, int R) {
        return get(R) - get(L - 1);
    }
};

template <class type>
struct fenwick_range {
    int n;
    fenwick_tree<type> fen1, fen2;

    fenwick_range() : n(0), fen1(), fen2() {}
    fenwick_range(int n) : n(n), fen1(n), fen2(n) {}

    void set(int n) {
        this->n = n;
        fen1.set(n);
        fen2.set(n);
    }

    void update_point(int pos, type val) {
        fen1.update(pos, val);
        fen2.update(pos, val * (pos - 1));
    }

    void update(int pos, type val) {
        update_point(pos, val);
        update_point(pos + 1, -val);
    }

    void update(int l, int r, type val) {
        update_point(l, val);
        update_point(r + 1, -val);
    }

    type get(int pos) const {
        return fen1.get(pos) * pos - fen2.get(pos);
    }

    type query(int l, int r) const {
        return get(r) - get(l - 1);
    }
};

int main() {
}