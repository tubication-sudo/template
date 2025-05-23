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

const int base = 31;
const ll MOD[] = {1000000007, 9999999967};

ll pbase[2][nmax];
pll HashF[nmax];
pll HashR[nmax];

void hash_str(const string &s) {
    int n = s.size();

    pbase[0][0] = pbase[1][0] = 1;
    for (int i = 1; i <= n; i++) {
        pbase[0][i] = (pbase[0][i - 1] * base) % MOD[0];
        pbase[1][i] = (pbase[1][i - 1] * base) % MOD[1];
    }

    for (int i = 1; i <= n; i++) {
        HashF[i].fi = (HashF[i - 1].fi * base + (s[i - 1] - 'a' + 1)) % MOD[0];
        HashF[i].se = (HashF[i - 1].se * base + (s[i - 1] - 'a' + 1)) % MOD[1];
    }

    for (int i = n; i >= 1; i--) {
        HashR[i].fi = (HashR[i + 1].fi * base + (s[i - 1] - 'a' + 1)) % MOD[0];
        HashR[i].se = (HashR[i + 1].se * base + (s[i - 1] - 'a' + 1)) % MOD[1];
    }
}

pll query_forward(int l, int r) {
    ll hash1 = (HashF[r].fi - HashF[l - 1].fi * pbase[0][r - l + 1] % MOD[0] + MOD[0]) % MOD[0];
    ll hash2 = (HashF[r].se - HashF[l - 1].se * pbase[1][r - l + 1] % MOD[1] + MOD[1]) % MOD[1];
    return {hash1, hash2};
}

pll query_reverse(int l, int r) {
    ll hash1 = (HashR[l].fi - HashR[r + 1].fi * pbase[0][r - l + 1] % MOD[0] + MOD[0]) % MOD[0];
    ll hash2 = (HashR[l].se - HashR[r + 1].se * pbase[1][r - l + 1] % MOD[1] + MOD[1]) % MOD[1];
    return {hash1, hash2};
}

int main() {
}