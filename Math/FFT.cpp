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

const int nmax = 3e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

using cd = complex<long double>;

void fft(vector<cd> &a, bool invert) {
    int n = a.size(), L = __builtin_ctz(n);
    vector<ll> rev(n);
    for (ll i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        cd wlen = polar(1.0L, acos(-1.0L) / len * (invert ? -2 : 2));
        for (int i = 0; i < n; i += len) {
            cd w = 1;
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (auto &x : a) x /= n;
    }
}

vector<ll> convolution(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    int n = 1;
    while (n < (ll)(a.size() + b.size()) - 1) n <<= 1;
    vector<cd> in(n), out(n);
    for (ll i = 0; i < (ll)a.size(); i++) in[i].real(a[i]);
    for (ll i = 0; i < (ll)b.size(); i++) in[i].imag(b[i]);
    fft(in, false);
    for (ll i = 0; i < n; i++) in[i] *= in[i];
    for (ll i = 0; i < n; i++) {
        ll j = -i & (n - 1);
        out[i] = in[i] - conj(in[j]);
    }
    fft(out, true);
    vector<ll> res(n);
    for (ll i = 0; i < n; i++)
        res[i] = (ll)(imag(out[i]) / 4 + 0.5);
    
    while (res.size() > (ll)(a.size() + b.size()) - 1) res.pop_back();
    return res;
}

int main() {
    
}