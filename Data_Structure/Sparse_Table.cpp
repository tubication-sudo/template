#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

int n, a[1000001];

int lg2(int n)  {
    return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1;
}

struct sparse_table {
    int n;
    vector<vector<ll>> table;

    sparse_table(int n, int arr[]) {
        this->n = n;
        table.resize(20, vector<ll>(n + 1));
        for (int i = 1; i <= n; i++) table[0][i] = arr[i];
        pre();
    }

    void pre() {
        for (int i = 1; (1 << i) <= n; i++) {
            for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    ll query(int u, int v) {
        int i = lg2(v - u + 1);
        return min(table[i][u], table[i][v - (1 << i) + 1]);
    }
};

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sparse_table rmq(n, a);

    cout << rmq.query(1, n);
}


