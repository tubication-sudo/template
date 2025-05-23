#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, a[401], opt[401][401];
ll dp[401][401], ps[401];

int main() {
    ios :: sync_with_stdio();
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ps[i] = ps[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++) opt[i][i] = i;

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            int optL = opt[l][r - 1], optR = opt[l + 1][r]; 
            
            dp[l][r] = LLONG_MAX;

            for (int k = optL; k <= optR; k++) {
                ll cost = ps[r] - ps[l - 1];
                ll val = dp[l][k] + dp[k + 1][r] + cost;

                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    opt[l][r] = k;
                }
            }
        }
    }

    cout << dp[1][n];
}
