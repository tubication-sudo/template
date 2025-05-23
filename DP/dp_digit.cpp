#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll mod = 1e9 + 7;

int t;
string L, R;
ll dp[50][2][2][33][33][2];

ll cal(int i, bool bl, bool sr, int cnt36, int cnt39, bool check3) {
    int x = cnt36 + 16, y = cnt39 + 16;

    if (i == R.size()) return (cnt36 == 0 && cnt39 == 0 && check3);

    if (cnt36 < -16 || cnt36 > 16) return 0;
    if (cnt39 < -16 || cnt39 > 16) return 0;

    if (dp[i][bl][sr][x][y][check3] != -1) return dp[i][bl][sr][x][y][check3];

    int a = (bl ? 0: L[i] - '0');
    int b = (sr ? 9: R[i] - '0');
    
    ll ans = 0;

    for (int z = a; z <= b; z++) {
        ans += cal(i + 1, bl || z > a, sr || z < b, cnt36 + (z == 3) - (z == 6), cnt39 + (z == 3) - (z == 9), check3 || (z == 3));
        ans %= mod;
    }

    return dp[i][bl][sr][x][y][check3] = ans;
}


int main() {
    cin >> t; while (t--) {
        cin >> L >> R;
        while (L.size() != R.size()) L = '0' + L;

        memset(dp, -1, sizeof(dp));
        cout << cal(0, 0, 0, 0, 0, 0) << '\n';
    }
}