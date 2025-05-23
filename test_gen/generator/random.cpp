#include "random.h"
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

#define pii pair<int, int>
#define pli pair<ll, int>
#define pil pair<int, ll>
#define pll pair<ll, ll>

#define vvi vector<vector<int>>

#define fi first
#define se second

template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
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

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char *argv[]) {
    int seed = (argc > 1) ? stoi(argv[1]) : 0;
    Random gen(seed);
    
    int tc = gen.uniform(1, 1000);
    int sum = gen.uniform(100 * tc, 100000);
    vector<int> res = gen.gen_sum<int>(sum, tc, 1, 100000);

    cout << res.size() << '\n';
    for (int val : res) {
        cout << val << ' ' << gen.uniform<ll>(1, 900000000) << '\n';
    }
}
