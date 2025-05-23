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

int n, a[nmax];
int L[nmax], R[nmax];

void left_right() {
    for (int i = 1; i <= n; i++) {
        L[i] = i - 1;
        while (a[L[i]] >= a[i] && L[i] > 0) L[i] = L[L[i]];
    }

    for (int i = n; i >= 1; i--) {
        R[i] = i + 1;
        while (a[R[i]] >= a[i] && R[i] < n + 1) R[i] = R[R[i]];
    }
}

int main() {
}
