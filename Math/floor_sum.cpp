#include <bits/stdc++.h>
using namespace std;

#define file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define synchronize {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

#define ll long long
#define pii pair <int, int>

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

// Calculate (a * i + b) / m for i in range 0 -> n
ll floor_sum(ll n, ll m, ll a, ll b) {
    ll res = 0;

    if (a >= m) {
        res += (n * (n - 1) / 2) * (a / m);
        a %= m;
    }

    if (b >= m) {
        res += n * (b / m);
        b %= m;
    }

    ll y = (a * n + b) / m;
    ll x = (y * m - b);
    if (y == 0) return res;

    res += (n - (x + a - 1) / a) * y;
    res += f(y, a, m, (a - x % a) % a);

    return res;
}

int main() {
}