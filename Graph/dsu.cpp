#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector <int> parent, sz;

    DSU(int n): parent(n + 1), sz(n + 1) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i; sz[i] = 1;
        }
    };

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
    }

    bool check(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
}