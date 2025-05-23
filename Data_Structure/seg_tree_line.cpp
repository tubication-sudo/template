#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int nmax = 2e5 + 5;
const ll oo = 1e18;

struct line {
    ll m, b;

    line(ll _m = 0, ll _b = -oo) : m(_m), b(_b) {}

    ll get(ll x) {
        return m * x + b;
    }
};

struct seg_tree_line {
  private:
    vector<line> it;
    int n;

    void update(int id, int l, int r, int u, int v, line val) {
        if (u > r || v < l) return;

        if (u <= l && r <= v) {
            int mid = (l + r) / 2;

            bool left_dom = val.get(l) > it[id].get(l);
            bool right_dom = val.get(r) > it[id].get(r);

            if (left_dom && right_dom) { it[id] = val; return; } 
            else if (!left_dom && !right_dom) return;

            if (val.get(mid) > it[id].get(mid)) swap(it[id], val);

            if (l != r) {
                update(2 * id, l, mid, u, v, val);
                update(2 * id + 1, mid + 1, r, u, v, val);
            }

            return;
        }

        int mid = (l + r) / 2;
        update(2 * id, l, mid, u, v, val);
        update(2 * id + 1, mid + 1, r, u, v, val);
    }

    ll query(int id, int l, int r, int pos) {
        if (l > pos || r < pos) return -oo;

        ll res = it[id].get(pos);
        if (l == r) return res;

        int mid = (l + r) / 2;
        res = max(res, query(2 * id, l, mid, pos));
        res = max(res, query(2 * id + 1, mid + 1, r, pos));

        return res;
    }
    
  public:
    seg_tree_line(int n) : n(n) {
        it.resize(4 * n + 5, line());
    }

    void ins(ll m, ll b, int l, int r) {
        update(1, 0, n, l, r, line(m, b));
    }

    ll query(int pos) {
        ll val = query(1, 0, n, pos);
        if (val == -oo) return 0;
        return val;
    }
} seg(nmax);

int n, m;
ll s, e, v, d;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // freopen("JEWEL.INP", "r", stdin);
    // freopen("JEWEL.OUT", "w", stdout);

    cin >> n >> m;
    
    for (int i = 1; i <= m; i++) {
        cin >> s >> e >> v >> d;
        seg.ins(d, v - s * d, s, e);
    }

    for (int i = 1; i <= n; i++) {
        cout << seg.query(i) << '\n';
    }
}
