#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define synchronize {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for(long blockTime = 0; (blockTime == 0 ? (blockTime=clock()) != 0 : false); debug("%s time : %.4fs", d, (double)(clock() - blockTime) / CLOCKS_PER_SEC))

#define ll long long
#define ld long double

#define pii pair <int, int>
#define pli pair <ll, int>
#define pil pair <int, ll>
#define pll pair <ll, ll>

#define vvi vector <vector <int>>

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

const int mod = 3;

ll fact[mod], inv_fact[mod];
ll inv_num[mod];

void pre() {
    fact[0] = fact[1] = 1;
    inv_num[0] = inv_num[1] = 1;
    inv_fact[0] = inv_fact[1] = 1;

    for (int i = 2; i < mod; ++i) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv_num[i] = mod - (mod / i) * inv_num[mod % i] % mod;
        inv_fact[i] = (inv_fact[i - 1] * inv_num[i]) % mod;
    }
}

ll nCr(int n, int r) {
    auto cal = [](int n, int r) -> ll {
        if (r < 0 || r > n) return 0;
        return (fact[n] * inv_fact[r] % mod) * inv_fact[n - r] % mod;
    };

    if (r < 0 || r > n) return 0;
    if (n < mod && r < mod) return cal(n, r); 
    if (r == 0) return 1; 


    return (nCr(n / mod, r / mod) * cal(n % mod, r % mod)) % mod;
}

int main() {
    pre();
    
}