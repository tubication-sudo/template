#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("O3,unroll-loops,inline")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4.1,sse4.2,mmx")

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

int main() {
}