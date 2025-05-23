#include <bits/stdc++.h>
using namespace std;

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

    type query(int L, int R) const {
        return get(R) - get(L - 1);
    }
};
