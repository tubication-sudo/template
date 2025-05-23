#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int nmax = 1e6;
const ll mod = 1e9 + 7;

ll fact[nmax + 1], inv_fact[nmax + 1];
ll inv_num[nmax + 1];

void pre() {
    fact[0] = fact[1] = 1;
    inv_num[0] = inv_num[1] = 1;
    inv_fact[0] = inv_fact[1] = 1;

    for (int i = 2; i <= nmax; ++i) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv_num[i] = mod - (mod / i) * inv_num[mod % i] % mod;
        inv_fact[i] = (inv_fact[i - 1] * inv_num[i]) % mod;
    }
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (fact[n] * inv_fact[r] % mod) * inv_fact[n - r] % mod;
}

int main() {
    
}
