#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define synchronize {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

#define fi first
#define se second

template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}

template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}

const int nmax = 3e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

struct node {
    int lazy;
    int cnt, mx;

    node() {
        cnt = 0;
        lazy = 0;
        mx = INT_MIN;
    }

    node(int val) {
        cnt = 1;
        lazy = 0;
        mx = val;
    }

    node operator+(const node &other) const {
        node res;
        res.cnt = 0;
        res.mx = max(mx, other.mx);

        if (mx == res.mx) res.cnt += cnt;
        if (other.mx == res.mx) res.cnt += other.cnt;

        res.lazy = 0;
        return res;
    }
};

struct seg_tree {
    vector<node> tree;
    int n;

    seg_tree(int n) : n(n), tree(4 * n + 1) {}

    void build(vector<int> &arr, int id, int l, int r) {
        if (l == r) {
            tree[id] = node(arr[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(arr, 2 * id, l, mid);
        build(arr, 2 * id + 1, mid + 1, r);

        tree[id] = tree[2 * id] + tree[2 * id + 1];
    }

    void build(int arr[], int id, int l, int r) {
        if (l == r) {
            tree[id] = node(arr[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(arr, 2 * id, l, mid);
        build(arr, 2 * id + 1, mid + 1, r);

        tree[id] = tree[2 * id] + tree[2 * id + 1];
    }

    void push(int id, int l, int r, int lazy) {
        tree[id].mx += lazy;
        tree[id].lazy += lazy;
    }

    void down(int id, int l, int r) {
        if (tree[id].lazy == 0) return;

        int mid = (l + r) / 2;
        push(2 * id, l, mid, tree[id].lazy);
        push(2 * id + 1, mid + 1, r, tree[id].lazy);

        tree[id].lazy = 0;
    }

    void update(int id, int l, int r, int u, int v, int val) {
        if (u > r || v < l) return;
        if (u <= l && r <= v) {
            push(id, l, r, val);
            return;
        }

        down(id, l, r);
        int mid = (l + r) / 2;
        update(2 * id, l, mid, u, v, val);
        update(2 * id + 1, mid + 1, r, u, v, val);

        tree[id] = tree[2 * id] + tree[2 * id + 1];
    }

    node query(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return node();
        if (u <= l && r <= v) return tree[id];

        down(id, l, r);
        int mid = (l + r) / 2;

        node tl = query(2 * id, l, mid, u, v);
        node tr = query(2 * id + 1, mid + 1, r, u, v);

        return tl + tr;
    }
};

int n, m, q;
int u, v, k;
int arr[nmax];

int main() {
    synchronize;
    cin >> n >> m;
    
    seg_tree seg(n);
    memset(arr, 0, sizeof(arr));

    seg.build(arr, 1, 1, n);

    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> k;
        seg.update(1, 1, n, u, v, k);
    }

    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> u >> v;
        node res = seg.query(1, 1, n, u, v);
        cout << res.mx << ' ' << res.cnt << '\n';
    }
}
