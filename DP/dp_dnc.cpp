#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int nmax = 1e6 + 5;

int n, m, tmp;
ll a[nmax], b[nmax];
ll best[nmax], ans = -1;

void cal(int i, int j, int l, int r) {
    if (i > j) return;
    int mid = (i + j) / 2, pos = 0;
    ll ans = 0;

    for (int p = l; p <= r; ++p) {
        ll val = (a[b[mid]] + a[p]) * (p - b[mid]);
        if (ans < val) {
            ans = val;
            pos = p;
        }
    }

    best[mid] = pos;
    cal(i, mid - 1, l, pos);
    cal(mid + 1, j, pos, r);
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (tmp < a[i]) {
            b[++m] = i;
            tmp = a[i];
        }
    }

    cal(1, m, 1, n);

    for (int i = 1; i <= m; ++i) ans = max(ans, (a[b[i]] + a[best[i]]) * (best[i] - b[i]));

    cout << ans;
}
