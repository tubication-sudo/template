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

#define all(v) (v).begin(), (v).end()
#define __builtin_popcount __builtin_popcountll

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

/** END OF TEMPLATE **/

int main() {

    return (0 ^ 0);
}